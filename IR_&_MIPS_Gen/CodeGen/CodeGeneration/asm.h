#ifndef __ASM_H__
#define __ASM_H__

/*****************/
/* INCLUDE FILES */
/*****************/
#include "../../COMMON_H_FILES/tree.h"
#include "../../COMMON_H_FILES/temp.h"


void MIPS_ASM_CodeGeneration(T_exp IR_tree,const char *mips_asm_output_filename);

#endif