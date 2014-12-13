/****************************/
/* FILE NAEM: ABSYN_Print.c */
/****************************/

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

/********************/
/* GLOBAL VARIABLES */
/********************/
static FILE *fl;

/***********************/
/* FUNCTION PROTOTYPES */
/***********************/
void ABSYN_PrintTreeRecursively(A_exp ABSYN_Tree);

void ABSYN_PrintVar(A_var var)
{

}

void ABSYN_PrintVarDec(A_dec dec)
{
	/*******************************/
	/* Print my serial node number */
	/*******************************/
	fprintf(fl,"v%d ",dec->PrintMyNodeSerialNumber);

	if (dec->u.var.init == NULL)
	{
		/********************************************/
		/* VariableDeclaration ---> VAR ID COLON ID */
		/********************************************/
		fprintf(fl,"[label = \"%s%s:%s\"];\n","Variable\nDeclaration\n",S_name(dec->u.var.var),S_name(dec->u.var.typ));
		return;
	}

	if (dec->u.var.typ == NULL)
	{
		/**********************************************/
		/* VariableDeclaration ---> VAR ID ASSIGN exp */
		/**********************************************/
		fprintf(fl,"[label = \"%s(%s)\"];\n","Variable\nDeclaration\n",S_name(dec->u.var.var));
		//fprintf(fl,"v%d -> v%d;\n",fieldList->PrintMyNodeSerialNumber,fieldList->head->PrintMyNodeSerialNumber);
		ABSYN_PrintTreeRecursively(dec->u.var.init);
		return;
	}

	/*******************************************************/
	/* VariableDeclaration ---> VAR ID COLON ID ASSIGN exp */
	/*******************************************************/
	fprintf(fl,"[label = \"%s(%s:%s)\"];\n","Variable\nDeclaration\n\n",S_name(dec->u.var.var),S_name(dec->u.var.typ));
	//fprintf(fl,"v%d -> v%d;\n",fieldList->PrintMyNodeSerialNumber,fieldList->head->PrintMyNodeSerialNumber);
	ABSYN_PrintTreeRecursively(dec->u.var.init);
	return;
}

void ABSYN_PrintFieldsDecRecursively(A_fieldList fieldList)
{
	/*******************************/
	/* Print my serial node number */
	/*******************************/
	fprintf(fl,"v%d ",fieldList->PrintMyNodeSerialNumber);

	/*****************/
	/* Print content */
	/*****************/
	fprintf(fl,"[label = \"%s\"];\n",fieldList->PrintTheKindOfTreeIAm);

	/*********************/
	/* Print first field */
	/*********************/
	fprintf(fl,"v%d -> v%d;\n",fieldList->PrintMyNodeSerialNumber,fieldList->head->PrintMyNodeSerialNumber);

	/*********************/
	/* Print first field */
	/*********************/
	fprintf(fl,"v%d ",fieldList->head->PrintMyNodeSerialNumber);

	/*****************/
	/* Print content */
	/*****************/
	fprintf(fl,"[label = \"%s:%s\"];\n",S_name(fieldList->head->name),S_name(fieldList->head->typ));

	/********************************/
	/* Print the rest of the fields */
	/********************************/
	if (fieldList->tail != NULL)
	{
		fprintf(fl,"v%d -> v%d;\n",fieldList->PrintMyNodeSerialNumber,fieldList->tail->PrintMyNodeSerialNumber);
		ABSYN_PrintFieldsDecRecursively(fieldList->tail);
	}
}
void ABSYN_PrintTypeDec(A_dec dec)
{
	switch (dec->u.type->ty->kind) {
	case (A_nameTy):
		
		fprintf(fl,"[label = \"%s%s = %s\"];\n","Type\nDeclaration\n\n",S_name(dec->u.type->name),S_name(dec->u.type->ty->u.name));
		break;

	case (A_arrayTy):
		
		fprintf(fl,"[label = \"%s%s = %s\"];\n","Type\nDeclaration\n\n",S_name(dec->u.type->name),S_name(dec->u.type->ty->u.array));
		break;

	case (A_recordTy):
		
		fprintf(fl,"[label = \"%s%s = \"];\n","Type\nDeclaration\n\n",S_name(dec->u.type->name));
		ABSYN_PrintFieldsDecRecursively(dec->u.type->ty->u.record);
		break;
	}
}

void ABSYN_PrintFunDec(A_dec dec)
{
	/*****************/
	/* Print content */
	/*****************/
	fprintf(fl,"[label = \"%s(%s)\"];\n","Function\nDeclaration\n",S_name(dec->u.function->name));
	
	/****************/
	/* Print params */
	/****************/
	fprintf(fl,"v%d -> v%d;\n",dec->PrintMyNodeSerialNumber,dec->u.function->params->PrintMyNodeSerialNumber);
	ABSYN_PrintFieldsDecRecursively(dec->u.function->params);

	/**************/
	/* Print body */
	/**************/
	fprintf(fl,"v%d -> v%d;\n",dec->PrintMyNodeSerialNumber,dec->u.function->body->PrintMyNodeSerialNumber);
	ABSYN_PrintTreeRecursively(dec->u.function->body);
}

void ABSYN_PrintDec(A_dec dec)
{
	/***********************************/
	/* [1] Print my serial node number */
	/***********************************/
	fprintf(fl,"v%d ",dec->PrintMyNodeSerialNumber);

	/*************************/
	/* [2] Print declaration */
	/*************************/
	switch (dec->kind) {
	case (A_varDec):      ABSYN_PrintVarDec( dec); break;
	case (A_typeDec):     ABSYN_PrintTypeDec(dec); break;
	case (A_functionDec): ABSYN_PrintFunDec( dec); break;
	}
}

void ABSYN_PrintTreeRecursively(A_exp ABSYN_Tree)
{
	A_expList expList;
	A_expList argumentsList;
	A_decList declarationList;

	/*****************/
	/* [0] Oh well.. */
	/*****************/
	if (ABSYN_Tree == NULL) return;

	/***********************************/
	/* [1] Print my serial node number */
	/***********************************/
	fprintf(fl,"v%d ",ABSYN_Tree->PrintMyNodeSerialNumber);

	/***************************/
	/* [2] Print my node label */
	/***************************/
	fprintf(fl,"[label = \"%s\"];\n",ABSYN_Tree->PrintTheKindOfTreeIAm);

	/***********************************************/
	/* [3] Print the remaining subtree recursively */
	/***********************************************/
	switch (ABSYN_Tree->kind) {

	case (A_seqExp):

		for (expList = ABSYN_Tree->u.seq; expList; expList = expList->tail)
		{
			fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,expList->head->PrintMyNodeSerialNumber);
		}

		for (expList = ABSYN_Tree->u.seq; expList; expList = expList->tail)
		{
			ABSYN_PrintTreeRecursively(expList->head);
		}

		break;

	case (A_callExp):

		for (argumentsList = ABSYN_Tree->u.call.args; argumentsList; argumentsList = argumentsList->tail)
		{
			fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,argumentsList->head->PrintMyNodeSerialNumber);
		}

		for (argumentsList = ABSYN_Tree->u.call.args; argumentsList; argumentsList = argumentsList->tail)
		{
			ABSYN_PrintTreeRecursively(argumentsList->head);
		}

		break;

	case (A_opExp):

		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.op.left->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.op.right->PrintMyNodeSerialNumber);

		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.op.left);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.op.right);
		break;

	case (A_ifExp):

		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.iff.test->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.iff.then->PrintMyNodeSerialNumber);

		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.iff.test);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.iff.then);
		break;

	case (A_whileExp):

		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.whilee.test->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.whilee.body->PrintMyNodeSerialNumber);

		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.whilee.test);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.whilee.body);
		break;

	case (A_forExp):

		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.forr.lo->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.forr.hi->PrintMyNodeSerialNumber);
		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.forr.body->PrintMyNodeSerialNumber);

		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.forr.lo);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.forr.hi);
		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.forr.body);
		break;

	case (A_letExp):

		for (declarationList = ABSYN_Tree->u.let.decs; declarationList; declarationList = declarationList->tail)
		{
			fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,declarationList->head->PrintMyNodeSerialNumber);
		}

		fprintf(fl,"v%d -> v%d;\n",ABSYN_Tree->PrintMyNodeSerialNumber,ABSYN_Tree->u.let.body->PrintMyNodeSerialNumber);

		for (declarationList = ABSYN_Tree->u.let.decs; declarationList; declarationList = declarationList->tail)
		{
			ABSYN_PrintDec(declarationList->head);
		}

		ABSYN_PrintTreeRecursively(ABSYN_Tree->u.let.body);
		break;
	}
}

void ABSYN_PrintTreeInit(const char *filename)
{
	fl=fopen(filename,"w+t");
	if (fl == NULL) return;

	fprintf(fl,"digraph\n");
	fprintf(fl,"{\n");
	fprintf(fl,"graph [ordering = \"out\"]\n");
}

void ABSYN_PrintTreeEnd(void)
{
	fprintf(fl,"\n}");
	fclose(fl);
}

void ABSYN_PrintTree(A_exp ABSYN_tree,const char *filename)
{
	/************/
	/* [1] Init */
	/************/
	ABSYN_PrintTreeInit(filename);

	/******************************/
	/* [2] Print Tree Recursively */
	/******************************/
	ABSYN_PrintTreeRecursively(ABSYN_tree);

	/***********/
	/* [3] End */
	/***********/
	ABSYN_PrintTreeEnd();
}
