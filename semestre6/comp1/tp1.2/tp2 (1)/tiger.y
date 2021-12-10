%{
#include <stdio.h>
extern int yylineno;
int error = 0;
%}

/* Yacc Definitions */
%token ASSIGN
%token COLON
%token COMMA
%token IF
%token ELSE
%token ARRAY
%token WHILE
%token FOR
%token VAR
%token FUNCTION
%token LET
%token BREAK
%token TO
%token DO
%token IN
%token OF
%token NIL
%token TYPE
%token IMPORT
%token PRIMITIVE
%token MULT_OP
%token BOOL_OP
%token OPEN_RB
%token CLOSE_RB
%token OPEN_CB
%token CLOSE_CB
%token OPEN_BB
%token CLOSE_BB
%token ID
%token INTEGER
%token STRING
%token TYPE_ID
%token THEN
%token END
%token EQ_OP
%token LT_OP
%token LE_OP
%token GT_OP
%token GTE_OP
%token NEQ_OP
%token ADD_OP
%token SUB_OP
%token MUL_OP
%token DIV_OP	
%token AND_OP
%token OR_OP
%token DOT
%token SEMICOLON
%start exp
%left AND_OP OR_OP
%nonassoc EQ_OP NEQ_OP LT_OP LE_OP GT_OP GTE_OP
%left ADD_OP SUB_OP
%left MUL_OP DIV_OP

%%
/* descriptions of expected inputs     corresponding actions (in C) */

exp : 
     l_value {printf("exp ::= l_value\n");}
    | NIL {printf("exp ::= nil\n");}
    | OPEN_RB expseq CLOSE_RB {printf("exp ::= ( expseq )\n");}
    | INTEGER {printf("exp ::= num \n");}
    | STRING {printf("exp ::= string \n");}
    | SUB_OP exp {printf("exp ::= -exp \n");}
    | ID OPEN_RB args CLOSE_RB {printf("exp ::= id ( args )\n");}
    | exp ADD_OP exp {printf("exp ::= exp + exp \n");}
    | exp SUB_OP exp {printf("exp ::= exp - exp \n");}
    | exp MUL_OP exp {printf("exp ::= exp * exp \n");}
    | exp DIV_OP exp {printf("exp ::= exp / exp \n");}
    | exp EQ_OP exp {printf("exp ::= exp = exp \n");}
    | exp NEQ_OP exp {printf("exp ::= exp <> exp \n");}
    | exp LT_OP exp {printf("exp ::= exp < exp \n");}
    | exp GT_OP exp {printf("exp ::= exp > exp \n");}
    | exp LE_OP exp {printf("exp ::= exp <= exp \n");}
    | exp GTE_OP exp {printf("exp ::= exp >= exp \n");}
    | exp AND_OP exp {printf("exp ::= exp & exp \n");}
    | exp OR_OP exp {printf("exp ::= exp | exp \n");}
    | type_id OPEN_CB ID EQ_OP exp idexps CLOSE_CB {printf("exp ::= type_id {id = exp idexps} \n");}
    | type_id OPEN_BB exp CLOSE_BB OF exp {printf("exp ::= type_id [exp] of exp \n");}
    | l_value ASSIGN exp {printf("exp ::= l_value := exp \n");}
    | IF exp THEN exp ELSE exp {printf("exp ::= if exp then exp else exp \n");}
    | IF exp THEN exp {printf("exp ::= if exp then exp \n");}
    | WHILE exp DO exp {printf("exp ::= while exp do exp \n");}
    | FOR ID ASSIGN exp TO exp DO exp {printf("exp ::= for id := exp to exp do exp \n");}
    | BREAK {printf("exp ::= break \n");}
    | LET decs IN expseq END {printf("exp ::= let decs in expseq end \n");}
    ;

decs :
    dec decs {printf("decs ::= dec decs \n");}
    | %empty 
    ;

dec :
    tydec {printf("dec ::= tydec \n");}
    | vardec {printf("dec ::= vardec \n");}
    | fundec {printf("dec ::= fundec \n");}
    ;

tydec :
    TYPE ID EQ_OP ty {printf("tydec ::= type id = ty \n");}
    ;

ty :
    ID {printf("ty ::= id \n");}
    | OPEN_CB ID COLON type_id tyfields1 CLOSE_CB {printf("ty ::= {id : type_id tyfields1} \n");}
    | ARRAY OF ID {printf("ty ::= array of id \n");}
    | ARRAY OF type_id {printf("ty ::= array of id \n");}
    ;

tyfields :
    ID COLON type_id tyfields1 {printf("tyfields ::= id : type_id tyfields1 \n");}
    | %empty
    ;

tyfields1 :
    COMMA ID COLON type_id tyfields1 {printf("tyfields1 ::= , id : type_id tyfields1 \n");}
    | %empty 
    ;

vardec :
    VAR ID ASSIGN exp {printf("vardec ::= var id := exp \n");}
    | VAR ID COLON type_id ASSIGN exp {printf("vardec ::= var id : type_id := exp \n");}
    ;

fundec :
    FUNCTION ID OPEN_RB tyfields CLOSE_RB EQ_OP exp {printf("fundec ::= function id ( tyfields ) = exp \n");}
    | FUNCTION ID OPEN_RB tyfields CLOSE_RB COLON type_id EQ_OP exp {printf("fundec ::= function id ( tyfields ) : type_id  = exp \n");}
    ;

l_value :
    type_id {printf("l_value ::= type_id \n");}
    | l_value DOT ID {printf("l_value ::= l_value.id \n");}
    | type_id OPEN_BB exp CLOSE_BB {printf("l_value ::= l_value [exp] \n");}
    | l_value OPEN_BB exp CLOSE_BB {printf("l_value ::= l_value [exp] \n");}
    ;

type_id :
    ID {printf("type_id ::= id \n");}
    | TYPE_ID {printf("type_id ::= type_id \n");}
    ;

expseq :
    exp expseq1 {printf("expseq ::= exp expseq1 \n");}
    | %empty;

expseq1 :
    SEMICOLON exp expseq1 {printf("expseq1 ::= ; exp expseq1 \n");}
    | %empty 
    ;

args :
    exp args1   {printf("args ::= exp args1 \n");}
    | %empty
    ;

args1 : 
    COMMA exp args1 {printf("args1 ::= , exp args1 \n");}
    | %empty 
    ;

idexps :
    COMMA ID EQ_OP exp idexps {printf("idexps ::= , id = exp idexps \n");}
    | %empty 
    ;



%%


int main( int argc, char **argv ){
    yyparse ();
    if(!error)
        printf("\nsintaxe correta\n");
    return 1;

}   



void yyerror (char *s) { 
    //fprintf(stderr,"Error | Line: %d\n%s\n",yylineno,s);
    printf("\nerro de sintaxe\n");
    error = 1;
    }