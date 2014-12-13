/**********************/
/* FILE NAME: absyn.c */
/**********************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <string.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "util.h"
#include "absyn.h"

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_LOAD(char *temp1,char *temp2,int offset)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_LOAD_EXP_TYPE;

	p->u.load.temp1 = temp1;
	p->u.load.temp2 = temp2;
	p->u.load.offset = offset;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_ADD_IMMEDIATE(char *temp1,char *temp2,int value)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_ADD_IMMEDIATE_EXP_TYPE;

	p->u.add_immediate.temp1 = temp1;
	p->u.add_immediate.temp2 = temp2;
	p->u.add_immediate.value = value;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_STORE(char *temp1,char *temp2,int offset)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_STORE_EXP_TYPE;

	p->u.store.temp1 = temp1;
	p->u.store.temp2 = temp2;
	p->u.store.offset = offset;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_MOVE(char *temp1,char *temp2)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_MOVE_EXP_TYPE;

	p->u.move.temp1 = temp1;
	p->u.move.temp2 = temp2;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_ADD(char *temp1,char *temp2,char *temp3)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_ADD_EXP_TYPE;

	p->u.add.temp1 = temp1;
	p->u.add.temp2 = temp2;
	p->u.add.temp3 = temp3;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_SUB(char *temp1,char *temp2,char *temp3)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_SUB_EXP_TYPE;

	p->u.sub.temp1 = temp1;
	p->u.sub.temp2 = temp2;
	p->u.sub.temp3 = temp3;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_MUL(char *temp1,char *temp2,char *temp3)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_MUL_EXP_TYPE;

	p->u.mul.temp1 = temp1;
	p->u.mul.temp2 = temp2;
	p->u.mul.temp3 = temp3;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_LOAD_IMMEDIATE(char *temp,int value)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_LOAD_IMMEDIATE_EXP_TYPE;

	p->u.load_immediate.temp = temp;
	p->u.load_immediate.value = value;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_JUMP(char *label)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_JUMP_EXP_TYPE;

	strcpy(p->u.jump,label);

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_JUMP_REGISTER(char *register_name)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_JUMP_REGISTER_EXP_TYPE;

	strcpy(p->u.jump_register,register_name);

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_JUMP_AND_LINK(char *label)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_JUMP_AND_LINK_EXP_TYPE;

	strcpy(p->u.jump_and_link,label);

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_LABEL(char *label)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_LABEL_EXP_TYPE;

	strcpy(p->u.label,label);

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_BEQ(char *temp1,char *temp2,char *label)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_BEQ_EXP_TYPE;

	p->u.beq.temp1 = temp1;
	p->u.beq.temp2 = temp2;
	p->u.beq.label = label;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_BNE(char *temp1,char *temp2,char *label)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_BNE_EXP_TYPE;

	p->u.bne.temp1 = temp1;
	p->u.bne.temp2 = temp2;
	p->u.bne.label = label;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_BGT(char *temp1,char *temp2,char *label)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_BGT_EXP_TYPE;

	p->u.bgt.temp1 = temp1;
	p->u.bgt.temp2 = temp2;
	p->u.bgt.label = label;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_BGE(char *temp1,char *temp2,char *label)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_BGE_EXP_TYPE;

	p->u.bge.temp1 = temp1;
	p->u.bge.temp2 = temp2;
	p->u.bge.label = label;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_BLT(char *temp1,char *temp2,char *label)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_BLT_EXP_TYPE;
	
	p->u.blt.temp1 = temp1;
	p->u.blt.temp2 = temp2;
	p->u.blt.label = label;

	return p;
}

ABSTRACT_SYNTAX_exp ABSTRACT_SYNTAX_BLE(char *temp1,char *temp2,char *label)
{
	ABSTRACT_SYNTAX_exp p = (ABSTRACT_SYNTAX_exp) checked_malloc(sizeof(*p));

	p->type = ABSTRACT_SYNTAX_BLE_EXP_TYPE;

	p->u.ble.temp1 = temp1;
	p->u.ble.temp2 = temp2;
	p->u.ble.label = label;

	return p;
}

ABSTRACT_SYNTAX_expList ABSTRACT_SYNTAX_ExpList(ABSTRACT_SYNTAX_exp head, ABSTRACT_SYNTAX_expList tail)
{
	ABSTRACT_SYNTAX_expList p = (ABSTRACT_SYNTAX_expList) checked_malloc(sizeof(*p));

	p->head = head;
	p->tail = tail;

	return p;
}