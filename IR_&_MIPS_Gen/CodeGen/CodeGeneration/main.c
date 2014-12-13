/**********/
/* main.c */
/**********/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "asm.h"
#include "../../COMMON_H_FILES/IR.h"
#include "../../COMMON_H_FILES/util.h"
#include "../../COMMON_H_FILES/tree.h"
#include "../../COMMON_H_FILES/symbol.h"
#include "../../COMMON_H_FILES/semant.h"
#include "../../COMMON_H_FILES/absyn.h"
#include "../../COMMON_H_FILES/errormsg.h"
#include "../../COMMON_H_FILES/parse.h"

/********/
/* main */
/********/
int main(int argc,char **argv)
{
	T_exp IR_tree = NULL;
	char *filename=argv[1];
	A_exp AbstractSyntaxTree=NULL;


	/**********************************/
	/* [1] Build Abstract Syntax Tree */
	/**********************************/
	AbstractSyntaxTree = parse(filename);
	if (AbstractSyntaxTree == NULL) return 0;
	ABSYN_PrintTree(AbstractSyntaxTree,"ABSYN_Graph.txt");

	/*************************/
	/* [2] Semantic Analysis */
	/*************************/
	SEM_transProg(AbstractSyntaxTree);

	/***********************************/
	/* [3] Intermediate Representation */
	/***********************************/
	IR_tree = IR_transProg(AbstractSyntaxTree);
	IR_PrintTree(IR_tree,"IR_Graph.txt");

	/***********************/
	/* [4] Code Generation */
	/***********************/

	MIPS_ASM_CodeGeneration(IR_tree, "tiger_prog.s");

	/*************************/
	/* [5] Liveness Analysis */
	/*************************/

	/***************************/
	/* [6] Register Allocation */
	/***************************/
}
