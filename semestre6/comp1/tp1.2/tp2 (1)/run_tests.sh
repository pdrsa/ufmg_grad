yacc -d tiger.y -Wnone
lex yylex.lex
gcc -w lex.yy.c y.tab.c -o analyzer
for file in testes/*
do 
    echo "Teste $file:"
    echo ""
    echo "Input: "
    cat $file
    echo ""
    echo "Output:"
    ./analyzer < "$file"
    echo "-------------------------------------------------------"
done