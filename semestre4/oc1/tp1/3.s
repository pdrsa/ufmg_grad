main:
    addi x10, x0, 0 	# Potencia
    addi x11, x0, 10 	# Torque
    addi x12, x0, 225 	# Rotação
    addi x13, x0, 3		# Pi
    addi x14, x0, 2000 	# Preparando 2250
    addi x14, x14, 250	# 2250
    beq x10, x0, ifpot	# Se potencia é 0
	jal x0, elsepot		# Senão
ifpot:
	mul x10, x13, x11	# Potencia = Pi * Torque
    mul x10, x10, x12	# Potencia = Potencia * Rotação
    div x10, x10, x14	# Potencia = Potencia/2250
    jal x0, exit		# Termina o programa
elsepot:
	beq x11, x0, iftor	# Se torque é 0
	jal x0, elsetor		# Senão
iftor:
	mul x11, x10, x14 	# Torque = Potencia * 2250
    div x11, x11, x12	# Torque = Torque/Rotação
    div x11, x11, x13	# Torque = Torque/Pi
    jal x0, exit		# Termina o programa
elsetor:
	beq x12, x0, ifrot	# Se rotação é 0
    jal x0, exit		# Se nenhum dos 3 é 0 eu finalizo o programa
ifrot:
	mul x12, x10, x14 	# Rotação = Potencia * 2250
    div x12, x12, x11	# Rotação = Rotação/Torque
    div x12, x12, x13	# Rotação = Rotação/Pi
    jal x0, exit		# Termina o programa
exit:
