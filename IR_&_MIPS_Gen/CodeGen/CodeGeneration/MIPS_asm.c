/*************************/
/* FILE NAME: MIPS_asm.c */
/*************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "../../COMMON_H_FILES/tree.h"
#include "../../COMMON_H_FILES/frame.h"


/********************/
/* GLOBAL VARIABLES */
/********************/
FILE *fl=NULL;

/************************************/
/* MIPS_ASM_ALLOCATE_IMPLEMENTATION */
/************************************/
void MIPS_ASM_ALLOCATE_IMPLEMENTATION(void)
{
	fprintf(fl, "Label_0_PrintInt:\n\n");
		fprintf(fl, "\t\t lw $a0, 0($sp)\n\n");								// load a0 with the parameter to print from the top of the stack
		fprintf(fl, "\t\t li $v0, 1\n\n");									// load v0 with code for print syscall
		fprintf(fl, "\t\t syscall\n\n");
		fprintf(fl, "\t\t jr $ra\n\n");


	fprintf(fl,"AllocateRecord:\n\n");
		fprintf(fl, "\t lw $a0, 0($sp)\n\n");								// $a0 now holds the overall number of bytes needed to allocate
		fprintf(fl, "\t li $v0, 9\n\n");									// place '9' to $v0 as to initate a sbrk syscall
		fprintf(fl, "\t syscall\n\n");										// initiate syscall 9 (sbrk) to allocate on the heap
		fprintf(fl, "\t add $t6, $sp, $a0 \n\n");							// $t6 = $sp, we will treverse the stack using $t6 as to not harm $sp	
		fprintf(fl, "\t addi $t3, $v0, 0 \n\n");							// $t3 = $v0, we will init the heap-space gave to us by treversing the heap using $t3

	fprintf(fl, "\t initRecordAllocatedVariables:\n\n");
		fprintf(fl, "\t\t lw $t2, 0($t6) \n\n");							// move the parameter in [t6] to register $t2
		fprintf(fl, "\t\t sw $t2, 0($t3) \n\n");							// store the parameter $t2 holds to 0[t3]
		fprintf(fl, "\t\t addi $t6, $t6, -4 \n\n");
		fprintf(fl, "\t\t addi $t3, $t3, 4 \n\n");
		fprintf(fl, "\t\t addi $a0, $a0, -4 \n\n");							// we've finished one iteration of the the 'loop' so decrement 4 bytes from the num in $a0
		fprintf(fl, "\t\t bgt $a0, 0, initRecordAllocatedVariables\n\n");	// check if $a0 value greater then zero, if so jmp to initAllocatedVariables label

	fprintf(fl, "\t jr $ra \n\n");
	


	/****************************** Allocate array part *******************************/

	fprintf(fl, "AllocateArray:\n\n");
	fprintf(fl, "\t lw $a0, 0($sp)\n\n");									// $a0 now holds the overall number of bytes needed to allocate
	fprintf(fl, "\t li $v0, 9\n\n");										// place '9' to $v0 as to initate a sbrk syscall
	fprintf(fl, "\t syscall\n\n");											// initiate syscall 9 (sbrk) to allocate on the heap
	fprintf(fl, "\t addi $t6, $sp, 4 \n\n");								// $t6 = $sp+4 (+4 to skip through the ra), we will treverse the stack using $t6 as to not harm $sp
	fprintf(fl, "\t addi $t3, $v0, 0 \n\n");								// $t3 = $v0, we will init the heap-space gave to us by treversing the heap using $t3

	fprintf(fl, "\t initArrayAllocatedVariables:\n\n");
		fprintf(fl, "\t\t lw $t2, 0($t6) \n\n");							// move the parameter in [fp] to register $t2
		fprintf(fl, "\t\t sw $t2, 0($t3) \n\n");							// store the parameter $t2 holds to 0[t3]
		fprintf(fl, "\t\t addi $t6, $t6, 4 \n\n");
		fprintf(fl, "\t\t addi $t3, $t3, 4 \n\n");
		fprintf(fl, "\t\t addi $a0, $a0, -4 \n\n");							// we've finished one iteration of the the 'loop' so decrement 4 bytes from the num in $a0
		fprintf(fl, "\t\t bgt $a0, 0, initArrayAllocatedVariables\n\n");	// check if $a0 value is greater then zero, if so jmp to initAllocatedVariables label

	fprintf(fl, "\t jr $ra \n\n");


}

/*****************/
/* ASM_MIPS_Init */
/*****************/
void MIPS_ASM_Init()
{
	/*******************/
	/* Allocation Code */
	/*******************/
	MIPS_ASM_ALLOCATE_IMPLEMENTATION();

	/***************/
	/* Entry Point */
	/***************/
	fprintf(fl,"main:\n\n");
	fprintf(fl, "jal Label_0_main\n\n");

	fprintf(fl, "Label_0_main:\n\n");
	fprintf(fl, "\taddi %s,%s,40\n\n", Temp_look(Temp_name(), FP()), Temp_look(Temp_name(), SP()));
}

/**********************/
/* ASM_MIPS_Terminate */
/**********************/
void MIPS_ASM_Terminate()
{
	fprintf(fl,"li $v0, 10\n\n");
	fprintf(fl,"syscall");
}

/***********************/
/* FUNCTION PROTOTYPES */
/***********************/
static Temp_temp MIPS_ASM_codeGeneration(T_exp IR_tree);

const char *Convert_IR_Binops_To_MIPS_ASM_Binops(T_binOp binop)
{
	switch (binop) {
	case (T_plus):   return "add";
	case (T_minus):  return "sub";
	case (T_mul):    return "mul";
	case (T_div):    return "div";
	case (T_and):    return "and";
	case (T_or):     return "or";
	}
}
Temp_temp MIPS_ASM_CodeGeneration_Seq(T_exp t)
{
	/**********************/
	/* [1] first left son */
	/**********************/
	(void) MIPS_ASM_codeGeneration(t->u.SEQ.left);

	/***********************************************/
	/* [2] then return the result of the right son */
	/***********************************************/
 	return MIPS_ASM_codeGeneration(t->u.SEQ.right);
}

Temp_temp MIPS_ASM_CodeGeneration_Mem(T_exp t)
{
	/********************************/
	/* [0] allocate a new temporary */
	/********************************/
	Temp_temp r = Temp_newtemp("");

	/************************************************/
	/* [1] compute memory address, and move it to s */
	/************************************************/
	Temp_temp s = MIPS_ASM_codeGeneration(t->u.MEM);

	/******************************************/
	/* [2] get memory contents from address s */
	/******************************************/
	fprintf(fl,"\tlw %s,0(%s)\n\n",Temp_look(Temp_name(),r),Temp_look(Temp_name(),s));

	/****************/
	/* [3] return r */
	/****************/
	return r;
}

Temp_temp MIPS_ASM_CodeGeneration_Call(T_exp t)
{
	Temp_temp arg;
	int numParameters=0;
	T_expList expList=t->u.CALL.args;

	/*********************************************************************************/
	/* [0] - Our Addition: push registers $t0 - $t7 to our stack
	/* the conventation we take to consideration here is:
	/* SP will point at the last used cell on the stack
	/* (another method would be - SP will point to the first free-cell on the stack
	/********************************************************************************/
	
	
	fprintf(fl, "\t addi $sp, $sp, -32 \n\n");
	fprintf(fl, "\t sw $t0, 0($sp)\n\n");
	fprintf(fl, "\t sw $t1, 4($sp)\n\n");
	fprintf(fl, "\t sw $t2, 8($sp)\n\n");
	fprintf(fl, "\t sw $t3, 12($sp)\n\n");
	fprintf(fl, "\t sw $t4, 16($sp)\n\n");
	fprintf(fl, "\t sw $t5, 20($sp)\n\n");
	fprintf(fl, "\t sw $t6, 24($sp)\n\n");
	fprintf(fl, "\t sw $t7, 28($sp)\n\n");

	/***********************************/
	/* [1] pass all arguments on stack */
	/***********************************/
	for (expList = t->u.CALL.args; expList; expList=expList->tail)
	{
		/********/
		/* TODO */
		/********/
		numParameters++;
		arg = MIPS_ASM_codeGeneration(expList->head);
		fprintf(fl, "\t addi $sp, $sp, -4\n\n");						   	 // Decrement stack-pointer by 4 to deploy room for the param to be pushed
		fprintf(fl, "\t sw %s, 0($sp)\n\n", Temp_look(Temp_name(), arg));	 // save arg (which is $temp_something) to stack
	}


	/***********************************************************************/
	/* [2] jump to function and remember the PC to know where to return to */
	/***********************************************************************/
	fprintf(fl,"\tjal %s\n\n",Temp_labelstring(t->u.CALL.name));
	
	
	/******************************************/
	/* [3] pop outgoing parameters from stack */
	/******************************************/
	fprintf(fl, "\t addi $sp, $sp, %d\n\n", numParameters * 4);



	/***********************************************************************/
	/* [3.1] - Our Addition: pop registers $t0 - $t7 from our stack
	/***********************************************************************/
	
	fprintf(fl, "\t lw $t0, 0($sp)\n\n");
	fprintf(fl, "\t lw $t1, 4($sp)\n\n");
	fprintf(fl, "\t lw $t2, 8($sp)\n\n");
	fprintf(fl, "\t lw $t3, 12($sp)\n\n");
	fprintf(fl, "\t lw $t4, 16($sp)\n\n");
	fprintf(fl, "\t lw $t5, 20($sp)\n\n");
	fprintf(fl, "\t lw $t6, 24($sp)\n\n");
	fprintf(fl, "\t lw $t7, 28($sp)\n\n");
	fprintf(fl, "\t addi $sp, $sp, 32 \n\n");


	/********************/
	/* [4] return value */
	/********************/
	return RV();
}

Temp_temp MIPS_ASM_CodeGeneration_Temp(T_exp t)
{
	/*******************/
	/* [1] clearly ... */
	/*******************/
	return t->u.TEMP;
}

Temp_temp MIPS_ASM_CodeGeneration_Jump(T_exp t)
{
	if (t->u.JUMP.type == T_JUMP_LABEL)
	{
		fprintf(fl,"\tj %s\n\n",Temp_labelstring(t->u.JUMP.u.label));
	}
	if (t->u.JUMP.type == T_JUMP_REGISTER)
	{
		fprintf(fl,"\tjr %s\n\n",Temp_look(Temp_name(),t->u.JUMP.u.temp));
	}
}

Temp_temp MIPS_ASM_CodeGeneration_Move(T_exp t)
{
	if (t->u.MOVE.dst->kind == T_TEMP)
	{
		/***********************************/
		/* [1] move dst expression to temp */
		/***********************************/
		Temp_temp dst = MIPS_ASM_codeGeneration(t->u.MOVE.dst);

		/***********************************/
		/* [2] move src expression to temp */
		/***********************************/
		Temp_temp src = MIPS_ASM_codeGeneration(t->u.MOVE.src);

		/*********************************/
		/* [3] generate move instruction */
		/*********************************/
		fprintf(fl,"\taddi %s,%s,0\n\n",Temp_look(Temp_name(),dst),Temp_look(Temp_name(),src));
	}
	if (t->u.MOVE.dst->kind == T_MEM)
	{
		/***********************************/
		/* [1] move dst expression to temp */
		/***********************************/
		Temp_temp dst = MIPS_ASM_codeGeneration(t->u.MOVE.dst->u.MEM);

		/***********************************/
		/* [2] move src expression to temp */
		/***********************************/
		Temp_temp src = MIPS_ASM_codeGeneration(t->u.MOVE.src);

		/**********************************/
		/* [3] generate store instruction */
		/**********************************/
		if (Temp_look(Temp_name(), src) == "$v0"){

		}
		else{
			fprintf(fl, "\tsw %s,0(%s)\n\n", Temp_look(Temp_name(), src), Temp_look(Temp_name(), dst));
		}
		
	}
}

Temp_temp MIPS_ASM_CodeGeneration_Binop(T_exp t)
{
	/***********************************************/
	/* [0] allocate a new temporary for the result */
	/***********************************************/
	Temp_temp t1 = Temp_newtemp("");

	/*****************************************/
	/* [1] move left operand to t2 temporary */
	/*****************************************/
	Temp_temp t2 = MIPS_ASM_codeGeneration(t->u.BINOP.left);

	/******************************************/
	/* [2] move right operand to t3 temporary */
	/******************************************/
	Temp_temp t3 = MIPS_ASM_codeGeneration(t->u.BINOP.right);

	/**********************************/
	/* [3] generate binop instruction */
	/**********************************/
	fprintf(
		fl,
		"\t%s %s,%s,%s\n\n",
		Convert_IR_Binops_To_MIPS_ASM_Binops(t->u.BINOP.op),
		Temp_look(Temp_name(),t1),
		Temp_look(Temp_name(),t2),
		Temp_look(Temp_name(),t3));

	/*********************/
	/* [4] return result */
	/*********************/
	return t1;
}

Temp_temp MIPS_ASM_CodeGeneration_Label(T_exp t)
{
	/*********************/
	/* [1] that's it ... */
	/*********************/
	fprintf(fl,"%s:\n\n",Temp_labelstring(t->u.LABEL));

	/**************/
	/* [2] return */
	/**************/
	return NULL;
}

Temp_temp MIPS_ASM_CodeGeneration_Const(T_exp t)
{
	Temp_temp r = Temp_newtemp("");

	/****************/
	/* [1] easy ... */
	/****************/
	fprintf(fl,"\t li %s,%d\n\n",Temp_look(Temp_name(),r),t->u.CONST);

	/**************/
	/* [2] return */
	/**************/
	return r;
}

Temp_temp MIPS_ASM_CodeGeneration_Cjump(T_exp t)
{
	Temp_temp operand1 = MIPS_ASM_codeGeneration(t->u.CJUMP.left);
	Temp_temp operand2 = MIPS_ASM_codeGeneration(t->u.CJUMP.right);

	string op1_name = Temp_look(Temp_name(),operand1);
	string op2_name = Temp_look(Temp_name(),operand2);

	string jumpToHereIfTrue = Temp_labelstring(t->u.CJUMP.jumpToHereIfTrue);
	string jumpToHereIfFalse = Temp_labelstring(t->u.CJUMP.jumpToHereIfFalse);

	switch (t->u.CJUMP.op) {
	case (T_eq):

		fprintf(fl,"\tbeq %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfTrue);
		fprintf(fl,"\tbne %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfFalse);
		break;

	case (T_ne):

		fprintf(fl,"\tbne %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfTrue);
		fprintf(fl,"\tbeq %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfFalse);
		break;

	case (T_lt):

		fprintf(fl,"\tblt %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfTrue);
		fprintf(fl,"\tbge %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfFalse);
		break;

	case (T_gt):

		fprintf(fl,"\tbgt %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfTrue);
		fprintf(fl,"\tble %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfFalse);
		break;

	case (T_le):

		fprintf(fl,"\tble %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfTrue);
		fprintf(fl,"\tbgt %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfFalse);
		break;

	case (T_ge):

		fprintf(fl,"\tbge %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfTrue);
		fprintf(fl,"\tblt %s, %s, %s\n\n",op1_name,op2_name,jumpToHereIfFalse);
		break;
	}

	return NULL;
}

Temp_temp MIPS_ASM_CodeGeneration_Function(T_exp t)
{
	Temp_temp returned_value;

	/***************************/
	/* [0] print function name */
	/***************************/
	fprintf(fl,"%s:\n\n",Temp_labelstring(t->u.FUNCTION.name));

	/*************************/
	/* [1] generate prologue */
	/*************************/
	(void) MIPS_ASM_codeGeneration(t->u.FUNCTION.prologue);

	/******************************************/
	/* [2] generate code for body of function */
	/******************************************/
	returned_value = MIPS_ASM_codeGeneration(t->u.FUNCTION.body);

	/**************************************************/
	/* [3] check if function return value is not void */
	/**************************************************/
	if (returned_value != NULL)
	{
		/*******************************************/
		/* [4] move returned_value temporary to RV */
		/*******************************************/
		fprintf(fl,"\taddi %s,%s,0\n\n",Temp_look(Temp_name(),RV()),Temp_look(Temp_name(),returned_value));

		/*************************/
		/* [5] generate epilogue */
		/*************************/
		(void) MIPS_ASM_codeGeneration(t->u.FUNCTION.epilogue);

		/********************/
		/* [6] return value */
		/********************/
		return RV();
	}

	/**********************************************/
	/* [7] no return value - just do the epilogue */
	/**********************************************/
	if (returned_value == NULL)
	{
		/*************************/
		/* [8] generate epilogue */
		/*************************/
		(void) MIPS_ASM_codeGeneration(t->u.FUNCTION.epilogue);

		/********************/
		/* [9] return value */
		/********************/
		return NULL;
	}
}

Temp_temp MIPS_ASM_codeGeneration(T_exp IR_tree)
{
	if (IR_tree)
	{
		switch (IR_tree->kind)
		{
		case (T_SEQ):     return MIPS_ASM_CodeGeneration_Seq(     IR_tree);
		case (T_MEM):     return MIPS_ASM_CodeGeneration_Mem(     IR_tree);
		case (T_CALL):    return MIPS_ASM_CodeGeneration_Call(    IR_tree);
		case (T_TEMP):    return MIPS_ASM_CodeGeneration_Temp(    IR_tree);
		case (T_JUMP):    return MIPS_ASM_CodeGeneration_Jump(    IR_tree);
		case (T_MOVE):    return MIPS_ASM_CodeGeneration_Move(    IR_tree);
		case (T_BINOP):   return MIPS_ASM_CodeGeneration_Binop(   IR_tree);
		case (T_LABEL):   return MIPS_ASM_CodeGeneration_Label(   IR_tree);
		case (T_CJUMP):   return MIPS_ASM_CodeGeneration_Cjump(   IR_tree);
		case (T_CONST):   return MIPS_ASM_CodeGeneration_Const(   IR_tree);
		case (T_FUNCTION):return MIPS_ASM_CodeGeneration_Function(IR_tree);
		}
	}
}

/***************************/
/* ASM_MIPS_codeGeneration */
/***************************/
void MIPS_ASM_CodeGeneration(T_exp IR_tree,const char *mips_asm_output_filename)
{
	/************************/
	/* [0] Open output file */
	/************************/
	fl=fopen(mips_asm_output_filename,"w+t");

	/********************/
	/* [1] Write header */
	/********************/
	MIPS_ASM_Init();

	/************************************/
	/* [2] Generate MIPS assembler code */
	/************************************/
	MIPS_ASM_codeGeneration(IR_tree);

	/**********************/
	/* [3] Write epilogue */
	/**********************/
	MIPS_ASM_Terminate();

	/*************************/
	/* [4] Close output file */
	/*************************/
	fclose(fl);
}
