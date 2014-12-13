/*******************/
/* FILE NAME: IR.c */
/*******************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "../../COMMON_H_FILES/frame.h"
#include "../../COMMON_H_FILES/tree.h"
#include "../../COMMON_H_FILES/types.h"
#include "../../COMMON_H_FILES/env.h"
#include "../../COMMON_H_FILES/semant.h"
#include "../../COMMON_H_FILES/symbol.h"
#include "../../COMMON_H_FILES/absyn.h"
#include "../../COMMON_H_FILES/errormsg.h"

/**************************/
/* FUNCTIONS DECLARATIONS */
/**************************/
T_exp IR_transExp(S_table venv, S_table tenv, A_exp exp, F_frame frame);

/**********************************/
/* HELPER FUNCTIONS :: PUSH & POP */
/**********************************/
T_exp PUSH(Temp_temp t)
{
	return T_Seq(
		T_Move(T_Mem(T_Temp(SP())), T_Temp(t)),
		T_Move(T_Temp(SP()), T_Binop(T_minus, T_Temp(SP()), T_Const(F_wordSize))));
}

T_exp POP(Temp_temp t)
{
	return T_Seq(
		T_Move(T_Temp(t), T_Mem(T_Temp(SP()))),
		T_Move(T_Temp(SP()), T_Binop(T_plus, T_Temp(SP()), T_Const(F_wordSize))));
}


/**********************************************************/
/* CONVERSION BETWEEN ABSTRACT SYNTAX BINOPS TO IR BINOPS */
/**********************************************************/
T_binOp ConvertAbstractSyntaxBinopsToIRBinops(A_oper abstractSyntaxBinop)
{
	switch (abstractSyntaxBinop) {
	case (A_plusOp) : return T_plus;
	case (A_minusOp) : return T_minus;
	case (A_timesOp) : return T_mul;
	case (A_divideOp) : return T_div;
	case (A_eqOp) : return T_eq;
	case (A_neqOp) : return T_ne;
	case (A_ltOp) : return T_lt;
	case (A_leOp) : return T_le;
	case (A_gtOp) : return T_gt;
	case (A_geOp) : return T_ge;
	case (A_andOp) : return T_and;
	case (A_orOp) : return T_or;
	}
}

T_exp IR_transVarDecInit(S_table venv, S_table tenv, A_dec dec, F_frame frame)
{
	F_access access = F_allocLocal(frame);
	Ty_ty type = SEM_transExp(venv, tenv, dec->u.var.init);

	/******************************/
	/* [0] enter variable to venv */
	/******************************/
	S_enter(venv, dec->u.var.var, (E_enventry)E_VarEntry(type, access));

	/***********************************/
	/* [1] build a move representation */
	/***********************************/
	return T_Move(F_Exp(access, frame), IR_transExp(venv, tenv, dec->u.var.init, frame));
}

T_exp IR_transVarDecNoInit(S_table venv, S_table tenv, A_dec dec, F_frame frame)
{
	F_access access = F_allocLocal(frame);
	Ty_ty type = (Ty_ty)S_look(tenv, dec->u.var.typ);

	/******************************/
	/* [0] enter variable to venv */
	/******************************/
	S_enter(venv, dec->u.var.var, (E_enventry)E_VarEntry(type, access));

	/****************************/
	/* [1] nothing to be done.. */
	/****************************/
	return NULL;
}

T_exp IR_transVarDec(S_table venv, S_table tenv, A_dec dec, F_frame frame)
{
	/*************************************/
	/* [1] trans var with initialization */
	/*************************************/
	if (dec->u.var.init != NULL)
	{
		return IR_transVarDecInit(venv, tenv, dec, frame);
	}

	/****************************************/
	/* [2] trans var without initialization */
	/****************************************/
	if (dec->u.var.init == NULL)
	{
		return IR_transVarDecNoInit(venv, tenv, dec, frame);
	}
}

void IR_transNameTypeDec(S_table venv, S_table tenv, A_dec dec)
{
	S_enter(tenv, dec->u.type->name, (Ty_ty)S_look(tenv, dec->u.type->ty->u.name));
}

void IR_transArrayTypeDec(S_table venv, S_table tenv, A_dec dec)
{
	S_enter(tenv, dec->u.type->name, Ty_Array((Ty_ty)S_look(tenv, dec->u.type->ty->u.array)));
}

void IR_transRecordTypeDec(S_table venv, S_table tenv, A_dec dec)
{
	Ty_field fieldType;
	Ty_fieldList fieldsTypesList = NULL;
	A_fieldList fields = dec->u.type->ty->u.record;

	/*************************/
	/* scan fields in record */
	/*************************/
	for (fields = dec->u.type->ty->u.record; fields != NULL; fields = fields->tail)
	{
		fieldType = Ty_Field(fields->head->name, (Ty_ty)S_look(tenv, fields->head->typ));
		fieldsTypesList = Ty_FieldList(fieldType, fieldsTypesList);
	}

	/*********************/
	/* enter record type */
	/*********************/
	S_enter(tenv, dec->u.type->name, Ty_Record(fieldsTypesList));
}

T_exp IR_transTypeDec(S_table venv, S_table tenv, A_dec dec)
{
	/********************************************************/
	/* [0] scan the declaration for simple, array or record */
	/********************************************************/
	switch (dec->u.type->ty->kind) {
	case (A_nameTy) : IR_transNameTypeDec(venv, tenv, dec); break;
	case (A_arrayTy) : IR_transArrayTypeDec(venv, tenv, dec); break;
	case (A_recordTy) : IR_transRecordTypeDec(venv, tenv, dec); break;
	}

	/***************************************************/
	/* [1] no translated IR code for type declarations */
	/***************************************************/
	return NULL;
}

T_exp IR_transFuncDec(S_table venv, S_table tenv, A_dec dec)
{
	T_exp body;
	F_frame frame;
	T_exp epilogue;
	T_exp prologue;
	T_exp sp = T_Temp(SP());
	T_exp fp = T_Temp(FP());
	T_exp ra = T_Temp(RA());
	int numParameters = 0;
	T_exp store_return_address;
	T_exp update_new_frame_pointer;
	T_exp update_new_stack_pointer;
	T_exp save_previous_frame_pointer;
	T_exp restore_previous_frame_pointer;
	T_exp restore_previous_stack_pointer;
	T_exp jump_back_to_return_address;
	T_exp load_return_address;
	F_accessList formals = NULL;
	Temp_temp temp = Temp_newtemp("");
	A_fundec fundec = dec->u.function;
	A_fieldList functionParameters = fundec->params;
	Temp_label skipThisFunctionForNow = Temp_newlabel("Skip_This_Function_For_Now");

	/*******************************************/
	/* [0] Create a new label for the function */
	/*******************************************/
	/**********************************************************************************************/
	/* NOTE: since nested functions are allowed, we can not use the function's name for its label */
	/**********************************************************************************************/
	Temp_label functionLabel = Temp_newlabel(S_name(fundec->name));

	/*********************************************/
	/* [1] compute number of incoming parameters */
	/*********************************************/
	for (functionParameters = fundec->params; functionParameters; functionParameters = functionParameters->tail)
	{
		numParameters++;
	}

	/**************************/
	/* [2] Create a new frame */
	/**************************/
	frame = F_newFrame(functionLabel, numParameters);

	/******************************/
	/* [3] enter function to venv */
	/******************************/
	S_enter(venv, dec->u.function->name, E_FunEntry(NULL, NULL, frame));

	/*****************************************/
	/* [4] open a new scope for the function */
	/*****************************************/
	S_beginScope(venv);

	/************************************************/
	/* [5] enter parameters to variable environment */
	/************************************************/
	for (
		formals = frame->formals, functionParameters = fundec->params;
		functionParameters;
	formals = formals->tail, functionParameters = functionParameters->tail)
	{
		S_enter(venv, functionParameters->head->name, E_VarEntry((Ty_ty)S_look(tenv, functionParameters->head->typ), formals->head));
	}

	/**************************************/
	/* [6] trans the body of the function */
	/**************************************/
	body = IR_transExp(venv, tenv, dec->u.function->body, frame);

	/***************************************/
	/* [7] close the scope of the function */
	/***************************************/
	S_endScope(venv);

	/***************************/
	/* [8-11] *** PROLOGUE *** */
	/***************************/

	/************************************/
	/* [8] push return address on stack */
	/************************************/

	store_return_address = T_Seq(
								 T_Move(sp, T_Binop(T_minus, sp, T_Const(F_wordSize))),
								 T_Move(T_Mem(sp), ra));

	/***********************************/
	/* [9] save frame pointer המלך מת */
	/***********************************/

	save_previous_frame_pointer = T_Seq(
										T_Move(sp, T_Binop(T_minus, sp, T_Const(F_wordSize))),
										T_Move(T_Mem(sp), fp));

	/********************************/
	/* [10] fp = sp יחי המלך החדש */
	/********************************/
	update_new_frame_pointer = T_Move(fp, sp);

	/*****************************/
	/* [11] sp = sp - frame size */
	/*****************************/
	update_new_stack_pointer = T_Move(sp, T_Binop(T_minus, sp, T_Const(frame->size)));

	/****************************/
	/* [12-15] *** EPILOGUE *** */
	/****************************/

	/****************************/
	/* [12] restore previous sp */
	/****************************/

	restore_previous_stack_pointer = T_Move(sp, fp);

	/****************************/
	/* [13] restore previous fp */
	/****************************/
	restore_previous_frame_pointer = T_Seq(
											T_Move(fp, T_Mem(sp)),
											T_Move(sp, T_Binop(T_plus, sp, T_Const(F_wordSize))));


	/****************************/
	/* [14] load return address */
	/****************************/
	load_return_address = T_Seq(
								T_Move(ra, T_Mem(sp)),
								T_Move(sp, T_Binop(T_plus, sp, T_Const(F_wordSize))));

	/************************************/
	/* [15] jump back to return address */
	/************************************/
	jump_back_to_return_address = T_JumpRegister(RA());

	/*************************/
	/* [16] prepare prologue */
	/*************************/
	prologue = T_Seq(store_return_address,
						T_Seq(save_previous_frame_pointer,
							T_Seq(update_new_frame_pointer, update_new_stack_pointer)
						)
					);


	/*************************/
	/* [17] prepare epilogue */
	/*************************/
	epilogue = T_Seq(restore_previous_stack_pointer,
					T_Seq(restore_previous_frame_pointer,
						T_Seq(load_return_address, jump_back_to_return_address)
					)
				);


	/***************************************************************************************/
	/* because nested functions are allowed:                                               */
	/*                                                                                     */
	/* [18] this is tricky:                                                                */
	/*                                                                                     */
	/*     [a] write the label of the function                                             */
	/*     [b] generate the code for the function                                          */
	/*                                                                                     */
	/*     however, at the point the PC reaches this code, this function is NOT called, so */
	/*                                                                                     */
	/*     [c] add a jump instruction before, to skip the execution of this code           */
	/*     [d] add a label to know where to jump to                                        */
	/*                                                                                     */
	/***************************************************************************************/
	return
		T_Seq(
				T_JumpLabel(skipThisFunctionForNow),
					T_Seq(T_Function(prologue, body, epilogue, functionLabel),
						T_Label(skipThisFunctionForNow)
					)
			 );
}

T_exp IR_transDecs(S_table venv, S_table tenv, A_decList decList, F_frame frame)
{
	T_exp t = NULL;

	/*************************************************/
	/* [0] if there are no declarations - do nothing */
	/*************************************************/
	if (decList == NULL) return NULL;

	/**************************/
	/* [1] trans dec the head */
	/**************************/
	switch (decList->head->kind) {
	case (A_varDec) : t = IR_transVarDec(venv, tenv, decList->head, frame); break;
	case (A_typeDec) : t = IR_transTypeDec(venv, tenv, decList->head);       break;
	case (A_functionDec) : t = IR_transFuncDec(venv, tenv, decList->head);       break;
	}

	/**************************/
	/* [2] trans dec the tail */
	/**************************/
	return T_Seq(t, IR_transDecs(venv, tenv, decList->tail, frame));
}

T_exp IR_transSeqExp(S_table venv, S_table tenv, A_exp exp, F_frame frame)
{
	T_exp t = NULL;
	A_expList expList = exp->u.seq;

	while (expList != NULL)
	{
		/**********************/
		/* [1] Trans the head */
		/**********************/
		t = T_Seq(t, IR_transExp(venv, tenv, expList->head, frame));

		/**********************/
		/* [2] Trans the tail */
		/**********************/
		expList = expList->tail;
	}

	return t;
}

T_exp IR_transLetExp(S_table venv, S_table tenv, A_exp exp, F_frame frame)
{
	T_exp t1;
	T_exp t2;

	/*************************************************/
	/* [0] open a new variable and type environments */
	/*************************************************/
	S_beginScope(venv);
	S_beginScope(tenv);

	/***********************************/
	/* [1] trans the declarations part */
	/***********************************/
	t1 = IR_transDecs(venv, tenv, exp->u.let.decs, frame);

	/**********************************/
	/* [2] trans the expressions part */
	/**********************************/
	t2 = IR_transExp(venv, tenv, exp->u.let.body, frame);

	/****************************************************/
	/* [3] close the new variable and type environments */
	/****************************************************/
	S_endScope(venv);
	S_endScope(tenv);

	/***********************************************************************************/
	/* [4] build seq expression for possible initializations done in declarations part */
	/***********************************************************************************/
	return T_Seq(t1, t2);
}

T_exp IR_transOpExp(S_table venv, S_table tenv, A_exp exp, F_frame frame)
{
	T_exp left;
	T_exp right;

	Temp_temp temp = Temp_newtemp("");

	Temp_label T = Temp_newlabel("T");
	Temp_label F = Temp_newlabel("F");
	Temp_label END = Temp_newlabel("END");

	T_binOp op = ConvertAbstractSyntaxBinopsToIRBinops(exp->u.op.oper);

	/******************************/
	/* [0] trans the left operand */
	/******************************/
	left = IR_transExp(venv, tenv, exp->u.op.left, frame);

	/*******************************/
	/* [1] trans the right operand */
	/*******************************/
	right = IR_transExp(venv, tenv, exp->u.op.right, frame);

	/****************************/
	/* [2] return op expression */
	/****************************/
	switch (exp->u.op.oper)
	{
	case (A_orOp) :
	case (A_andOp) :
	case (A_plusOp) :
	case (A_minusOp) :
	case (A_timesOp) :
	case (A_divideOp) :

					  /********************/
					  /* binary operation */
					  /********************/
					  return T_Binop(op, left, right);

	case (A_eqOp) :
	case (A_ltOp) :
	case (A_leOp) :
	case (A_gtOp) :
	case (A_geOp) :
	case (A_neqOp) :

				   /*******************/
				   /* binary relation */
				   /*******************/
				   return T_Seq(
				   T_Seq(
				   T_Cjump(op, left, right, T, F),
				   T_Seq(
				   T_Seq(
				   T_Label(T),
				   T_Seq(
				   T_Move(T_Temp(temp), T_Const(1)),
				   T_JumpLabel(END))),
				   T_Seq(
				   T_Label(F),
				   T_Seq(
				   T_Move(T_Temp(temp), T_Const(0)),
				   T_JumpLabel(END))))),
				   T_Seq(T_Label(END), T_Temp(temp)));

	}
}

T_exp IR_transIntExp(S_table venv, S_table tenv, A_exp exp)
{
	return T_Const(exp->u.intt);
}

T_exp IR_transFloatExp(S_table venv, S_table tenv, A_exp exp)
{
	return T_Const(exp->u.intt);
}

struct expty IR_transVarExp(S_table venv, S_table tenv, A_var var, F_frame frame)
{
	Ty_ty type;
	struct expty e;
	int fieldOffset = 0;
	E_enventry envEntry;
	Ty_fieldList fieldList;

	switch (var->kind) {
	case (A_simpleVar) :

		/*********************************/
		/* for example,                  */
		/*                               */
		/* type salary = int             */
		/*                               */
		/* salary mySalary := 80         */
		/*                               */
		/* mySalary is a simple variable */
		/*********************************/

		/**********************/
		/* [0] find var entry */
		/**********************/
		envEntry = (E_enventry)S_look(venv, var->u.simple);

		/*****************/
		/* [1] build exp */
		/*****************/
		e.exp = F_Exp(envEntry->u.var.access, frame);
		e.ty = envEntry->u.var.type;

		/**************/
		/* [2] return */
		/**************/
		return e;

	case (A_fieldVar) :

		/***************************************************************/
		/* for example,                                                */
		/*                                                             */
		/* type salary = int                                           */
		/* type date = {year:int, month:int, day:int, time:float}      */
		/* type employee = {mySalary:salary, startWorking:date}        */
		/*                                                             */
		/* employee oren                                               */
		/*                                                             */
		/* oren->startWorking->time = 23.54 (6 minutes before 24.00)   */
		/*                                                             */
		/* the recursive call will be with variable oren->startWorking */
		/*                                                             */
		/* the following documentation uses [RECORD]->field            */
		/*                                                             */
		/* and in this example: RECORD is oren->startWorking           */
		/*                      field  is time                         */
		/***************************************************************/

		/********************/
		/* [0] trans RECORD */
		/********************/
		e = IR_transVarExp(venv, tenv, var->u.field.var, frame);

		/**************************************************************************************/
		/* [1] build exp: take address of record and add the shift needed for current field   */
		/*                                                                                    */
		/* in the example above, take the address of oren->startWorking and add 3*sizeof(int) */
		/*                                                                                    */
		/**************************************************************************************/

		/*************************/
		/* [1a] read record type */
		/*************************/
		type = e.ty;

		/*********************************/
		/* [1b] find field in field list */
		/*********************************/
		for (fieldList = type->u.record; fieldList != NULL; fieldList = fieldList->tail, fieldOffset++)
		{
			if (var->u.field.sym == fieldList->head->name)
			{
				break;
			}
		}

		/******************************/
		/* [1c] compute actual offset */
		/******************************/
		e.exp = T_Mem(T_Binop(T_plus, e.exp, T_Const(fieldOffset * F_wordSize)));
		e.ty = fieldList->head->ty;

		/**************/
		/* [2] return */
		/**************/
		return e;

	case (A_subscriptVar) :

		/*******************/
		/* [0] trans ARRAY */
		/*******************/
		e = IR_transVarExp(venv, tenv, var->u.subscript.var, frame);

		/*****************************/
		/* [1] compute actual offset */
		/*****************************/
		e.exp =
			T_Mem(
			T_Binop(T_plus,
			T_Binop(T_mul,
			IR_transExp(venv, tenv, var->u.subscript.exp, frame),
			T_Const(F_wordSize)),
			e.exp));

		e.ty = e.ty->u.array;

		/**************/
		/* [2] return */
		/**************/
		return e;
	}
}

T_exp IR_transAssignExp(S_table venv, S_table tenv, A_exp exp, F_frame frame)
{
	T_exp t;

	struct expty e;

	/************************/
	/* [1] trans expression */
	/************************/
	t = IR_transExp(venv, tenv, exp->u.assign.exp, frame);

	/**********************/
	/* [2] trans variable */
	/**********************/
	e = IR_transVarExp(venv, tenv, exp->u.var, frame);

	/*********************/
	/* [3] move t1 to t2 */
	/*********************/
	return T_Move(e.exp, t);
}

T_exp IR_transForExp(S_table venv, S_table tenv, A_exp exp, F_frame frame)
{
	T_exp one;

	T_exp low;
	T_exp low_;
	T_exp high;
	T_exp high_;
	T_exp body;

	T_exp localLoopVariable;
	T_exp localLoopVariable_;
	T_exp localLoopVariable__;
	T_exp localLoopVariable___;
	T_exp localLoopVariable_plus_1;
	T_exp localLoopVariable_plus_plus;
	T_exp localLoopVariable_equals_low;

	/****************************************/
	/* [0] create start and end loop labels */
	/****************************************/
	Temp_label loop = Temp_newlabel("for_loop");
	Temp_label exitLoop = Temp_newlabel("exit_loop");
	Temp_label forCheck = Temp_newlabel("for_check");

	/************************************/
	/* [1] allocate local loop variable */
	/************************************/
	F_access access = F_allocLocal(frame);

	/*****************************************/
	/* [2] enter local loop variable to venv */
	/*****************************************/
	S_enter(venv, exp->u.forr.var, E_VarEntry(NULL, access));

	/*************************************/
	/* [3] trans lower bound of for loop */
	/*************************************/
	low = IR_transExp(venv, tenv, exp->u.forr.lo, frame);
	low_ = IR_transExp(venv, tenv, exp->u.forr.lo, frame);

	/*************************************/
	/* [4] trans upper bound of for loop */
	/*************************************/
	high = IR_transExp(venv, tenv, exp->u.forr.hi, frame);
	high_ = IR_transExp(venv, tenv, exp->u.forr.hi, frame);

	/******************************/
	/* [5] trans body of for loop */
	/******************************/
	body = IR_transExp(venv, tenv, exp->u.forr.body, frame);

	/******************************************************/
	/* [6] create IR building blocks for "for" expression */
	/******************************************************/
	one = T_Const(1);
	localLoopVariable = F_Exp(access, frame);
	localLoopVariable_ = F_Exp(access, frame);
	localLoopVariable__ = F_Exp(access, frame);
	localLoopVariable___ = F_Exp(access, frame);
	localLoopVariable_equals_low = T_Move(localLoopVariable_, low);
	localLoopVariable_plus_1 = T_Binop(T_plus, localLoopVariable__, one);
	localLoopVariable_plus_plus = T_Move(localLoopVariable___, localLoopVariable_plus_1);

	/*************************************************/
	/* [7] build IR "for" expression from its blocks */
	/*************************************************/
	//return T_Const(0);

	return T_Seq(
		T_Seq(localLoopVariable_equals_low,
		T_Seq(T_Label(forCheck),
		T_Seq(T_Cjump(T_le, localLoopVariable, high, loop, exitLoop),
		T_Seq(T_Label(loop),
		T_Seq(body,
		T_Seq(localLoopVariable_plus_plus,
		T_JumpLabel(forCheck)
		)
		)
		)
		)
		)
		),
		T_Label(exitLoop)
		);
}

T_exp IR_transIfExp(S_table venv, S_table tenv, A_exp exp, F_frame frame)
{
	T_exp testExpression;
	T_exp thenExpression;
	Temp_label jumpToHereIfTrue = Temp_newlabel("if_taken");
	Temp_label jumpToHereIfFalse = Temp_newlabel("if_not_taken");

	/********************************/
	/* [1] build IR test expression */
	/********************************/
	testExpression = IR_transExp(venv, tenv, exp->u.iff.test, frame);

	/****************************************/
	/* [2] build IR do_something expression */
	/****************************************/
	thenExpression = IR_transExp(venv, tenv, exp->u.iff.then, frame);

	/*******************************/
	/* [3] return IR if expression */
	/*******************************/
	return
		T_Seq(
		T_Seq(
		T_Cjump(
		T_ne,
		testExpression,
		T_Const(0),
		jumpToHereIfTrue,
		jumpToHereIfFalse),
		T_Seq(
		T_Label(jumpToHereIfTrue),
		thenExpression)),
		T_Label(jumpToHereIfFalse));

}

T_exp IR_transCallExp(S_table venv, S_table tenv, A_exp exp, F_frame frame)
{
	T_exp t = NULL;
	A_expList args = NULL;
	E_enventry envEntry = NULL;
	T_expList expListPtr = T_ExpList(NULL, NULL);
	T_expList expList = NULL;
	Temp_label functionLabel = NULL;

	/******************************/
	/* [0] extract function label */
	/******************************/
	envEntry = (E_enventry)S_look(venv, exp->u.call.func);
	functionLabel = envEntry->u.fun.frame->label;

	/*******************************/
	/* [1] translate each argument */
	/*******************************/
	for (args = exp->u.call.args; args != NULL; args = args->tail)
	{
		expList = T_ExpList(IR_transExp(venv, tenv, args->head, frame), expList);
	}

	/*******************************/
	/* [2] build a call expression */
	/*******************************/
	return T_Call(functionLabel, expList);
}

T_exp IR_transAllocteRecordExp(S_table venv, S_table tenv, A_exp exp, F_frame frame)
{
	A_expList initExpList;
	T_expList expList = NULL;
	int elementCounter = 0;


	for (initExpList = exp->u.recordInit.initExpList; initExpList; initExpList = initExpList->tail)
	{
		elementCounter++;
	}

	expList = T_ExpList(T_Const(elementCounter * 4), expList);  // element counter is the num of parameters, so to get the overall number of bytes
																// neccessery, we'll multiply that number by 4 (x params * 4 bytes each = overall bytes)

	for (initExpList = exp->u.recordInit.initExpList; initExpList; initExpList = initExpList->tail)
	{
		expList = T_ExpList(IR_transExp(venv, tenv, initExpList->head, frame), expList);
	}

	return F_externalCall("AllocateRecord", expList);
}

T_exp IR_transAllocteArrayExp(S_table venv, S_table tenv, A_exp exp)
{
	T_expList expList = NULL;
	int elementCounter = exp->u.arrayInit.size;
	int initalizeValue = exp->u.arrayInit.initalized_value;

	expList = T_ExpList(T_Const(elementCounter * 4), NULL);

	for (int i = 0; i < elementCounter; i++){
		expList = T_ExpList(T_Const(initalizeValue), expList);
	}

	return F_externalCall("AllocateArray", expList);
}

/****************/
/* IR_transExp */
/****************/
T_exp IR_transExp(S_table venv, S_table tenv, A_exp exp, F_frame frame)
{
	struct expty e;

	switch (exp->kind) {
	case (A_opExp) : return IR_transOpExp(venv, tenv, exp, frame);
	case (A_ifExp) : return IR_transIfExp(venv, tenv, exp, frame);
	case (A_forExp) : return IR_transForExp(venv, tenv, exp, frame);
	case (A_letExp) : return IR_transLetExp(venv, tenv, exp, frame);
	case (A_intExp) : return IR_transIntExp(venv, tenv, exp);
	case (A_seqExp) : return IR_transSeqExp(venv, tenv, exp, frame);
	case (A_varExp) : e = IR_transVarExp(venv, tenv, exp->u.var, frame); return e.exp;
	case (A_callExp) : return IR_transCallExp(venv, tenv, exp, frame);
	case (A_floatExp) : return IR_transFloatExp(venv, tenv, exp);
	case (A_assignExp) : return IR_transAssignExp(venv, tenv, exp, frame);
	case (A_allocateArrayExp) : return IR_transAllocteArrayExp(venv, tenv, exp);
	case (A_allocateRecordExp) : return IR_transAllocteRecordExp(venv, tenv, exp, frame);
	}
}

/*****************/
/* IR_transProg */
/*****************/
T_exp IR_transProg(A_exp exp)
{
	F_frame main;
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
	S_enter(baseTypesEnv, S_Symbol("int"), Ty_Int());
	S_enter(baseTypesEnv, S_Symbol("float"), Ty_Float());
	S_enter(baseTypesEnv, S_Symbol("string"), Ty_String());

	/****************************************************/
	/* [2] enter system functions: printFloat, printInt */
	/****************************************************/
	S_enter(baseVariablesEnv, S_Symbol("PrintInt"), E_FunEntry(NULL, NULL, F_newFrame(Temp_newlabel("PrintInt"), 1, NULL)));
	S_enter(baseVariablesEnv, S_Symbol("PrintFloat"), E_FunEntry(NULL, NULL, F_newFrame(Temp_newlabel("PrintFloat"), 1, NULL)));
	S_enter(baseVariablesEnv, S_Symbol("PrintString"), E_FunEntry(NULL, NULL, F_newFrame(Temp_newlabel("PrintString"), 1, NULL)));

	/******************************/
	/* [3] open new frame: "main" */
	/******************************/
	main = F_newFrame(Temp_newlabel("main"), 0, NULL);

	/********************************/
	/* [4] trans the entire program */
	/********************************/
	return IR_transExp(baseVariablesEnv, baseTypesEnv, exp, main);
}
