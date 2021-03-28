make
for i in 01 02 03 04 05 06 07 08 09 10
	do
		echo Solução João/Oficial Caso $i
		./tp03 < CasosTeste/input$i.txt
		cat CasosTeste/out$i.txt
	done
