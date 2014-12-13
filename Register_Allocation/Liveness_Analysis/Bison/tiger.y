%{
#include <stdio.h>
#include "../VerifyCodeGen/util.h"
#include "../VerifyCodeGen/absyn.h"
#include "../VerifyCodeGen/errormsg.h"

int yylex(void); /* function prototype */

int numArguments=1;
int numParameters=1;

ABSTRACT_SYNTAX_expList absyn_root;

void yyerror(char *s)
{
 EM_error(EM_tokPos, "%s", s);
}
%}


%union
{
	int						ival;
	float					fval;
	string					sval;
	ABSTRACT_SYNTAX_exp		exp;
	ABSTRACT_SYNTAX_expList	expList;

	struct
	{
		union
		{
			int						ival;
			float					fval;
			string					sval;
			ABSTRACT_SYNTAX_exp		exp;
			ABSTRACT_SYNTAX_expList	expList;
		}
		gval;
		
		int type;
	}
	xval;
}

%token <xval> INT
%token <xval> FLOAT
%token <xval> STRING
%token <xval> ID
%token <xval> LABEL
%token <xval> COMMA
%token <xval> COLON
%token <xval> LOAD
%token <xval> STORE
%token <xval> LOAD_IMMEDIATE
%token <xval> ADD_IMMEDIATE
%token <xval> JUMP
%token <xval> JUMP_AND_LINK
%token <xval> LPAREN
%token <xval> RPAREN
%token <xval> PLUS
%token <xval> MINUS
%token <xval> ADD
%token <xval> SUB
%token <xval> MUL
%token <xval> TEMP
%token <xval> BEQ
%token <xval> BNE
%token <xval> BLT
%token <xval> BLE
%token <xval> BGT
%token <xval> BGE
%token <xval> REGISTER
%token <xval> AND
%token <xval> OR
%token <xval> MOVE

%type <xval> exp
%type <xval> expList
%type <xval> labelExp
%type <xval> jumpExp	
%type <xval> cjumpExp	
%type <xval> loadExp	
%type <xval> storeExp	
%type <xval> binopExp	
%type <xval> movExp	
%type <xval> var
%type <xval> program

%start program

%%

program:				expList								{absyn_root = $1.gval.expList;}

expList:				exp	expList							{$$.gval.expList = ABSTRACT_SYNTAX_ExpList($1.gval.exp,$2.gval.expList);}
						| exp								{$$.gval.expList = ABSTRACT_SYNTAX_ExpList($1.gval.exp,NULL);}

exp:					labelExp							{$$.gval.exp = $1.gval.exp;}
						| jumpExp							{$$.gval.exp = $1.gval.exp;}
						| cjumpExp							{$$.gval.exp = $1.gval.exp;}
						| loadExp							{$$.gval.exp = $1.gval.exp;}
						| storeExp							{$$.gval.exp = $1.gval.exp;}
						| binopExp							{$$.gval.exp = $1.gval.exp;}
						| movExp							{$$.gval.exp = $1.gval.exp;}

labelExp:				LABEL COLON							{$$.gval.exp = ABSTRACT_SYNTAX_LABEL($1.gval.sval);}

jumpExp:				JUMP LABEL							{$$.gval.exp = ABSTRACT_SYNTAX_JUMP($2.gval.sval);}
						| JUMP REGISTER						{$$.gval.exp = ABSTRACT_SYNTAX_JUMP_REGISTER($2.gval.sval);}
						| JUMP_AND_LINK LABEL				{$$.gval.exp = ABSTRACT_SYNTAX_JUMP_AND_LINK($2.gval.sval);}

cjumpExp:				BEQ var COMMA var COMMA LABEL		{$$.gval.exp = ABSTRACT_SYNTAX_BEQ( $2.gval.sval,$4.gval.sval,$6.gval.sval );}
						| BNE var COMMA var COMMA LABEL		{$$.gval.exp = ABSTRACT_SYNTAX_BNE( $2.gval.sval,$4.gval.sval,$6.gval.sval );}
						| BGT TEMP COMMA TEMP COMMA LABEL	{$$.gval.exp = ABSTRACT_SYNTAX_BGT( $2.gval.sval,$4.gval.sval,$6.gval.sval );}
						| BGT REGISTER COMMA INT COMMA LABEL	{$$.gval.exp = ABSTRACT_SYNTAX_BGT( $2.gval.sval,$4.gval.ival,$6.gval.sval );}
						| BGE TEMP COMMA TEMP COMMA LABEL	{$$.gval.exp = ABSTRACT_SYNTAX_BGE( $2.gval.sval,$4.gval.sval,$6.gval.sval );}
						| BLT TEMP COMMA TEMP COMMA LABEL	{$$.gval.exp = ABSTRACT_SYNTAX_BLT( $2.gval.sval,$4.gval.sval,$6.gval.sval );}
						| BLE TEMP COMMA TEMP COMMA LABEL	{$$.gval.exp = ABSTRACT_SYNTAX_BLE( $2.gval.sval,$4.gval.sval,$6.gval.sval );}

loadExp:				LOAD var COMMA INT LPAREN var RPAREN				{$$.gval.exp = ABSTRACT_SYNTAX_LOAD($2.gval.sval,$6.gval.sval,$4.gval.ival);}
						| LOAD_IMMEDIATE TEMP COMMA INT						{$$.gval.exp = ABSTRACT_SYNTAX_LOAD_IMMEDIATE($2.gval.sval,$4.gval.ival);}
						| LOAD_IMMEDIATE REGISTER COMMA INT					{$$.gval.exp = ABSTRACT_SYNTAX_LOAD_IMMEDIATE($2.gval.sval,$4.gval.ival);}

storeExp:				STORE var COMMA INT LPAREN var RPAREN				{$$.gval.exp = ABSTRACT_SYNTAX_STORE($2.gval.sval,$6.gval.sval,$4.gval.ival);}

binopExp:				ADD var COMMA var COMMA var							{$$.gval.exp = ABSTRACT_SYNTAX_ADD($2.gval.sval,$4.gval.sval,$6.gval.sval);}
						| SUB var COMMA var COMMA TEMP						{$$.gval.exp = ABSTRACT_SYNTAX_SUB($2.gval.sval,$4.gval.sval,$6.gval.sval);}
						| MUL TEMP COMMA TEMP COMMA TEMP					{$$.gval.exp = ABSTRACT_SYNTAX_MUL($2.gval.sval,$4.gval.sval,$6.gval.sval);}
						| ADD_IMMEDIATE REGISTER COMMA REGISTER COMMA INT	{$$.gval.exp = ABSTRACT_SYNTAX_ADD_IMMEDIATE($2.gval.sval,$4.gval.sval,$6.gval.ival);}
						| ADD_IMMEDIATE REGISTER COMMA TEMP COMMA INT		{$$.gval.exp = ABSTRACT_SYNTAX_ADD_IMMEDIATE($2.gval.sval,$4.gval.sval,$6.gval.ival);}
						| ADD_IMMEDIATE TEMP COMMA REGISTER COMMA INT		{$$.gval.exp = ABSTRACT_SYNTAX_ADD_IMMEDIATE($2.gval.sval,$4.gval.sval,$6.gval.ival);}
						| ADD_IMMEDIATE TEMP COMMA TEMP COMMA INT			{$$.gval.exp = ABSTRACT_SYNTAX_ADD_IMMEDIATE($2.gval.sval,$4.gval.sval,$6.gval.ival);}

movExp:					MOVE TEMP COMMA TEMP								{$$.gval.exp = ABSTRACT_SYNTAX_MOVE($2.gval.sval,$4.gval.sval);}
						| MOVE REGISTER COMMA REGISTER						{$$.gval.exp = ABSTRACT_SYNTAX_MOVE($2.gval.sval,$4.gval.sval);}

var:					TEMP												{$$.gval.sval = $1.gval.sval;}
						| REGISTER											{$$.gval.sval = $1.gval.sval;}

%%

	
