Label_0_PrintInt:

		 lw $a0, 0($sp)

		 li $v0, 1

		 syscall

		 jr $ra

AllocateRecord:

	 lw $a0, 0($sp)

	 li $v0, 9

	 syscall

	 add $t6, $sp, $a0 

	 addi $t3, $v0, 0 

	 initRecordAllocatedVariables:

		 lw $t2, 0($t6) 

		 sw $t2, 0($t3) 

		 addi $t6, $t6, -4 

		 addi $t3, $t3, 4 

		 addi $a0, $a0, -4 

		 bgt $a0, 0, initRecordAllocatedVariables

	 jr $ra 

AllocateArray:

	 lw $a0, 0($sp)

	 li $v0, 9

	 syscall

	 addi $t6, $sp, 4 

	 addi $t3, $v0, 0 

	 initArrayAllocatedVariables:

		 lw $t2, 0($t6) 

		 sw $t2, 0($t3) 

		 addi $t6, $t6, 4 

		 addi $t3, $t3, 4 

		 addi $a0, $a0, -4 

		 bgt $a0, 0, initArrayAllocatedVariables

	 jr $ra 

main:

jal Label_0_main

Label_0_main:

	addi $fp,$sp,40

	j Label_4_Skip_This_Function_For_Now

Label_5_PrintPrimesInRange:

	 li Temp_112,4

	sub Temp_111,$sp,Temp_112

	addi $sp,Temp_111,0

	sw $ra,0($sp)

	 li Temp_114,4

	sub Temp_113,$sp,Temp_114

	addi $sp,Temp_113,0

	sw $fp,0($sp)

	addi $fp,$sp,0

	 li Temp_116,4

	sub Temp_115,$sp,Temp_116

	addi $sp,Temp_115,0

	j Label_6_Skip_This_Function_For_Now

Label_7_IsPrime:

	 li Temp_118,4

	sub Temp_117,$sp,Temp_118

	addi $sp,Temp_117,0

	sw $ra,0($sp)

	 li Temp_120,4

	sub Temp_119,$sp,Temp_120

	addi $sp,Temp_119,0

	sw $fp,0($sp)

	addi $fp,$sp,0

	 li Temp_122,12

	sub Temp_121,$sp,Temp_122

	addi $sp,Temp_121,0

	 li Temp_124,-4

	add Temp_123,$fp,Temp_124

	 li Temp_125,1

	sw Temp_125,0(Temp_123)

	 li Temp_127,-8

	add Temp_126,$fp,Temp_127

	 li Temp_128,2

	sw Temp_128,0(Temp_126)

Label_10_for_check:

	 li Temp_131,-8

	add Temp_130,$fp,Temp_131

	lw Temp_129,0(Temp_130)

	 li Temp_135,8

	add Temp_134,$fp,Temp_135

	lw Temp_133,0(Temp_134)

	 li Temp_136,1

	sub Temp_132,Temp_133,Temp_136

	ble Temp_129, Temp_132, Label_8_for_loop

	bgt Temp_129, Temp_132, Label_9_exit_loop

Label_8_for_loop:

	 li Temp_138,-12

	add Temp_137,$fp,Temp_138

	 li Temp_139,2

	sw Temp_139,0(Temp_137)

Label_19_for_check:

	 li Temp_142,-12

	add Temp_141,$fp,Temp_142

	lw Temp_140,0(Temp_141)

	 li Temp_146,8

	add Temp_145,$fp,Temp_146

	lw Temp_144,0(Temp_145)

	 li Temp_147,1

	sub Temp_143,Temp_144,Temp_147

	ble Temp_140, Temp_143, Label_17_for_loop

	bgt Temp_140, Temp_143, Label_18_exit_loop

Label_17_for_loop:

	 li Temp_151,-8

	add Temp_150,$fp,Temp_151

	lw Temp_149,0(Temp_150)

	 li Temp_154,-12

	add Temp_153,$fp,Temp_154

	lw Temp_152,0(Temp_153)

	mul Temp_148,Temp_149,Temp_152

	 li Temp_157,8

	add Temp_156,$fp,Temp_157

	lw Temp_155,0(Temp_156)

	beq Temp_148, Temp_155, Label_28_T

	bne Temp_148, Temp_155, Label_29_F

Label_28_T:

	 li Temp_158,1

	addi Temp_109,Temp_158,0

	j Label_30_END

Label_29_F:

	 li Temp_159,0

	addi Temp_109,Temp_159,0

	j Label_30_END

Label_30_END:

	 li Temp_160,0

	bne Temp_109, Temp_160, Label_26_if_taken

	beq Temp_109, Temp_160, Label_27_if_not_taken

Label_26_if_taken:

	 li Temp_162,-4

	add Temp_161,$fp,Temp_162

	 li Temp_163,0

	sw Temp_163,0(Temp_161)

Label_27_if_not_taken:

	 li Temp_165,-12

	add Temp_164,$fp,Temp_165

	 li Temp_169,-12

	add Temp_168,$fp,Temp_169

	lw Temp_167,0(Temp_168)

	 li Temp_170,1

	add Temp_166,Temp_167,Temp_170

	sw Temp_166,0(Temp_164)

	j Label_19_for_check

Label_18_exit_loop:

	 li Temp_172,-8

	add Temp_171,$fp,Temp_172

	 li Temp_176,-8

	add Temp_175,$fp,Temp_176

	lw Temp_174,0(Temp_175)

	 li Temp_177,1

	add Temp_173,Temp_174,Temp_177

	sw Temp_173,0(Temp_171)

	j Label_10_for_check

Label_9_exit_loop:

	 li Temp_180,-4

	add Temp_179,$fp,Temp_180

	lw Temp_178,0(Temp_179)

	addi $v0,Temp_178,0

	addi $sp,$fp,0

	lw Temp_182,0($sp)

	addi $fp,Temp_182,0

	 li Temp_184,4

	add Temp_183,$sp,Temp_184

	addi $sp,Temp_183,0

	lw Temp_185,0($sp)

	addi $ra,Temp_185,0

	 li Temp_187,4

	add Temp_186,$sp,Temp_187

	addi $sp,Temp_186,0

	jr $ra

Label_6_Skip_This_Function_For_Now:

	 li Temp_189,-4

	add Temp_188,$fp,Temp_189

	 li Temp_192,8

	add Temp_191,$fp,Temp_192

	lw Temp_190,0(Temp_191)

	sw Temp_190,0(Temp_188)

Label_36_for_check:

	 li Temp_195,-4

	add Temp_194,$fp,Temp_195

	lw Temp_193,0(Temp_194)

	 li Temp_198,12

	add Temp_197,$fp,Temp_198

	lw Temp_196,0(Temp_197)

	ble Temp_193, Temp_196, Label_34_for_loop

	bgt Temp_193, Temp_196, Label_35_exit_loop

Label_34_for_loop:

	 addi $sp, $sp, -32 

	 sw $t0, 0($sp)

	 sw $t1, 4($sp)

	 sw $t2, 8($sp)

	 sw $t3, 12($sp)

	 sw $t4, 16($sp)

	 sw $t5, 20($sp)

	 sw $t6, 24($sp)

	 sw $t7, 28($sp)

	 li Temp_201,-4

	add Temp_200,$fp,Temp_201

	lw Temp_199,0(Temp_200)

	 addi $sp, $sp, -4

	 sw Temp_199, 0($sp)

	jal Label_7_IsPrime

	 addi $sp, $sp, 4

	 lw $t0, 0($sp)

	 lw $t1, 4($sp)

	 lw $t2, 8($sp)

	 lw $t3, 12($sp)

	 lw $t4, 16($sp)

	 lw $t5, 20($sp)

	 lw $t6, 24($sp)

	 lw $t7, 28($sp)

	 addi $sp, $sp, 32 

	 li Temp_202,0

	bne $v0, Temp_202, Label_37_if_taken

	beq $v0, Temp_202, Label_38_if_not_taken

Label_37_if_taken:

	 addi $sp, $sp, -32 

	 sw $t0, 0($sp)

	 sw $t1, 4($sp)

	 sw $t2, 8($sp)

	 sw $t3, 12($sp)

	 sw $t4, 16($sp)

	 sw $t5, 20($sp)

	 sw $t6, 24($sp)

	 sw $t7, 28($sp)

	 li Temp_205,-4

	add Temp_204,$fp,Temp_205

	lw Temp_203,0(Temp_204)

	 addi $sp, $sp, -4

	 sw Temp_203, 0($sp)

	jal Label_0_PrintInt

	 addi $sp, $sp, 4

	 lw $t0, 0($sp)

	 lw $t1, 4($sp)

	 lw $t2, 8($sp)

	 lw $t3, 12($sp)

	 lw $t4, 16($sp)

	 lw $t5, 20($sp)

	 lw $t6, 24($sp)

	 lw $t7, 28($sp)

	 addi $sp, $sp, 32 

Label_38_if_not_taken:

	 li Temp_207,-4

	add Temp_206,$fp,Temp_207

	 li Temp_211,-4

	add Temp_210,$fp,Temp_211

	lw Temp_209,0(Temp_210)

	 li Temp_212,1

	add Temp_208,Temp_209,Temp_212

	sw Temp_208,0(Temp_206)

	j Label_36_for_check

Label_35_exit_loop:

	addi $sp,$fp,0

	lw Temp_213,0($sp)

	addi $fp,Temp_213,0

	 li Temp_215,4

	add Temp_214,$sp,Temp_215

	addi $sp,Temp_214,0

	lw Temp_216,0($sp)

	addi $ra,Temp_216,0

	 li Temp_218,4

	add Temp_217,$sp,Temp_218

	addi $sp,Temp_217,0

	jr $ra

Label_4_Skip_This_Function_For_Now:

	 addi $sp, $sp, -32 

	 sw $t0, 0($sp)

	 sw $t1, 4($sp)

	 sw $t2, 8($sp)

	 sw $t3, 12($sp)

	 sw $t4, 16($sp)

	 sw $t5, 20($sp)

	 sw $t6, 24($sp)

	 sw $t7, 28($sp)

	 li Temp_219,25

	 addi $sp, $sp, -4

	 sw Temp_219, 0($sp)

	 li Temp_220,1

	 addi $sp, $sp, -4

	 sw Temp_220, 0($sp)

	jal Label_5_PrintPrimesInRange

	 addi $sp, $sp, 8

	 lw $t0, 0($sp)

	 lw $t1, 4($sp)

	 lw $t2, 8($sp)

	 lw $t3, 12($sp)

	 lw $t4, 16($sp)

	 lw $t5, 20($sp)

	 lw $t6, 24($sp)

	 lw $t7, 28($sp)

	 addi $sp, $sp, 32 

li $v0, 10

syscall