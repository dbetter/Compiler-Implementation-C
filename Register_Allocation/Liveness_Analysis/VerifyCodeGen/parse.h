#ifndef __PARSE_H__
#define __PARSE_H__

/*****************/
/* INCLUDE FILES */
/*****************/
#include "absyn.h"
#include "util.h"

ABSTRACT_SYNTAX_expList parse(string fname);

extern int yyparse(void);
extern ABSTRACT_SYNTAX_exp absyn_root;

#endif