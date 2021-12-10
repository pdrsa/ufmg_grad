yacc -d tiger.y -Wnone
lex yylex.lex
gcc -w lex.yy.c y.tab.c -o analyzer

echo "Teste $1:"
echo "Input: "
cat $1
echo ""
echo "Output:"
./analyzer < $1