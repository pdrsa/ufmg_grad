make tsp
for i in testes/*
    do 
    echo $i
    ./tsp < $i; 
    done

