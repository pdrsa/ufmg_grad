main:
	addi x12, x0, -3	# x12 = -3
    addi x13, x0, 3		# x13 = 3
    jal x1, multiplica	# Chama Multiplica
    addi x12, x0, -3	# x12 = -3
    add x13, x0, x14	# x13 = multiplica(-3, 3)
    jal x1, multiplica	# Chama Multiplica
    jal x0, exit		# Vá para "exit"
multiplica:
	add x5, x0, x0		# x5 = 0
    beq x12, x0, return	# Se x12 == 0 Return
    beq x13, x0, return	# Se x13 == 0 Return
    blt x12, x0, if		# Se x12 < 0, vá para "if"
    jal x0, else		# Vá para "else"
if:
	beq x12, x0, return # Se x12 == 0 Return
    sub x5, x5, x13		# x5 -= x13
    addi x12, x12, 1	# x12++
    jal x0, if			# Vá para "if"
else:
	beq x12, x0, return	# Se x12 == 0 Return
    add x5, x5, x13		# x5 += x13
    addi x12, x12, -1	# x12--
return:
	add x14, x0, x5		# x14 = x5
	jalr x0, 0(x1)		# Volte para onde a função multiplica foi chamada
exit:					# Fim do Programa

