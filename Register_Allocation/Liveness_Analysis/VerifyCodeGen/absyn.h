#ifndef __ABSYN_H__
#define __ABSYN_H__

/**********************/
/* FILE NAME: absyn.h */
/**********************/

/*****************/
/* INCLUDE FILES */
/*****************/
#include <stdio.h>

/***************/
/* DEFINITIONS */
/***************/
#define MAX_NAME_LENGTH_OF_LABEL 100

/*********/
/* ENUMS */
/*********/
typedef enum {
	ABSTRACT_SYNTAX_LOAD_EXP_TYPE,
	ABSTRACT_SYNTAX_LOAD_REGISTERS_EXP_TYPE,
	ABSTRACT_SYNTAX_ADD_IMMEDIATE_EXP_TYPE,
	ABSTRACT_SYNTAX_STORE_EXP_TYPE,
	ABSTRACT_SYNTAX_LOAD_IMMEDIATE_EXP_TYPE,
	ABSTRACT_SYNTAX_ADD_EXP_TYPE,
	ABSTRACT_SYNTAX_SUB_EXP_TYPE,
	ABSTRACT_SYNTAX_MUL_EXP_TYPE,
	ABSTRACT_SYNTAX_LABEL_EXP_TYPE,
	ABSTRACT_SYNTAX_MOVE_EXP_TYPE,
	ABSTRACT_SYNTAX_JUMP_EXP_TYPE,
	ABSTRACT_SYNTAX_JUMP_AND_LINK_EXP_TYPE,
	ABSTRACT_SYNTAX_JUMP_REGISTER_EXP_TYPE,
	ABSTRACT_SYNTAX_PUSH_EXP_TYPE,
	ABSTRACT_SYNTAX_POP_EXP_TYPE,
	ABSTRACT_SYNTAX_BEQ_EXP_TYPE,
	ABSTRACT_SYNTAX_BNE_EXP_TYPE,
	ABSTRACT_SYNTAX_BGT_EXP_TYPE,
	ABSTRACT_SYNTAX_BGE_EXP_TYPE,
	ABSTRACT_SYNTAX_BLT_EXP_TYPE,
	ABSTRACT_SYNTAX_BLE_EXP_TYPE,
} 	ABSTRACT_SYNTAX_EXP_TYPE;

/*********/
/* TYPES */
/*********/
typedef struct ABSTRACT_SYNTAX_exp_ *ABSTRACT_SYNTAX_exp;
typedef struct ABSTRACT_SYNTAX_expList_ *ABSTRACT_SYNTAX_expList;

struct ABSTRACT_SYNTAX_exp_
{
	ABSTRACT_SYNTAX_EXP_TYPE type;

	union
	{
		char jump[MAX_NAME_LENGTH_OF_LABEL];
		char label[MAX_NAME_LENGTH_OF_LABEL];
		char jump_and_link[MAX_NAME_LENGTH_OF_LABEL];
		char jump_register[MAX_NAME_LENGTH_OF_LABEL];
 
		struct {char *temp1;char *temp2;char *label;} beq;
		struct {char *temp1;char *temp2;char *label;} bne;
		struct {char *temp1;char *temp2;char *label;} bgt;
		struct {char *temp1;char *temp2;char *label;} bge;
		struct {char *temp1;char *temp2;char *label;} blt;
		struct {char *temp1;char *temp2;char *label;} ble;

		struct {char *temp1;char *temp2;char *temp3;} add;
		struct {char *temp1;char *temp2;char *temp3;} sub;
		struct {char *temp1;char *temp2;char *temp3;} mul;

		struct {char *temp1;char *temp2;} move;

		struct {char *temp1; char *temp2;int value;} add_immediate;

		struct {char *temp ;int value;} load_immediate;

		struct {char *temp1;char *temp2;int offset;} load;
		struct {char *temp1;char *temp2;int offset;} store;

	} u;
};

/***********************************/
/* Linked lists and nodes of lists */
/***********************************/
struct ABSTRACT_SYNTAX_expList_ {ABSTRACT_SYNTAX_exp head; ABSTRACT_SYNTAX_expList tail;};

/***********************/
/* Function Prototypes */
/***********************/
ABSTRACT_SYNTAX_expList ABSTRACT_SYNTAX_ExpList(ABSTRACT_SYNTAX_exp head, ABSTRACT_SYNTAX_expList tail);

#endif