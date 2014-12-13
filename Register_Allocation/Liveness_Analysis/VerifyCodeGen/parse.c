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
#include "parse.h"
#include "util.h"
#include "absyn.h"
#include "errormsg.h"

/*********/
/* parse */
/*********/
ABSTRACT_SYNTAX_expList parse(string fname) 
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
