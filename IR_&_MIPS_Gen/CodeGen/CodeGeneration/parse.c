/***********/
/* parse.c */
/***********/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "../../COMMON_H_FILES/parse.h"
#include "../../COMMON_H_FILES/symbol.h"
#include "../../COMMON_H_FILES/util.h"
#include "../../COMMON_H_FILES/absyn.h"
#include "../../COMMON_H_FILES/errormsg.h"

/*********/
/* parse */
/*********/
A_exp parse(string fname) 
{
	EM_reset(fname);
	if (yyparse() == 0)
	{
		/******************/
		/* parsing worked */
		/******************/
		return absyn_root;
	}
	else
	{
		return NULL;
	}
}
