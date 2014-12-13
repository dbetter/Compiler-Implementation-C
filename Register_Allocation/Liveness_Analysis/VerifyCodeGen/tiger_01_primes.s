main:

	j Label_4_Skip_This_Function_For_Now

Label_5_PrintPrimesInRange:

	sw $ra,0($sp)

	li Temp_112,4

	sub Temp_111,$sp,Temp_112

	addi $sp,Temp_111,0

	sw $fp,0($sp)

	li Temp_114,4

	sub Temp_113,$sp,Temp_114

	addi $sp,Temp_113,0

	addi $fp,$sp,0

	li Temp_116,20

	sub Temp_115,$sp,Temp_116

	addi $sp,Temp_115,0

	j Label_6_Skip_This_Function_For_Now

Label_7_IsPrime:

	sw $ra,0($sp)

	li Temp_118,4

	sub Temp_117,$sp,Temp_118

	addi $sp,Temp_117,0

	sw $fp,0($sp)

	li Temp_120,4

	sub Temp_119,$sp,Temp_120

	addi $sp,Temp_119,0

	addi $fp,$sp,0

	li Temp_122,28

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

	li Temp_129,2

	li Temp_133,8

	add Temp_132,$fp,Temp_133

	lw Temp_131,0(Temp_132)

	li Temp_134,1

	sub Temp_130,Temp_131,Temp_134

	ble Temp_129, Temp_130, Label_8_for_loop

	bgt Temp_129, Temp_130, Label_9_exit_loop

Label_8_for_loop:

	li Temp_136,-12

	add Temp_135,$fp,Temp_136

	li Temp_137,2

	sw Temp_137,0(Temp_135)

	li Temp_138,2

	li Temp_142,8

	add Temp_141,$fp,Temp_142

	lw Temp_140,0(Temp_141)

	li Temp_143,1

	sub Temp_139,Temp_140,Temp_143

	ble Temp_138, Temp_139, Label_16_for_loop

	bgt Temp_138, Temp_139, Label_17_exit_loop

Label_16_for_loop:

	li Temp_147,-8

	add Temp_146,$fp,Temp_147

	lw Temp_145,0(Temp_146)

	li Temp_150,-12

	add Temp_149,$fp,Temp_150

	lw Temp_148,0(Temp_149)

	mul Temp_144,Temp_145,Temp_148

	li Temp_153,8

	add Temp_152,$fp,Temp_153

	lw Temp_151,0(Temp_152)

	beq Temp_144, Temp_151, Label_26_T

	bne Temp_144, Temp_151, Label_27_F

Label_26_T:

	li Temp_154,1

	addi Temp_108,Temp_154,0

	j Label_28_END

Label_27_F:

	li Temp_155,0

	addi Temp_108,Temp_155,0

	j Label_28_END

Label_28_END:

	li Temp_156,0

	bne Temp_108, Temp_156, Label_24_if_taken

	beq Temp_108, Temp_156, Label_25_if_not_taken

Label_24_if_taken:

	li Temp_158,-4

	add Temp_157,$fp,Temp_158

	li Temp_159,0

	sw Temp_159,0(Temp_157)

Label_25_if_not_taken:

	li Temp_161,-12

	add Temp_160,$fp,Temp_161

	li Temp_165,-12

	add Temp_164,$fp,Temp_165

	lw Temp_163,0(Temp_164)

	li Temp_166,1

	add Temp_162,Temp_163,Temp_166

	sw Temp_162,0(Temp_160)

	li Temp_169,-12

	add Temp_168,$fp,Temp_169

	lw Temp_167,0(Temp_168)

	li Temp_173,8

	add Temp_172,$fp,Temp_173

	lw Temp_171,0(Temp_172)

	li Temp_174,1

	sub Temp_170,Temp_171,Temp_174

	blt Temp_167, Temp_170, Label_16_for_loop

	bge Temp_167, Temp_170, Label_17_exit_loop

Label_17_exit_loop:

	li Temp_176,-8

	add Temp_175,$fp,Temp_176

	li Temp_180,-8

	add Temp_179,$fp,Temp_180

	lw Temp_178,0(Temp_179)

	li Temp_181,1

	add Temp_177,Temp_178,Temp_181

	sw Temp_177,0(Temp_175)

	li Temp_184,-8

	add Temp_183,$fp,Temp_184

	lw Temp_182,0(Temp_183)

	li Temp_188,8

	add Temp_187,$fp,Temp_188

	lw Temp_186,0(Temp_187)

	li Temp_189,1

	sub Temp_185,Temp_186,Temp_189

	blt Temp_182, Temp_185, Label_8_for_loop

	bge Temp_182, Temp_185, Label_9_exit_loop

Label_9_exit_loop:

	li Temp_192,-4

	add Temp_191,$fp,Temp_192

	lw Temp_190,0(Temp_191)

	addi $rv,Temp_190,0

	addi $sp,$fp,0

	lw Temp_194,0($sp)

	addi $fp,Temp_194,0

	li Temp_196,4

	add Temp_195,$sp,Temp_196

	addi $sp,Temp_195,0

	lw Temp_197,0($sp)

	addi $ra,Temp_197,0

	li Temp_199,4

	add Temp_198,$sp,Temp_199

	addi $sp,Temp_198,0

	jr $ra

Label_6_Skip_This_Function_For_Now:

	li Temp_201,-4

	add Temp_200,$fp,Temp_201

	li Temp_204,8

	add Temp_203,$fp,Temp_204

	lw Temp_202,0(Temp_203)

	sw Temp_202,0(Temp_200)

	li Temp_207,8

	add Temp_206,$fp,Temp_207

	lw Temp_205,0(Temp_206)

	li Temp_210,12

	add Temp_209,$fp,Temp_210

	lw Temp_208,0(Temp_209)

	ble Temp_205, Temp_208, Label_32_for_loop

	bgt Temp_205, Temp_208, Label_33_exit_loop

Label_32_for_loop:

	li Temp_213,-4

	add Temp_212,$fp,Temp_213

	lw Temp_211,0(Temp_212)

	sw Temp_211,0($sp)

	addi $sp,$sp,-4

	jal Label_7_IsPrime

	addi $sp,$sp,4

	li Temp_214,0

	bne $rv, Temp_214, Label_34_if_taken

	beq $rv, Temp_214, Label_35_if_not_taken

Label_34_if_taken:

	li Temp_217,-4

	add Temp_216,$fp,Temp_217

	lw Temp_215,0(Temp_216)

	sw Temp_215,0($sp)

	addi $sp,$sp,-4

	jal Label_0_PrintInt

	addi $sp,$sp,4

Label_35_if_not_taken:

	li Temp_219,-4

	add Temp_218,$fp,Temp_219

	li Temp_223,-4

	add Temp_222,$fp,Temp_223

	lw Temp_221,0(Temp_222)

	li Temp_224,1

	add Temp_220,Temp_221,Temp_224

	sw Temp_220,0(Temp_218)

	li Temp_227,-4

	add Temp_226,$fp,Temp_227

	lw Temp_225,0(Temp_226)

	li Temp_230,12

	add Temp_229,$fp,Temp_230

	lw Temp_228,0(Temp_229)

	blt Temp_225, Temp_228, Label_32_for_loop

	bge Temp_225, Temp_228, Label_33_exit_loop

Label_33_exit_loop:

	addi $sp,$fp,0

	lw Temp_231,0($sp)

	addi $fp,Temp_231,0

	li Temp_233,4

	add Temp_232,$sp,Temp_233

	addi $sp,Temp_232,0

	lw Temp_234,0($sp)

	addi $ra,Temp_234,0

	li Temp_236,4

	add Temp_235,$sp,Temp_236

	addi $sp,Temp_235,0

	jr $ra

Label_4_Skip_This_Function_For_Now:

	li Temp_237,100

	sw Temp_237,0($sp)

	addi $sp,$sp,-4

	li Temp_238,2

	sw Temp_238,0($sp)

	addi $sp,$sp,-4

	jal Label_5_PrintPrimesInRange

	addi $sp,$sp,8
