main:
	addi x10, x0, 1		# Atribui um valor à x10 (Define a precisão)
    addi x5, x5, 1		# x5 = 1
loop:
    beq x10, x0, exit	# Se x10 == 0, vá para "exit"
	add x6, x0, x5		# x6 = x5
    addi x7, x0, 1		# x7 = 1
	div x5, x7, x6		# x5 = 1/x6
    add x5, x5, x7		# x5 += 1
    addi x10, x10, -1	# x10--
    jal x0, loop		# Vá para "loop"
exit:					# Termina o programa

