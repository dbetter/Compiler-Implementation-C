
/*  A Bison parser, made from tiger.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	INT	258
#define	FLOAT	259
#define	STRING	260
#define	ID	261
#define	COMMA	262
#define	COLON	263
#define	SEMICOLON	264
#define	LPAREN	265
#define	RPAREN	266
#define	LBRACK	267
#define	RBRACK	268
#define	LBRACE	269
#define	RBRACE	270
#define	ARROW	271
#define	PLUS	272
#define	MINUS	273
#define	TIMES	274
#define	DIVIDE	275
#define	EQ	276
#define	NEQ	277
#define	LT	278
#define	LE	279
#define	GT	280
#define	GE	281
#define	AND	282
#define	OR	283
#define	ASSIGN	284
#define	ARRAY	285
#define	IF	286
#define	THEN	287
#define	ELSE	288
#define	WHILE	289
#define	FOR	290
#define	TO	291
#define	DO	292
#define	LET	293
#define	IN	294
#define	END	295
#define	OF	296
#define	BREAK	297
#define	NIL	298
#define	FUNCTION	299
#define	VAR	300
#define	TYPE	301

#line 1 "tiger.y"

#include <stdio.h>
#include "../../../COMMON_H_FILES/util.h"
#include "../../../COMMON_H_FILES/errormsg.h"
#include "../../../COMMON_H_FILES/symbol.h" 
#include "../../../COMMON_H_FILES/absyn.h"

int yylex(void); /* function prototype */

int numArguments=1;

A_exp absyn_root;

void yyerror(char *s)
{
 EM_error(EM_tokPos, "%s", s);
}

#line 21 "tiger.y"
typedef union
{
	int			pos;
	int			ival;
	float		fval;
	string		sval;
	A_var		var;
	A_exp		exp;
	A_dec		dec;
	A_decList	decList;
	A_expList	expList;
	A_fieldList	fieldList;
	A_fundec	fundec;

	struct
	{
		union
		{
			int			ival;
			float		fval;
			string		sval;
			A_var		var;
			A_exp		exp;
			A_dec		dec;
			A_decList	decList;
			A_expList	expList;
			A_fieldList	fieldList;
			A_fundec	fundec;
		}
		gval;
		
		int type;
	}
	xval;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		142
#define	YYFLAG		-32768
#define	YYNTBASE	47

#define YYTRANSLATE(x) ((unsigned)(x) <= 301 ? yytranslate[x] : 67)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     6,     8,    10,    12,    16,    18,    20,
    22,    24,    26,    28,    32,    36,    40,    44,    48,    52,
    56,    60,    64,    68,    72,    76,    81,    90,    94,    98,
   102,   104,   108,   114,   118,   123,   130,   137,   144,   151,
   158,   163,   168,   173,   178,   183,   190,   197,   204,   211,
   220,   228,   238,   240,   242,   244,   247,   249,   255,   257,
   261,   266,   270,   274,   278,   283
};

static const short yyrhs[] = {    48,
     0,     3,     0,     4,     0,     5,     0,    64,     0,    54,
     0,    10,    48,    11,     0,    63,     0,    51,     0,    50,
     0,    65,     0,    49,     0,    66,     0,    48,    17,    48,
     0,    48,    18,    48,     0,    48,    19,    48,     0,    48,
    20,    48,     0,    48,    21,    48,     0,    48,    22,    48,
     0,    48,    23,    48,     0,    48,    24,    48,     0,    48,
    25,    48,     0,    48,    26,    48,     0,    48,    27,    48,
     0,    48,    28,    48,     0,    31,    48,    32,    48,     0,
    35,     6,    29,    48,    36,    48,    37,    48,     0,    48,
     9,    52,     0,    48,     9,    48,     0,    48,     7,    53,
     0,    48,     0,    10,    52,    11,     0,     6,     8,     6,
     7,    55,     0,     6,     8,     6,     0,    46,     6,    21,
     6,     0,    46,     6,    21,    30,    41,     6,     0,    46,
     6,    21,    14,    55,    15,     0,     6,    12,     3,    13,
    41,    43,     0,     6,    12,     3,    13,    41,     3,     0,
     6,    12,     3,    13,    41,     4,     0,     6,    14,    53,
    15,     0,    45,     6,     8,     6,     0,    45,     6,    29,
    48,     0,    45,     6,    29,    57,     0,    45,     6,    29,
    58,     0,    45,     6,     8,     6,    29,    48,     0,    45,
     6,     8,     6,    29,    57,     0,    45,     6,     8,     6,
    29,    58,     0,    44,     6,    10,    11,    21,    48,     0,
    44,     6,    10,    11,     8,     6,    21,    48,     0,    44,
     6,    10,    55,    11,    21,    48,     0,    44,     6,    10,
    55,    11,     8,     6,    21,    48,     0,    56,     0,    59,
     0,    60,     0,    61,    62,     0,    61,     0,    38,    62,
    39,    48,    40,     0,     6,     0,    64,    16,     6,     0,
    64,    12,    48,    13,     0,    64,    29,    48,     0,    64,
    29,    57,     0,    64,    29,    58,     0,     6,    10,    53,
    11,     0,     6,    10,    11,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   135,   137,   138,   139,   140,   141,   142,   143,   144,   145,
   146,   147,   148,   151,   152,   153,   154,   155,   156,   157,
   158,   159,   160,   161,   162,   165,   168,   171,   172,   174,
   175,   177,   180,   181,   184,   185,   186,   189,   190,   191,
   193,   195,   196,   197,   198,   199,   200,   201,   204,   205,
   206,   207,   209,   210,   211,   214,   215,   218,   221,   222,
   223,   225,   226,   227,   229,   230
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","INT","FLOAT",
"STRING","ID","COMMA","COLON","SEMICOLON","LPAREN","RPAREN","LBRACK","RBRACK",
"LBRACE","RBRACE","ARROW","PLUS","MINUS","TIMES","DIVIDE","EQ","NEQ","LT","LE",
"GT","GE","AND","OR","ASSIGN","ARRAY","IF","THEN","ELSE","WHILE","FOR","TO",
"DO","LET","IN","END","OF","BREAK","NIL","FUNCTION","VAR","TYPE","program","exp",
"OpExp","IfThenExp","ForExp","ListExpSemicolon","ListExpComma","SequenceExp",
"TypeFields","TypeDeclaration","AllocateArrayExp","AllocateRecordExp","VariableDeclaration",
"FunctionDeclaration","declaration","declarations","LetExp","lvalue","AssignExp",
"CallExp", NULL
};
#endif

static const short yyr1[] = {     0,
    47,    48,    48,    48,    48,    48,    48,    48,    48,    48,
    48,    48,    48,    49,    49,    49,    49,    49,    49,    49,
    49,    49,    49,    49,    49,    50,    51,    52,    52,    53,
    53,    54,    55,    55,    56,    56,    56,    57,    57,    57,
    58,    59,    59,    59,    59,    59,    59,    59,    60,    60,
    60,    60,    61,    61,    61,    62,    62,    63,    64,    64,
    64,    65,    65,    65,    66,    66
};

static const short yyr2[] = {     0,
     1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
     1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     4,     8,     3,     3,     3,
     1,     3,     5,     3,     4,     6,     6,     6,     6,     6,
     4,     4,     4,     4,     4,     6,     6,     6,     6,     8,
     7,     9,     1,     1,     1,     2,     1,     5,     1,     3,
     4,     3,     3,     3,     4,     3
};

static const short yydefact[] = {     0,
     2,     3,     4,    59,     0,     0,     0,     0,     1,    12,
    10,     9,     6,     8,     5,    11,    13,     0,     0,     0,
     0,     0,     0,     0,     0,    53,    54,    55,    57,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    66,    31,     0,     0,     7,
    32,     0,     0,     0,     0,     0,    56,     0,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
     0,    60,    59,    62,    63,    64,     0,    65,    29,    28,
    26,     0,     0,     0,     0,     0,     0,    61,     0,     0,
    30,     0,     0,     0,     0,    42,    43,    44,    45,    35,
     0,     0,    58,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    41,     0,    34,     0,    49,     0,
     0,    46,    47,    48,    37,    36,     0,    27,     0,     0,
     0,    51,    39,    40,    38,    33,    50,     0,    52,     0,
     0,     0
};

static const short yydefgoto[] = {   140,
    47,    10,    11,    12,    20,    48,    13,    95,    26,    75,
    76,    27,    28,    29,    30,    14,    15,    16,    17
};

static const short yypact[] = {    51,
-32768,-32768,-32768,     2,    51,    51,     8,    22,   235,-32768,
-32768,-32768,-32768,-32768,    71,-32768,-32768,    13,   155,    -1,
   207,    -8,    44,    78,    85,-32768,-32768,-32768,    22,    56,
    51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
    51,    51,    51,    90,    59,-32768,   122,    87,    51,-32768,
-32768,    51,    51,    89,    17,    82,-32768,    51,    40,    40,
-32768,-32768,    95,    95,    95,    95,    95,    95,   247,   247,
   223,-32768,    92,   235,-32768,-32768,    51,-32768,   175,-32768,
   235,   187,     9,    99,    59,    -3,    53,-32768,   104,    51,
-32768,    51,   100,     1,   106,    81,   235,-32768,-32768,-32768,
   112,    79,-32768,   109,   108,   134,   113,   118,    51,     5,
    59,   110,   120,    86,-32768,    51,   121,   111,   235,   125,
    51,   235,-32768,-32768,-32768,-32768,     4,   235,   112,    51,
   114,   235,-32768,-32768,-32768,-32768,   235,    51,   235,   133,
   136,-32768
};

static const short yypgoto[] = {-32768,
     0,-32768,-32768,-32768,    88,    11,-32768,  -100,-32768,   -83,
   -81,-32768,-32768,-32768,   105,-32768,-32768,-32768,-32768
};


#define	YYLAST		273


static const short yytable[] = {     9,
   112,    98,   100,    99,    19,    21,   133,   134,   108,    51,
   101,    18,   120,    22,    93,     1,     2,     3,     4,    94,
    53,   109,     5,    46,    84,   121,   102,   123,   136,   124,
    59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
    69,    70,    71,     6,    74,    85,   135,     7,    79,    54,
     8,    81,    82,     1,     2,     3,     4,    87,    33,    34,
     5,     1,     2,     3,    73,    23,    24,    25,     5,    31,
    32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
    42,     6,    43,    55,    97,     7,    44,    91,     8,     6,
    56,   106,   103,     7,    58,    72,     8,    78,    83,    45,
   105,    18,    86,    89,    96,    90,   104,   107,   119,   111,
   122,    31,    32,    33,    34,   128,   110,    93,   117,   113,
   132,   114,   115,   118,   125,   126,   127,   129,    77,   137,
   131,   130,   141,    57,   138,   142,    80,   139,    31,    32,
    33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
    31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
    41,    42,     0,    49,     0,    50,     0,     0,     0,     0,
   116,    31,    32,    33,    34,    35,    36,    37,    38,    39,
    40,    41,    42,    49,     0,     0,     0,     0,     0,     0,
     0,    31,    32,    33,    34,    35,    36,    37,    38,    39,
    40,    41,    42,    31,    32,    33,    34,    35,    36,    37,
    38,    39,    40,    41,    42,     0,     0,     0,     0,     0,
     0,     0,    92,    31,    32,    33,    34,    35,    36,    37,
    38,    39,    40,    41,    42,    88,     0,     0,    52,    31,
    32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
    42,    31,    32,    33,    34,    35,    36,    37,    38,    39,
    40,    41,    42,    31,    32,    33,    34,    35,    36,    37,
    38,    39,    40
};

static const short yycheck[] = {     0,
   101,    85,     6,    85,     5,     6,     3,     4,     8,    11,
    14,    10,     8,     6,     6,     3,     4,     5,     6,    11,
    29,    21,    10,    11,     8,    21,    30,   111,   129,   111,
    31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
    41,    42,    43,    31,    45,    29,    43,    35,    49,     6,
    38,    52,    53,     3,     4,     5,     6,    58,    19,    20,
    10,     3,     4,     5,     6,    44,    45,    46,    10,    17,
    18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
    28,    31,    12,     6,    85,    35,    16,    77,    38,    31,
     6,    92,    40,    35,    39,     6,    38,    11,    10,    29,
    90,    10,    21,    12,     6,    14,     3,     8,   109,    29,
   111,    17,    18,    19,    20,   116,    11,     6,     6,    41,
   121,    13,    15,     6,    15,     6,    41,     7,     7,   130,
     6,    21,     0,    29,    21,     0,    49,   138,    17,    18,
    19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    -1,     9,    -1,    11,    -1,    -1,    -1,    -1,
    37,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,     9,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    17,    18,    19,    20,    21,    22,    23,
    24,    25,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    36,    17,    18,    19,    20,    21,    22,    23,
    24,    25,    26,    27,    28,    13,    -1,    -1,    32,    17,
    18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
    28,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    17,    18,    19,    20,    21,    22,    23,
    24,    25,    26
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) malloc (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) malloc (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 135 "tiger.y"
{absyn_root = yyvsp[0].xval.gval.exp;;
    break;}
case 2:
#line 137 "tiger.y"
{yyval.xval.gval.exp = A_IntExp(EM_tokPos,yyvsp[0].xval.gval.ival);;
    break;}
case 3:
#line 138 "tiger.y"
{yyval.xval.gval.exp = A_FloatExp(EM_tokPos,yyvsp[0].xval.gval.fval);;
    break;}
case 4:
#line 139 "tiger.y"
{yyval.xval.gval.exp = A_StringExp(EM_tokPos,yyvsp[0].xval.gval.sval);;
    break;}
case 5:
#line 140 "tiger.y"
{yyval.xval.gval.exp = A_VarExp(EM_tokPos,yyvsp[0].xval.gval.var);;
    break;}
case 6:
#line 141 "tiger.y"
{yyval.xval.gval.exp = yyvsp[0].xval.gval.exp;;
    break;}
case 7:
#line 142 "tiger.y"
{yyval.xval.gval.exp = yyvsp[-1].xval.gval.exp;;
    break;}
case 8:
#line 143 "tiger.y"
{yyval.xval.gval.exp = yyvsp[0].xval.gval.exp;;
    break;}
case 9:
#line 144 "tiger.y"
{yyval.xval.gval.exp = yyvsp[0].xval.gval.exp;;
    break;}
case 10:
#line 145 "tiger.y"
{yyval.xval.gval.exp = yyvsp[0].xval.gval.exp;;
    break;}
case 11:
#line 146 "tiger.y"
{yyval.xval.gval.exp = yyvsp[0].xval.gval.exp;;
    break;}
case 12:
#line 147 "tiger.y"
{yyval.xval.gval.exp = yyvsp[0].xval.gval.exp;;
    break;}
case 13:
#line 148 "tiger.y"
{yyval.xval.gval.exp = yyvsp[0].xval.gval.exp;;
    break;}
case 14:
#line 151 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_plusOp,   yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 15:
#line 152 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_minusOp,  yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 16:
#line 153 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_timesOp,  yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 17:
#line 154 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_divideOp, yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 18:
#line 155 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_eqOp,     yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 19:
#line 156 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_neqOp,    yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 20:
#line 157 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_ltOp,     yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 21:
#line 158 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_leOp,     yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 22:
#line 159 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_gtOp,     yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 23:
#line 160 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_geOp,     yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 24:
#line 161 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_andOp,    yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 25:
#line 162 "tiger.y"
{yyval.xval.gval.exp = A_OpExp(EM_tokPos, A_orOp,     yyvsp[-2].xval.gval.exp, yyvsp[0].xval.gval.exp);;
    break;}
case 26:
#line 165 "tiger.y"
{yyval.xval.gval.exp = A_IfExp(EM_tokPos,yyvsp[-2].xval.gval.exp,yyvsp[0].xval.gval.exp,NULL);;
    break;}
case 27:
#line 168 "tiger.y"
{yyval.xval.gval.exp = A_ForExp(EM_tokPos,S_Symbol(yyvsp[-6].xval.gval.sval),yyvsp[-4].xval.gval.exp,yyvsp[-2].xval.gval.exp,yyvsp[0].xval.gval.exp);;
    break;}
case 28:
#line 171 "tiger.y"
{yyval.xval.gval.expList = A_ExpList(yyvsp[-2].xval.gval.exp,yyvsp[0].xval.gval.expList);;
    break;}
case 29:
#line 172 "tiger.y"
{yyval.xval.gval.expList = A_ExpList(yyvsp[-2].xval.gval.exp,A_ExpList(yyvsp[0].xval.gval.exp,NULL));;
    break;}
case 30:
#line 174 "tiger.y"
{yyval.xval.gval.expList = A_ExpList(yyvsp[-2].xval.gval.exp,yyvsp[0].xval.gval.expList);numArguments++;;
    break;}
case 31:
#line 175 "tiger.y"
{yyval.xval.gval.expList = A_ExpList(yyvsp[0].xval.gval.exp,NULL);;
    break;}
case 32:
#line 177 "tiger.y"
{yyval.xval.gval.exp = A_SeqExp(EM_tokPos,yyvsp[-1].xval.gval.expList);;
    break;}
case 33:
#line 180 "tiger.y"
{yyval.xval.gval.fieldList = A_FieldList(A_Field(EM_tokPos,S_Symbol(yyvsp[-4].xval.gval.sval),S_Symbol(yyvsp[-2].xval.gval.sval)),yyvsp[0].xval.gval.fieldList);;
    break;}
case 34:
#line 181 "tiger.y"
{yyval.xval.gval.fieldList = A_FieldList(A_Field(EM_tokPos,S_Symbol(yyvsp[-2].xval.gval.sval),S_Symbol(yyvsp[0].xval.gval.sval)),NULL);;
    break;}
case 35:
#line 184 "tiger.y"
{yyval.xval.gval.dec = A_TypeDec(EM_tokPos,A_Namety(S_Symbol(yyvsp[-2].xval.gval.sval),A_NameTy(  EM_tokPos,S_Symbol(yyvsp[0].xval.gval.sval))));;
    break;}
case 36:
#line 185 "tiger.y"
{yyval.xval.gval.dec = A_TypeDec(EM_tokPos,A_Namety(S_Symbol(yyvsp[-4].xval.gval.sval),A_ArrayTy( EM_tokPos,S_Symbol(yyvsp[0].xval.gval.sval))));;
    break;}
case 37:
#line 186 "tiger.y"
{yyval.xval.gval.dec = A_TypeDec(EM_tokPos,A_Namety(S_Symbol(yyvsp[-4].xval.gval.sval),A_RecordTy(EM_tokPos,yyvsp[-1].xval.gval.fieldList)));;
    break;}
case 38:
#line 189 "tiger.y"
{yyval.xval.gval.exp = A_AllocateArrayExp(EM_tokPos,S_Symbol(yyvsp[-5].xval.gval.sval),yyvsp[-3].xval.gval.ival,0);;
    break;}
case 39:
#line 190 "tiger.y"
{yyval.xval.gval.exp = A_AllocateArrayExp(EM_tokPos,S_Symbol(yyvsp[-5].xval.gval.sval),yyvsp[-3].xval.gval.ival,yyvsp[0].xval.gval.ival);;
    break;}
case 40:
#line 191 "tiger.y"
{yyval.xval.gval.exp = A_AllocateArrayExp(EM_tokPos,S_Symbol(yyvsp[-5].xval.gval.sval),yyvsp[-3].xval.gval.ival,2);;
    break;}
case 41:
#line 193 "tiger.y"
{yyval.xval.gval.exp = A_AllocateRecordExp(EM_tokPos,S_Symbol(yyvsp[-3].xval.gval.sval),yyvsp[-1].xval.gval.expList);;
    break;}
case 42:
#line 195 "tiger.y"
{yyval.xval.gval.dec = A_VarDec(EM_tokPos,S_Symbol(yyvsp[-2].xval.gval.sval),S_Symbol(yyvsp[0].xval.gval.sval),NULL);;
    break;}
case 43:
#line 196 "tiger.y"
{yyval.xval.gval.dec = A_VarDec(EM_tokPos,S_Symbol(yyvsp[-2].xval.gval.sval),NULL,yyvsp[0].xval.gval.exp);;
    break;}
case 44:
#line 197 "tiger.y"
{yyval.xval.gval.dec = A_VarDec(EM_tokPos,S_Symbol(yyvsp[-2].xval.gval.sval),NULL,yyvsp[0].xval.gval.exp);;
    break;}
case 45:
#line 198 "tiger.y"
{yyval.xval.gval.dec = A_VarDec(EM_tokPos,S_Symbol(yyvsp[-2].xval.gval.sval),NULL,yyvsp[0].xval.gval.exp);;
    break;}
case 46:
#line 199 "tiger.y"
{yyval.xval.gval.dec = A_VarDec(EM_tokPos,S_Symbol(yyvsp[-4].xval.gval.sval),S_Symbol(yyvsp[-2].xval.gval.sval),yyvsp[0].xval.gval.exp);;
    break;}
case 47:
#line 200 "tiger.y"
{yyval.xval.gval.dec = A_VarDec(EM_tokPos,S_Symbol(yyvsp[-4].xval.gval.sval),S_Symbol(yyvsp[-2].xval.gval.sval),yyvsp[0].xval.gval.exp);;
    break;}
case 48:
#line 201 "tiger.y"
{yyval.xval.gval.dec = A_VarDec(EM_tokPos,S_Symbol(yyvsp[-4].xval.gval.sval),S_Symbol(yyvsp[-2].xval.gval.sval),yyvsp[0].xval.gval.exp);;
    break;}
case 49:
#line 204 "tiger.y"
{yyval.xval.gval.dec = A_FunctionDec(EM_tokPos,A_Fundec(EM_tokPos,S_Symbol(yyvsp[-4].xval.gval.sval),NULL,NULL,yyvsp[0].xval.gval.exp));;
    break;}
case 50:
#line 205 "tiger.y"
{yyval.xval.gval.dec = A_FunctionDec(EM_tokPos,A_Fundec(EM_tokPos,S_Symbol(yyvsp[-6].xval.gval.sval),NULL,S_Symbol(yyvsp[-2].xval.gval.sval),yyvsp[0].xval.gval.exp));;
    break;}
case 51:
#line 206 "tiger.y"
{yyval.xval.gval.dec = A_FunctionDec(EM_tokPos,A_Fundec(EM_tokPos,S_Symbol(yyvsp[-5].xval.gval.sval),yyvsp[-3].xval.gval.fieldList,NULL,yyvsp[0].xval.gval.exp));;
    break;}
case 52:
#line 207 "tiger.y"
{yyval.xval.gval.dec = A_FunctionDec(EM_tokPos,A_Fundec(EM_tokPos,S_Symbol(yyvsp[-7].xval.gval.sval),yyvsp[-5].xval.gval.fieldList,S_Symbol(yyvsp[-2].xval.gval.sval),yyvsp[0].xval.gval.exp));;
    break;}
case 53:
#line 209 "tiger.y"
{yyval.xval.gval.dec = yyvsp[0].xval.gval.dec;;
    break;}
case 54:
#line 210 "tiger.y"
{yyval.xval.gval.dec = yyvsp[0].xval.gval.dec;;
    break;}
case 55:
#line 211 "tiger.y"
{yyval.xval.gval.dec = yyvsp[0].xval.gval.dec;;
    break;}
case 56:
#line 214 "tiger.y"
{yyval.xval.gval.decList = A_DecList(yyvsp[-1].xval.gval.dec,yyvsp[0].xval.gval.decList);;
    break;}
case 57:
#line 215 "tiger.y"
{yyval.xval.gval.decList = A_DecList(yyvsp[0].xval.gval.dec,NULL);;
    break;}
case 58:
#line 218 "tiger.y"
{yyval.xval.gval.exp = A_LetExp(EM_tokPos,yyvsp[-3].xval.gval.decList,yyvsp[-1].xval.gval.exp);;
    break;}
case 59:
#line 221 "tiger.y"
{yyval.xval.gval.var = A_SimpleVar(EM_tokPos,S_Symbol(yyvsp[0].xval.gval.sval));;
    break;}
case 60:
#line 222 "tiger.y"
{yyval.xval.gval.var = A_FieldVar(EM_tokPos,yyvsp[-2].xval.gval.var,S_Symbol(yyvsp[0].xval.gval.sval));;
    break;}
case 61:
#line 223 "tiger.y"
{yyval.xval.gval.var = A_SubscriptVar(EM_tokPos,yyvsp[-3].xval.gval.var,yyvsp[-1].xval.gval.exp);;
    break;}
case 62:
#line 225 "tiger.y"
{yyval.xval.gval.exp = A_AssignExp(EM_tokPos,yyvsp[-2].xval.gval.var,yyvsp[0].xval.gval.exp);;
    break;}
case 63:
#line 226 "tiger.y"
{yyval.xval.gval.exp = A_AssignExp(EM_tokPos,yyvsp[-2].xval.gval.var,yyvsp[0].xval.gval.exp);;
    break;}
case 64:
#line 227 "tiger.y"
{yyval.xval.gval.exp = A_AssignExp(EM_tokPos,yyvsp[-2].xval.gval.var,yyvsp[0].xval.gval.exp);;
    break;}
case 65:
#line 229 "tiger.y"
{yyval.xval.gval.exp = A_CallExp(EM_tokPos, S_Symbol(yyvsp[-3].xval.gval.sval), yyvsp[-1].xval.gval.expList);;
    break;}
case 66:
#line 230 "tiger.y"
{yyval.xval.gval.exp = A_CallExp(EM_tokPos, S_Symbol(yyvsp[-2].xval.gval.sval), NULL, NULL);;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 232 "tiger.y"


	
