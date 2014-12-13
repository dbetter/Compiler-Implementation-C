/************/
/* semant.c */
/************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "../../COMMON_H_FILES/types.h"
#include "../../COMMON_H_FILES/env.h"
#include "../../COMMON_H_FILES/semant.h"
#include "../../COMMON_H_FILES/symbol.h"
#include "../../COMMON_H_FILES/absyn.h"
#include "../../COMMON_H_FILES/errormsg.h"

/**************************/
/* FUNCTIONS DECLARATIONS */
/**************************/
Ty_ty SEM_transExp(S_table venv,S_table tenv,A_exp exp);

void SEM_transVarDecInit(S_table venv,S_table tenv, A_dec dec)
{
	Ty_ty type;

	/*****************************/
	/* [1] trans initialized exp */
	/*****************************/
	type = SEM_transExp(venv,tenv,dec->u.var.init);

	/********************************************/
	/* [2] check if variable's type was defined */
	/********************************************/
	if (dec->u.var.typ != NULL)
	{
		/***************************************/
		/* [3] check if variable's type exists */
		/***************************************/
		if (S_look(tenv,dec->u.var.typ) == NULL)
		{
			EM_error(dec->pos,"unknown type %s\n",dec->u.var.typ);
			return;
		}

		/****************************************************************************************/
		/* [4] make sure the initialized value is the same as the declared type of the variable */
		/****************************************************************************************/
		if (type != (Ty_ty) S_look(tenv,dec->u.var.typ))
		{
			EM_error(dec->pos,"type mismatch in initialization of variable");
		}
	}

	/**********************************/
	/* [4] Enter the variable to venv */
	/**********************************/
	S_enter(venv,dec->u.var.var,type);
}

void SEM_transVarDecNoInit(S_table venv,S_table tenv, A_dec dec)
{
	/*********************************************/
	/* [1] make sure variable's type was defined */
	/*********************************************/
	if (dec->u.var.typ == NULL) 
	{
		EM_error(dec->pos,"could not determine variable type\n");
		return;
	}

	/***************************************/
	/* [2] check if variable's type exists */
	/***************************************/
	if (S_look(tenv,dec->u.var.typ) == NULL)
	{
		EM_error(dec->pos,"unknown type %s\n",dec->u.var.typ);
		return;
	}

	/**********************************/
	/* [3] Enter the variable to venv */
	/**********************************/
	S_enter(venv,dec->u.var.var,(Ty_ty) S_look(tenv,dec->u.var.typ));	
}

void SEM_transVarDec(S_table venv,S_table tenv, A_dec dec)
{
	/********************************************************************/
	/* [0] Make sure the declaration is indeed a "variable" declaration */
	/********************************************************************/
	assert(dec->kind == A_varDec);

	/*************************************/
	/* [1] trans var with initialization */
	/*************************************/
	if (dec->u.var.init != NULL)
	{
		SEM_transVarDecInit(venv,tenv,dec);
		return;
	}

	/****************************************/
	/* [2] trans var without initialization */
	/****************************************/
	if (dec->u.var.init == NULL)
	{
		SEM_transVarDecNoInit(venv,tenv,dec);
		return;
	}
}

void SEM_transNameTypeDec(S_table venv,S_table tenv, A_dec dec)
{
	Ty_ty type = (Ty_ty) S_look(tenv,dec->u.type->ty->u.name);

	if (type == NULL)
	{
		/*********************************/
		/* [0] make sure the type exists */
		/*********************************/
		EM_error(dec->pos,"undefined type %s\n",S_name(dec->u.type->ty->u.name));
		return;
	}
	else
	{
		S_enter(tenv,dec->u.type->name,type);
		return;
	}
}

void SEM_transArrayTypeDec(S_table venv,S_table tenv, A_dec dec)
{
	/*****************************************************/
	/* [0] make sure type name is not previously defined */
	/*****************************************************/
	if (S_look(tenv,dec->u.type->name) != NULL)
	{
		EM_error(dec->pos,"type %s previously defined in current scope",S_name(dec->u.type->name));
		return;
	}

	/**********************************************/
	/* [1] make sure the type of array is defined */
	/**********************************************/
	if (S_look(tenv,dec->u.type->ty->u.array) == NULL)
	{
		EM_error(dec->pos,"undefined type %s for array\n",S_name(dec->u.type->ty->u.array));
		return;
	}

	/******************************/
	/* [2] Enter new type to tenv */
	/******************************/
	S_enter(tenv,dec->u.type->name,Ty_Array((Ty_ty) S_look(tenv,dec->u.type->ty->u.array)));
}

void SEM_transRecordTypeDec(S_table venv,S_table tenv, A_dec dec)
{
	Ty_field fieldType;
	Ty_fieldList fieldsTypesList=NULL;
	A_fieldList fields = dec->u.type->ty->u.record;

	/***********************************************************************/
	/* [0] We have to make sure there are no two fields with the same name */
	/* for that, we open a new environment, and make sure each field name  */
	/* wasn't previously defined in this record                            */
	/***********************************************************************/
	S_beginScope(tenv);

	/***********************************************************************************/
	/* [1] for each field check two things: that its type exists, and its name doesn't */
	/***********************************************************************************/
	for (fields=dec->u.type->ty->u.record; fields != NULL;fields = fields->tail)
	{
		/************************************/
		/* [1a] chaeck that its type exists */
		/************************************/
		if (S_look(tenv,fields->head->typ) == NULL)
		{
			EM_error(fields->head->pos,"undefined type for field %s of record %s",S_name(fields->head->name),S_name(dec->u.type->name));
			return;
		}
		/*******************************************/
		/* [1b] chaeck that its name doesn't exist */
		/*******************************************/
		if (S_look(tenv,fields->head->name) != NULL)
		{
			EM_error(fields->head->pos,"record %s has two fields with the same name: %s",S_name(dec->u.type->name),S_name(fields->head->name));
			return;
		}
		else
		{
			S_enter(tenv,fields->head->name,"dummy");
		}
	}
	
	/*****************************************/
	/* see explanation above for begin scope */
	/*****************************************/
	S_endScope(tenv);

	for (fields=dec->u.type->ty->u.record; fields != NULL;fields = fields->tail)
	{
		fieldType = Ty_Field(fields->head->name,(Ty_ty) S_look(tenv,fields->head->typ));
		fieldsTypesList = Ty_FieldList(fieldType,fieldsTypesList);
	}

	/*********************/
	/* enter record type */
	/*********************/
	S_enter(tenv,dec->u.type->name,Ty_Record(fieldsTypesList));
}

void SEM_transTypeDec(S_table venv,S_table tenv, A_dec dec)
{
	/************************************************************/
	/* [0] make sure declaration is indeed a "type" declaration */
	/************************************************************/
	assert(dec->kind == A_typeDec);

	/************************************************/
	/* [1] make sure type does not exist previously */
	/************************************************/
	if (S_look(tenv,dec->u.type->name) != NULL)
	{
		EM_error(dec->pos,"type %s previously defined in this scope",S_name(dec->u.type->name));
		return;
	}

	/********************************************************/
	/* [2] scan the declaration for simple, array or record */
	/********************************************************/
	switch (dec->u.type->ty->kind) {
	case (A_nameTy): SEM_transNameTypeDec(  venv,tenv,dec); return; 
	case(A_recordTy):SEM_transRecordTypeDec(venv,tenv,dec); return; 
	case(A_arrayTy): SEM_transArrayTypeDec( venv,tenv,dec); return; 
	}
}

void SEM_transFuncDec(S_table venv,S_table tenv, A_dec dec)
{
	Ty_ty type;
	Ty_ty resultType=NULL;
	A_fundec f = dec->u.function;
	A_fieldList functionParameters = f->params;
	Ty_tyList parametersTypes=Ty_TyList(NULL,NULL);
	Ty_tyList temp=parametersTypes;

	/**************************************************************/
	/* [0] check type of the returned value in case it is defined */
	/**************************************************************/
	if (f->result != NULL)
	{
		resultType = (Ty_ty) S_look(tenv,f->result);
		if (resultType == NULL)
		{
			EM_error(f->pos,"Unknown returned type in function %s\n",f->name);
		}
	}

	/******************************************/
	/* [1] check types of function parameters */
	/******************************************/
	for (functionParameters = f->params;functionParameters;functionParameters=functionParameters->tail) 
	{
		type = (Ty_ty) S_look(tenv,functionParameters->head->typ);
		if (type == NULL)
		{
			EM_error(f->pos,"unknown parameter type in function declaration\n",f->name);
		}
	}

	/***************************************************/
	/* [2] pack types of function parameters in a list */
	/***************************************************/
	for (functionParameters = f->params;functionParameters;functionParameters=functionParameters->tail) 
	{
		type = (Ty_ty) S_look(tenv,functionParameters->head->typ);
		temp->tail = Ty_TyList(type,NULL);
		temp = temp->tail;
	}

	/************************************************/
	/* [3] enter parameters to variable environment */
	/************************************************/
	for (functionParameters = f->params;functionParameters;functionParameters=functionParameters->tail) 
	{
		S_enter(venv,functionParameters->head->name,S_look(tenv,functionParameters->head->typ));
	}

	/**********************/
	/* [4] trans the body */
	/**********************/
	type=SEM_transExp(venv,tenv,dec->u.function->body);

	/***************************************************************/
	/* [5] Compare actual return type to declared one, if declared */
	/***************************************************************/
	if (f->result != NULL)
	{
		if (resultType != type)
		{
			EM_error(dec->pos,"return value has different type from declaration");
		}
	}

	/**********************************************/
	/* [6] enter function to variable environment */
	/**********************************************/
	S_enter(venv,f->name,E_FunEntry(parametersTypes->tail,type,NULL));

	/***************************/
	/* [7] free allocated data */
	/***************************/
	free(parametersTypes);
}

void SEM_transDecs(S_table venv,S_table tenv, A_decList decList)
{
	/**************************/
	/* [1] trans dec the head */
	/**************************/
	switch (decList->head->kind) {
	case (A_varDec):      SEM_transVarDec( venv,tenv,decList->head); break;
	case (A_typeDec):     SEM_transTypeDec(venv,tenv,decList->head); break;
	case (A_functionDec): SEM_transFuncDec(venv,tenv,decList->head); break;
	}

	/**************************/
	/* [2] trans dec the tail */
	/**************************/
	if (decList->tail != NULL) SEM_transDecs(venv,tenv,decList->tail);
}

Ty_ty SEM_transSeqExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;
	A_expList expList;

	/**********************/
	/* [0] Trans exp list */
	/**********************/
	for (expList=exp->u.seq; expList; expList = expList->tail)
	{
		/**********************/
		/* [1] Trans the head */
		/**********************/
		type=SEM_transExp(venv,tenv,expList->head);
	}
	
	/************************************************************************************/
	/* [2] the returned type of a seq expression is the last expression of the sequence */
	/************************************************************************************/
	return type;
}

Ty_ty SEM_transLetExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;

	/*************************************************************/
	/* [0] Make sure the expression is indeed a "let" expression */
	/*************************************************************/
	assert(exp->kind  == A_letExp);

	/*************************************************/
	/* [1] open a new variable and type environments */
	/*************************************************/
	S_beginScope(venv);
	S_beginScope(tenv);

	/***********************************/
	/* [2] Scan  the declarations part */
	/***********************************/
	SEM_transDecs(venv,tenv,exp->u.let.decs);

	/**********************************/
	/* [3] Scan  the expressions part */
	/**********************************/
	type=SEM_transExp(venv,tenv,exp->u.let.body);

	/****************************************************/
	/* [4] close the new variable and type environments */
	/****************************************************/
	S_endScope(venv);
	S_endScope(tenv);

	return type;
}

Ty_ty TypeCheck(Ty_ty left,Ty_ty right, A_oper op,int pos)
{
	switch (op) {
	case (A_andOp):
	case (A_orOp):

		if ((left == Ty_Int()) && (right == Ty_Int()))
		{
			return Ty_Int();
		}
		else
		{
			EM_error(pos,"Illegal use of operator(s) |,& between operands");
			return left;
		}

	case (A_plusOp):
	case (A_minusOp):
	case (A_timesOp):
	case (A_divideOp):

		if ((left == Ty_Int()) && (right == Ty_Int()))
		{
			return Ty_Int();
		}
		else
		{
			if ((left == Ty_Int())   && (right == Ty_Float())  ||
				(left == Ty_Float()) && (right == Ty_Int())    ||
				(left == Ty_Float()) && (right == Ty_Float()))
			{
				return Ty_Float();
			}
			else
			{
				EM_error(pos,"Illegal use of operator(s) +,-,*,/ between operands");
				return left;
			}
		}

	case (A_eqOp):
	case (A_neqOp):

		/******************************/
		/* Comparison between numbers */
		/******************************/
		if ((left == Ty_Int())    && (right == Ty_Int()))    {return Ty_Int();}
		if ((left == Ty_Int())    && (right == Ty_Float()))  {return Ty_Int();}
		if ((left == Ty_Float())  && (right == Ty_Int()))    {return Ty_Int();}
		if ((left == Ty_Float())  && (right == Ty_Float()))  {return Ty_Int();}

		/******************************/
		/* Comparison between strings */
		/******************************/
		if ((left == Ty_String()) && (right == Ty_String())) {return Ty_Int();}

		/******************************/
		/* Comparison between records */
		/******************************/
		if ((left->kind == Ty_record) && (right->kind == Ty_record)) {return Ty_Int();}

	case (A_ltOp):
	case (A_leOp):
	case (A_gtOp):
	case (A_geOp):

		/******************************/
		/* Comparison between numbers */
		/******************************/
		if ((left == Ty_Int())    && (right == Ty_Int()))    {return Ty_Int();}
		if ((left == Ty_Int())    && (right == Ty_Float()))  {return Ty_Int();}
		if ((left == Ty_Float())  && (right == Ty_Int()))    {return Ty_Int();}
		if ((left == Ty_Float())  && (right == Ty_Float()))  {return Ty_Int();}

		/******************************/
		/* Comparison between strings */
		/******************************/
		if ((left == Ty_String()) && (right == Ty_String())) {return Ty_Int();}
	}
}

Ty_ty SEM_transOpExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;
	Ty_ty left;
	Ty_ty right;

	/*************************************************************/
	/* [0] Make sure the expression is indeed an "op" expression */
	/*************************************************************/
	assert(exp->kind  == A_opExp);

	/******************************/
	/* [1] trans the left operand */
	/******************************/
	left = SEM_transExp(venv,tenv,exp->u.op.left);

	/*******************************/
	/* [2] trans the right operand */
	/*******************************/
	right = SEM_transExp(venv,tenv,exp->u.op.right);

	/****************************************************/
	/* [3] check validity of operation between operands */
	/****************************************************/
	type = TypeCheck(left,right,exp->u.op.oper,exp->pos);

	/****************/
	/* return value */
	/****************/
	return type;
}

Ty_ty SEM_transIntExp(S_table venv,S_table tenv,A_exp exp)
{
	/**************************************************************/
	/* [0] Make sure the expression is indeed an "int" expression */
	/**************************************************************/
	assert(exp->kind  == A_intExp);

	/**************/
	/* [1] return */
	/**************/
	return Ty_Int();
}

Ty_ty SEM_transFloatExp(S_table venv,S_table tenv,A_exp exp)
{
	/***************************************************************/
	/* [0] Make sure the expression is indeed a "float" expression */
	/***************************************************************/
	assert(exp->kind  == A_floatExp);

	/**************/
	/* [1] return */
	/**************/	
	return Ty_Float();
}

Ty_ty SEM_transVarExp(S_table venv,S_table tenv,A_var var)
{
	Ty_ty type;
	Ty_fieldList fieldList;

	switch (var->kind) {
	case (A_simpleVar):

		/****************************/
		/* [0] check if type exists */
		/****************************/
		if (S_look(venv,var->u.simple) == NULL)
		{
			/*****************************/
			/* ERROR: type doesn't exist */
			/*****************************/
			EM_error(var->pos,"undefined variable %s\n",S_name(var->u.simple));
			return NULL;
		}
	
		return (Ty_ty) S_look(venv,var->u.simple);

	case (A_fieldVar):

		/*************/
		/* [1] TO DO */
		/*************/
		break;

	case (A_subscriptVar):

		/*************/
		/* [2] TO DO */
		/*************/
		break;
	}
}

Ty_ty SEM_transAssignExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type1;
	Ty_ty type2;

	/*********************************************************************/
	/* [0] Make sure the expression is indeed an "assignment" expression */
	/*********************************************************************/
	assert(exp->kind == A_assignExp);

	/************************************/
	/* [1] trans initialized expression */
	/************************************/
	type1 = SEM_transExp(venv,tenv,exp->u.assign.exp);

	/**********************/
	/* [2] trans variable */
	/**********************/
	type2 = SEM_transVarExp(venv,tenv,exp->u.var);
	
	/******************/
	/* [3] type check */
	/******************/
	if (type1 != type2)
	{
		EM_error(exp->pos,"Illegal assignment\n");
	}

	return type1;
}

Ty_ty SEM_transForExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;

	/*************************************************************/
	/* [0] Make sure the expression is indeed a "for" expression */
	/*************************************************************/
	assert(exp->kind == A_forExp);

	/*********/
	/* TO DO */
	/*********/
	return NULL;
}

Ty_ty SEM_transIfExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;

	/*************************************************************/
	/* [0] Make sure the expression is indeed an "if" expression */
	/*************************************************************/
	assert(exp->kind == A_ifExp);

	/*********************************************************************/
	/* [1] Check the test expression to make sure it has an integer type */
	/*********************************************************************/
	type=SEM_transExp(venv,tenv,exp->u.iff.test);
	if (type != Ty_Int())
	{
		EM_error(exp->pos,"condition in IF expression is not an integer");
		return NULL;
	}

	/***********************************/
	/* [2] trans the result expression */
	/***********************************/
	type=SEM_transExp(venv,tenv,exp->u.iff.then);

	return type;
}

Ty_ty SEM_transCallExp(S_table venv,S_table tenv,A_exp exp)
{
	int i=0;
	Ty_ty type;
	E_enventry enventry;
	int parameterNumberOnList=1;
	A_expList functionArguments=NULL;
	Ty_tyList expectedParametersTypesList=NULL;

	/**************************************************************/
	/* [0] Make sure the expression is indeed a "call" expression */
	/**************************************************************/
	assert(exp->kind == A_callExp);

	/*****************************/
	/* [1] Check function exists */
	/*****************************/
	enventry = (E_enventry) S_look(venv,exp->u.call.func);
	if ((enventry == NULL) || (enventry->kind != E_funEntry))
	{
		EM_error(exp->pos,"a call to an undefined function");
		return NULL;
	}

	functionArguments = exp->u.call.args;
	expectedParametersTypesList = enventry->u.fun.formals;

	/***********************************************************/
	/* [2] Check that the arguments match their expected types */
	/***********************************************************/
	while ((functionArguments != NULL) || (expectedParametersTypesList != NULL))
	{
		if ((functionArguments != NULL) && (expectedParametersTypesList == NULL))
		{
			EM_error(exp->pos,"wrong number of parameters passed to function %s",S_name(exp->u.call.func));
		}

		if ((functionArguments == NULL) && (expectedParametersTypesList != NULL))
		{
			EM_error(exp->pos,"wrong number of parameters passed to function %s",S_name(exp->u.call.func));
		}

		type = SEM_transExp(venv,tenv,functionArguments->head);

		if (type != expectedParametersTypesList->head)
		{
			EM_error(exp->pos,"mismatch parameter passing no. %d for function %s",parameterNumberOnList,S_name(exp->u.call.func));
		}

		parameterNumberOnList++;

		functionArguments = functionArguments->tail;
		expectedParametersTypesList = expectedParametersTypesList->tail;
	}

	// return type;
	return enventry->u.fun.result;
}

Ty_ty SEM_transAllocateArrayExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;

	type = (Ty_ty) S_look(tenv,exp->u.arrayInit.arrayType);

	if (type == NULL)
	{
		EM_error(exp->pos,"type of array (%s) is undefined\n",S_name(exp->u.arrayInit.arrayType));
		return NULL;
	}

	return type;
}

Ty_ty SEM_transAllocateRecordExp(S_table venv,S_table tenv,A_exp exp)
{
	Ty_ty type;

	type = (Ty_ty) S_look(tenv,exp->u.recordInit.reocrdType);

	if (type == NULL)
	{
		EM_error(exp->pos,"undefined record %s\n",S_name(exp->u.recordInit.reocrdType));
		return NULL;
	}

	return type;
}

/****************/
/* SEM_transExp */
/****************/
Ty_ty SEM_transExp(S_table venv,S_table tenv,A_exp exp)
{
	switch (exp->kind) {
	case (A_opExp):             return SEM_transOpExp(            venv,tenv,exp);
	case (A_ifExp):             return SEM_transIfExp(            venv,tenv,exp);
	case (A_forExp):            return SEM_transForExp(           venv,tenv,exp);
	case (A_letExp):            return SEM_transLetExp(           venv,tenv,exp);
	case (A_intExp):            return SEM_transIntExp(           venv,tenv,exp);
	case (A_seqExp):            return SEM_transSeqExp(           venv,tenv,exp);
	case (A_varExp):            return SEM_transVarExp(           venv,tenv,exp->u.var);
	case (A_callExp):           return SEM_transCallExp(          venv,tenv,exp);
	case (A_floatExp):          return SEM_transFloatExp(         venv,tenv,exp);
	case (A_assignExp):         return SEM_transAssignExp(        venv,tenv,exp);
	case (A_allocateArrayExp):  return SEM_transAllocateArrayExp( venv,tenv,exp);
	case (A_allocateRecordExp): return SEM_transAllocateRecordExp(venv,tenv,exp);
	}
}

/*****************/
/* SEM_transProg */
/*****************/
void SEM_transProg(A_exp exp)
{
	S_table baseTypesEnv;
	S_table baseVariablesEnv;

	/****************************************************/
	/* [0] set up base variables and types environments */
	/****************************************************/
	baseTypesEnv = E_base_tenv();
	baseVariablesEnv = E_base_venv();

	/*********************************************/
	/* [1] enter basic types: int, float, string */
	/*********************************************/
	S_enter(baseTypesEnv,S_Symbol("int"),Ty_Int());
	S_enter(baseTypesEnv,S_Symbol("float"),Ty_Float());
	S_enter(baseTypesEnv,S_Symbol("string"),Ty_String());

	/*****************************/
	/* [2] enter basic functions */
	/*****************************/
	S_enter(baseVariablesEnv,S_Symbol("PrintInt"),   E_FunEntry(Ty_TyList(Ty_Int(),   NULL),Ty_Nil(),NULL));
	S_enter(baseVariablesEnv,S_Symbol("PrintFloat"), E_FunEntry(Ty_TyList(Ty_Float(), NULL),Ty_Nil(),NULL));
	S_enter(baseVariablesEnv,S_Symbol("PrintString"),E_FunEntry(Ty_TyList(Ty_String(),NULL),Ty_Nil(),NULL));

	/********************************/
	/* [3] trans the entire program */
	/********************************/
	SEM_transExp(baseVariablesEnv,baseTypesEnv,exp);
}