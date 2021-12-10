/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ASSIGN = 258,
    COLON = 259,
    COMMA = 260,
    IF = 261,
    ELSE = 262,
    ARRAY = 263,
    WHILE = 264,
    FOR = 265,
    VAR = 266,
    FUNCTION = 267,
    LET = 268,
    BREAK = 269,
    TO = 270,
    DO = 271,
    IN = 272,
    OF = 273,
    NIL = 274,
    TYPE = 275,
    IMPORT = 276,
    PRIMITIVE = 277,
    MULT_OP = 278,
    BOOL_OP = 279,
    OPEN_RB = 280,
    CLOSE_RB = 281,
    OPEN_CB = 282,
    CLOSE_CB = 283,
    OPEN_BB = 284,
    CLOSE_BB = 285,
    ID = 286,
    INTEGER = 287,
    STRING = 288,
    TYPE_ID = 289,
    THEN = 290,
    END = 291,
    EQ_OP = 292,
    LT_OP = 293,
    LE_OP = 294,
    GT_OP = 295,
    GTE_OP = 296,
    NEQ_OP = 297,
    ADD_OP = 298,
    SUB_OP = 299,
    MUL_OP = 300,
    DIV_OP = 301,
    AND_OP = 302,
    OR_OP = 303,
    DOT = 304,
    SEMICOLON = 305
  };
#endif
/* Tokens.  */
#define ASSIGN 258
#define COLON 259
#define COMMA 260
#define IF 261
#define ELSE 262
#define ARRAY 263
#define WHILE 264
#define FOR 265
#define VAR 266
#define FUNCTION 267
#define LET 268
#define BREAK 269
#define TO 270
#define DO 271
#define IN 272
#define OF 273
#define NIL 274
#define TYPE 275
#define IMPORT 276
#define PRIMITIVE 277
#define MULT_OP 278
#define BOOL_OP 279
#define OPEN_RB 280
#define CLOSE_RB 281
#define OPEN_CB 282
#define CLOSE_CB 283
#define OPEN_BB 284
#define CLOSE_BB 285
#define ID 286
#define INTEGER 287
#define STRING 288
#define TYPE_ID 289
#define THEN 290
#define END 291
#define EQ_OP 292
#define LT_OP 293
#define LE_OP 294
#define GT_OP 295
#define GTE_OP 296
#define NEQ_OP 297
#define ADD_OP 298
#define SUB_OP 299
#define MUL_OP 300
#define DIV_OP 301
#define AND_OP 302
#define OR_OP 303
#define DOT 304
#define SEMICOLON 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
