/**********/
/* main.c */
/**********/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "util.h"
#include "absyn.h"
#include "errormsg.h"
#include "parse.h"

/***************/
/* DEFINITIONS */
/***************/
#define MAX_NUM_ASM_COMMANDS 1000

FILE *fl;

int index=0;

char instructionToLabel[MAX_NUM_ASM_COMMANDS][50];

int FindInstructionNumberOfLabel(char *label)
{
	int i=0;

	for(i=0;i<MAX_NUM_ASM_COMMANDS;i++)
	{
		if (strcmp(instructionToLabel[i],label)==0)
		{
			return i;
		}
	}
	return 0;
}

void Build_Use_and_Def_from_Exp_Add_Sub_Mul(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = atoi(exp->u.add.temp1+strlen("Temp_"))-100;

	use[command][0] = atoi(exp->u.add.temp2+strlen("Temp_"))-100;
	use[command][1] = atoi(exp->u.add.temp3+strlen("Temp_"))-100;
}

void Build_Use_and_Def_from_Exp_Branch(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = -1;

	if ( (exp->u.bgt.temp1)[0] == 'T')
	{	use[command][0] = atoi(exp->u.beq.temp1 + strlen("Temp_")) - 100;
		use[command][1] = atoi(exp->u.beq.temp2 + strlen("Temp_")) - 100;
	}
}

void Build_Use_and_Def_from_Exp_Load(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = atoi(exp->u.load.temp1+strlen("Temp_"))-100;

	use[command][0] = atoi(exp->u.load.temp2+strlen("Temp_"))-100;
	use[command][1] = -1;
}

void Build_Use_and_Def_from_Exp_Move(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = atoi(exp->u.load.temp1+strlen("Temp_"))-100;

	use[command][0] = atoi(exp->u.load.temp2+strlen("Temp_"))-100;
	use[command][1] = -1;
}

void Build_Use_and_Def_from_Exp_Jump(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = -1;

	use[command][0] = -1;
	use[command][1] = -1;
}

void Build_Use_and_Def_from_Exp_Label(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = -1;

	use[command][0] = -1;
	use[command][1] = -1;
}

void Build_Use_and_Def_from_Exp_Store(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = -1;

	use[command][0] = atoi(exp->u.store.temp1+strlen("Temp_"))-100;
	use[command][1] = atoi(exp->u.store.temp2+strlen("Temp_"))-100;
}

void Build_Use_and_Def_from_Exp_Jump_And_link(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = -1;

	use[command][0] = -1;
	use[command][1] = -1;
}

void Build_Use_and_Def_from_Exp_Jump_Register(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = -1;

	use[command][0] = -1;
	use[command][1] = -1;
}

void Build_Use_and_Def_from_Exp_Add_Immediate(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = atoi(exp->u.add_immediate.temp1+strlen("Temp_"))-100;

	use[command][0] = atoi(exp->u.add_immediate.temp2+strlen("Temp_"))-100;;
	use[command][1] = -1;
}

void Build_Use_and_Def_from_Exp_Load_Immediate(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	def[command] = atoi(exp->u.load_immediate.temp+strlen("Temp_"))-100;

	use[command][0] = -1;
	use[command][1] = -1;
}

void Build_Use_and_Def_from_Exp(
	ABSTRACT_SYNTAX_exp exp,
	int use[MAX_NUM_ASM_COMMANDS][2],
	int def[MAX_NUM_ASM_COMMANDS],
	int command)
{
	switch (exp->type) {
	case (ABSTRACT_SYNTAX_ADD_EXP_TYPE):
	case (ABSTRACT_SYNTAX_SUB_EXP_TYPE):
	case (ABSTRACT_SYNTAX_MUL_EXP_TYPE):            Build_Use_and_Def_from_Exp_Add_Sub_Mul(exp,use,def,command);   break;
	case (ABSTRACT_SYNTAX_BEQ_EXP_TYPE):
	case (ABSTRACT_SYNTAX_BNE_EXP_TYPE):
	case (ABSTRACT_SYNTAX_BGT_EXP_TYPE):
	case (ABSTRACT_SYNTAX_BGE_EXP_TYPE):
	case (ABSTRACT_SYNTAX_BLT_EXP_TYPE):
	case (ABSTRACT_SYNTAX_BLE_EXP_TYPE):            Build_Use_and_Def_from_Exp_Branch(exp,use,def,command);        break;
	case (ABSTRACT_SYNTAX_LOAD_EXP_TYPE):           Build_Use_and_Def_from_Exp_Load(exp,use,def,command);          break;
	case (ABSTRACT_SYNTAX_MOVE_EXP_TYPE):           Build_Use_and_Def_from_Exp_Move(exp,use,def,command);          break;
	case (ABSTRACT_SYNTAX_JUMP_EXP_TYPE):           Build_Use_and_Def_from_Exp_Jump(exp,use,def,command);          break;
	case (ABSTRACT_SYNTAX_LABEL_EXP_TYPE):          Build_Use_and_Def_from_Exp_Label(exp,use,def,command);         break;
	case (ABSTRACT_SYNTAX_STORE_EXP_TYPE):          Build_Use_and_Def_from_Exp_Store(exp,use,def,command);         break;
	case (ABSTRACT_SYNTAX_JUMP_AND_LINK_EXP_TYPE):  Build_Use_and_Def_from_Exp_Jump_And_link(exp,use,def,command); break;
	case (ABSTRACT_SYNTAX_JUMP_REGISTER_EXP_TYPE):  Build_Use_and_Def_from_Exp_Jump_Register(exp,use,def,command); break;
	case (ABSTRACT_SYNTAX_ADD_IMMEDIATE_EXP_TYPE):  Build_Use_and_Def_from_Exp_Add_Immediate(exp,use,def,command); break;
	case (ABSTRACT_SYNTAX_LOAD_IMMEDIATE_EXP_TYPE): Build_Use_and_Def_from_Exp_Load_Immediate(exp,use,def,command);break;
	}
}

void Build_Control_Flow_graph_default(
	ABSTRACT_SYNTAX_exp exp,
	int out_edges[MAX_NUM_ASM_COMMANDS][2],
	int command)
{
	out_edges[command][0]=command+1;
	out_edges[command][1]=-1;
}

void Build_Control_Flow_graph_Branch(
	ABSTRACT_SYNTAX_exp exp,
	int out_edges[MAX_NUM_ASM_COMMANDS][2],
	int command)
{
	out_edges[command][0]=command+1;
	out_edges[command][1]=FindInstructionNumberOfLabel(exp->u.label);
}

void Build_Control_Flow_graph_Jump(
	ABSTRACT_SYNTAX_exp exp,
	int out_edges[MAX_NUM_ASM_COMMANDS][2],
	int command)
{
	out_edges[command][0]=FindInstructionNumberOfLabel(exp->u.jump);
	out_edges[command][1]=-1;
}

void Build_Control_Flow_graph_Jump_And_link(
	ABSTRACT_SYNTAX_exp exp,
	int out_edges[MAX_NUM_ASM_COMMANDS][2],
	int command)
{
	out_edges[command][0]=-1;
	out_edges[command][1]=-1;
}

void Build_Control_Flow_graph_Jump_Register(
	ABSTRACT_SYNTAX_exp exp,
	int out_edges[MAX_NUM_ASM_COMMANDS][2],
	int command)
{
	out_edges[command][0]=-1;
	out_edges[command][1]=-1;
}

void Build_Control_Flow_graph(
	ABSTRACT_SYNTAX_exp exp,
	int out_edges[MAX_NUM_ASM_COMMANDS][2],
	int command)
{
	switch (exp->type) {
	case (ABSTRACT_SYNTAX_ADD_EXP_TYPE):
	case (ABSTRACT_SYNTAX_SUB_EXP_TYPE):
	case (ABSTRACT_SYNTAX_LOAD_EXP_TYPE):           
	case (ABSTRACT_SYNTAX_LABEL_EXP_TYPE):          
	case (ABSTRACT_SYNTAX_STORE_EXP_TYPE):          
	case (ABSTRACT_SYNTAX_MOVE_EXP_TYPE):           
	case (ABSTRACT_SYNTAX_MUL_EXP_TYPE):            
	case (ABSTRACT_SYNTAX_ADD_IMMEDIATE_EXP_TYPE):  
	case (ABSTRACT_SYNTAX_LOAD_IMMEDIATE_EXP_TYPE): Build_Control_Flow_graph_default(exp,out_edges,command);       break;
	case (ABSTRACT_SYNTAX_BEQ_EXP_TYPE):
	case (ABSTRACT_SYNTAX_BNE_EXP_TYPE):
	case (ABSTRACT_SYNTAX_BGT_EXP_TYPE):
	case (ABSTRACT_SYNTAX_BGE_EXP_TYPE):
	case (ABSTRACT_SYNTAX_BLT_EXP_TYPE):
	case (ABSTRACT_SYNTAX_BLE_EXP_TYPE):            Build_Control_Flow_graph_Branch(exp,out_edges,command);        break;
	case (ABSTRACT_SYNTAX_JUMP_EXP_TYPE):           Build_Control_Flow_graph_Jump(exp,out_edges,command);          break;
	case (ABSTRACT_SYNTAX_JUMP_AND_LINK_EXP_TYPE):  Build_Control_Flow_graph_Jump_And_link(exp,out_edges,command); break;
	case (ABSTRACT_SYNTAX_JUMP_REGISTER_EXP_TYPE):  Build_Control_Flow_graph_Jump_Register(exp,out_edges,command); break;
	}
}

int EQUAL(int a[MAX_NUM_ASM_COMMANDS],int b[MAX_NUM_ASM_COMMANDS])
{
	int i=0;
	int ret=1;

	for (i=0;i<MAX_NUM_ASM_COMMANDS;i++)
	{
		if (a[i] != b[i]) ret = 0;
	}

	return ret;
}

/********/
/* main */
/********/
int main(int argc,char **argv)
{
	int i=0;
	int j=0;
	int n=0;
	int temp=0;
	int command=0;
	int low[300];
	int high[300];
	int firstTime=0;
	int numCommands=0;
	int numTemporaries=221-100+1;
	char *filename = "../../../IR_&_MIPS_Gen/CodeGen/CodeGeneration/tiger_prog.s";
	
	
	int in[MAX_NUM_ASM_COMMANDS];
	int out[MAX_NUM_ASM_COMMANDS];
	int def[MAX_NUM_ASM_COMMANDS];
	int use[MAX_NUM_ASM_COMMANDS][2];
	int in_tag[MAX_NUM_ASM_COMMANDS];
	int out_tag[MAX_NUM_ASM_COMMANDS];
	int out_edges[MAX_NUM_ASM_COMMANDS][2];
	ABSTRACT_SYNTAX_expList expList;
	ABSTRACT_SYNTAX_expList AbstractSyntaxTree=NULL;
	FILE *fl=fopen("LivenessAnalysis.txt","w+t");

	/***********************/
	/* [0] Initializations */
	/***********************/
	memset(in,-1,sizeof(in));
	memset(use,0,sizeof(use));
	memset(def,0,sizeof(def));
	memset(out,-1,sizeof(out));
	memset(in_tag,-1,sizeof(in_tag));
	memset(out_tag,-1,sizeof(out_tag));

	/**********************************/
	/* [1] Build Abstract Syntax Tree */
	/**********************************/
	AbstractSyntaxTree = parse(filename);
	if (AbstractSyntaxTree == NULL) return 0;

	/*************************/
	/* [2] Build use and def */
	/*************************/
	for (expList=AbstractSyntaxTree,command=0;expList;expList=expList->tail,command++)
	{
		Build_Use_and_Def_from_Exp(expList->head,use,def,command);
	}
	numCommands=command;

	/*****************************************/
	/* [3] map labels to instruction numbers */
	/*****************************************/
	for (expList=AbstractSyntaxTree,command=0;expList;expList=expList->tail,command++)
	{
		if (expList->head->type == ABSTRACT_SYNTAX_LABEL_EXP_TYPE)
		{
			strcpy(instructionToLabel[command],expList->head->u.label);
		}
	}

	/************************/
	/* [4] Build flow graph */
	/************************/
	for (expList=AbstractSyntaxTree,command=0;expList;expList=expList->tail,command++)
	{
		Build_Control_Flow_graph(expList->head,out_edges,command);
	}

	/**************************************************/
	/* [5] Liveness analysis - one variable at a time */
	/**************************************************/
	for (temp=0;temp<numTemporaries;temp++)
	{
		memset(in, -1,sizeof(in));
		memset(out,-1,sizeof(out));

		do
		{
			for (n=0;n<numCommands;n++)
			{
				in_tag[ n] = in[ n];
				out_tag[n] = out[n];

				if ((use[n][0] == temp) || (use[n][1] == temp) || ((out[n] == 1) && (def[n] != temp)))
				{
					in[n]=1;
				}
				if ((in[out_edges[n][0]] == 1) || (in[out_edges[n][1]] == 1))
				{
					out[n]=1;
				}

			}
		}
		while ((!EQUAL(in,in_tag)) || (!EQUAL(out,out_tag)));

		fprintf(fl,"Temp_%d = [ ",100+temp);

		firstTime=1;
		low[temp]=-1;
		high[temp]=-1;

		for (n=0;n<numCommands;n++)
		{
			if ((in[n] == 1) || (out[n] == 1))
			{
				if (firstTime)
				{
					firstTime=0;
					low[temp]=n;
				}
				high[temp]=n;
				fprintf(fl,"%d ",n);
			}
		}

		fprintf(fl,"]\n");
	}

	fclose(fl);


	/************************************/
	/* [6] Construct Interference Graph */
	/************************************/
	fl=fopen("InterferenceGraph.txt","w+t");
	fprintf(fl,"graph\n{\n");

	//for (i = 0; i<numTemporaries; i++)
	for (i=1;i<numTemporaries;i++)
	{
		for (j=i+1;j<numTemporaries;j++)
		{
			if ((low[i] >= 0) && (low[j] >= 0))
			{
				if ((low[i] <= high[j]) && (low[j] <= high[i]))
				{
					fprintf(fl,"%d -- %d;\n",i,j);				
				}
			}
		}
	}

	fprintf(fl, "%d\n", -1);
	fprintf(fl,"}\n");
	fclose(fl);
}
