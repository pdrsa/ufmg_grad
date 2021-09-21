for ((i = 1; ; i++)) do
	./gen $i > in
	time ./acorde < in > out
	echo "Teste $i"
done

