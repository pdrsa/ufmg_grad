%{
#include <stdio.h>
#include "y.tab.h"
%}
%% 

":="								return ASSIGN;
":" 								return COLON;
","									return COMMA;
"."									return DOT;
";"									return SEMICOLON;

"int"|"string"						return TYPE_ID;
"if"     							return IF;
"else" 								return ELSE;
"array" 							return ARRAY;
"while" 							return WHILE;
"for"								return FOR;
"var" 								return VAR;
"function"							return FUNCTION;
"let" 								return LET;
"break"								return BREAK;
"to"								return TO;
"do"								return DO;
"in"								return IN;
"of"								return OF;
"nil"								return NIL;
"type"								return TYPE;
"import"							return IMPORT;
"primitive"							return PRIMITIVE;
"then"								return THEN;
"end"								return END;

"="									return EQ_OP;
"<"									return LT_OP;
"<="								return LE_OP;
">"									return GT_OP;
">="								return GTE_OP;
"<>"								return NEQ_OP;
"+"									return ADD_OP;
"-"									return SUB_OP;
"*"									return MUL_OP;
"/"									return DIV_OP;		

"&"									return AND_OP;
"|"									return OR_OP;

[(]									return OPEN_RB;
[)]									return CLOSE_RB;
[{]									return OPEN_CB;
[}]									return CLOSE_CB;
[[]									return OPEN_BB;
[]]									return CLOSE_BB;


[a-zA-Z][a-zA-Z0-9_]*|"_main"		return ID;

([1-9][0-9]*)|"0" 					return INTEGER;

[\"].*[\"]							return STRING;

"/*".*"*/"							;
[ \n\r\t]							;

%% 

int yywrap(void)
{
	return 1;
}
