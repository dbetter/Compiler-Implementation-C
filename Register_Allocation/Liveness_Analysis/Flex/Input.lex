%{
#include <string.h>
#include <math.h>
#include "../VerifyCodeGen/util.h"
#include "../VerifyCodeGen/errormsg.h"
#include "../Bison/tiger.tab.h"
int charPos=1;

int yywrap(void)
{
 charPos=1;
 return 1;
}


void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}

%}

%%
" "									{adjust(); continue;}
\t									{adjust(); continue;}
\n									{adjust(); EM_newline(); continue;}
syscall								{adjust(); continue;}
","									{adjust(); return COMMA;}
":"									{adjust(); return COLON;}
lw									{adjust(); return LOAD;}
sw									{adjust(); return STORE;}
li									{adjust(); return LOAD_IMMEDIATE;}
j									{adjust(); return JUMP;}
jr									{adjust(); return JUMP;}
jal									{adjust(); return JUMP_AND_LINK;}
add									{adjust(); return ADD;}
addi								{adjust(); return ADD_IMMEDIATE;}
sub									{adjust(); return SUB;}
mul									{adjust(); return MUL;}
mov									{adjust(); return MOVE;}
beq									{adjust(); return BEQ;}
bne									{adjust(); return BNE;}
bgt									{adjust(); return BGT;}
bge									{adjust(); return BGE;}
blt									{adjust(); return BLT;}
ble									{adjust(); return BLE;}
"$"[a-zA-Z]+[0-9a-zA-Z]+			{adjust(); yylval.xval.gval.sval=String(yytext+1); return REGISTER;}
"("									{adjust(); return LPAREN;}
")"									{adjust(); return RPAREN;}
"+"									{adjust(); return PLUS;}
"-"									{adjust(); return MINUS;}
Temp_[0-9]+[0-9]*					{adjust(); yylval.xval.gval.sval=String(yytext); return TEMP;}
[0-9]+[0-9]*						{adjust(); yylval.xval.gval.ival=atoi(yytext); return INT;}
"-"[0-9]+[0-9]*						{adjust(); yylval.xval.gval.ival=atoi(yytext); return INT;}
[a-zA-Z_]+[0-9a-zA-Z_]*				{adjust(); yylval.xval.gval.sval=String(yytext); return LABEL;}
\"[0-9a-zA-Z ]*\"					{adjust(); yylval.xval.gval.sval=String(yytext); return STRING;}
[0-9]+"."[0-9]*						{adjust(); yylval.xval.gval.fval=atof(yytext); return FLOAT;}
"."[0-9]+							{adjust(); yylval.xval.gval.fval=atof(yytext); return FLOAT;}
@									{adjust(); EM_error(EM_tokPos,"illegal token");}
