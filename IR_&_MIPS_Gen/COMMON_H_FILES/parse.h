#ifndef __PARSE_H__
#define __PARSE_H__

/*****************/
/* INCLUDE FILES */
/*****************/
#include "absyn.h"

A_exp parse(string fname);

extern int yyparse(void);
extern A_exp absyn_root;

#endif