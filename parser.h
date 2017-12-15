/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 84 "parser.bison" /* yacc.c:1909  */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "code.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Expr* expr;
Cmd* cmd;
CmdList* cmdList;
BExpr* bexpr;

#line 61 "parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MAIN = 258,
    FUNC = 259,
    SSCAN = 260,
    SPRINT = 261,
    DECLARATION = 262,
    INC = 263,
    DEC = 264,
    VAR = 265,
    BOOL = 266,
    INT = 267,
    AND = 268,
    OR = 269,
    IF = 270,
    ELSE = 271,
    FOR = 272,
    ENDLINE = 273,
    COMMA = 274,
    LBRACE = 275,
    RBRACE = 276,
    LPAREN = 277,
    RPAREN = 278,
    ATTRIB = 279,
    EQUAL = 280,
    DIFFERENT = 281,
    GT = 282,
    GTE = 283,
    LT = 284,
    LTE = 285,
    PLUS = 286,
    MINUS = 287,
    DIVISION = 288,
    TIMES = 289,
    MOD = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 60 "parser.bison" /* yacc.c:1909  */

  int intValue;
  int boolValue;
  Expr* exprValue;
  BExpr* bexprValue;
  Cmd* cmdValue;
  CmdList* cmdListValue;
  char* varValue;
  int varIntValue;

#line 120 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
