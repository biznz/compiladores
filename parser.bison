/**

  A Bison grammar file has four main sections, shown here with the appropriate delimiters:
  https://www.gnu.org/software/bison/manual/bison.html

  ftp://ftp.auckland.ac.nz/pub/gnu/Manuals/bison-1.35/html_chapter/bison_6.html 3.5.4

%{
  Prologue
%}

Bison declarations

%%
Grammar rules
%%

Epilogue

**/


// Tokens
%token
  DECLARATION
  VAR
  BOOL
  INT
  ATTRIB
  AND
  OR
  IF
  ELSE
  FOR
  ENDLINE
  LBRACE
  RBRACE
/**while if print**/

// Operator associativity & precedence
%left EQUAL DIFFERENT GT GTE LT LTE
%left PLUS MINUS
%left DIVISION TIMES MOD
// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  int boolValue;
  Expr* exprValue;
  BExpr* bexprValue;
  Cmd* cmdValue;
  char* varValue;
  int varIntValue;
}

%type <intValue> INT
%type <boolValue> BOOL
%type <exprValue> expr
%type <cmdValue> cmd
%type <bexprValue> bexpr
%type <varValue> VAR

//trying to provide a more verbose and specific error message
%define parse.error verbose

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Expr* root;
Cmd* cmd;
BExpr* broot;
}

%%
program : source

source  : line 
        | line source
        ;

line    : cmd {cmd = $1;}

cmd     : VAR ATTRIB expr ENDLINE
          { $$ = ast_attrib($1, $3);}
        | IF bexpr LBRACE cmd RBRACE 
          { $$ = ast_if($2,$4);}
        | FOR bexpr LBRACE cmd RBRACE 
          { $$ = ast_for($2,$4);}
        ;

expr    :
        INT { 
          $$ = ast_integer($1);
        }
        |
        VAR{
          $$ = ast_var($1);
        }
        |
        expr PLUS expr{ 
          $$ = ast_operation(PLUS, $1, $3); 
        }
        |
        expr MINUS expr{ 
          $$ = ast_operation(MINUS, $1, $3); 
        }
        |
        expr TIMES expr{ 
          $$ = ast_operation(TIMES, $1, $3); 
        }
        |
        expr DIVISION expr{ 
          $$ = ast_operation(DIVISION, $1, $3); 
        }
        |
        expr MOD expr{ 
          $$ = ast_operation(MOD, $1, $3); 
        }
        |
        expr OR expr{
          $$ = ast_operation(OR, $1, $3);
        }
        |
        expr AND expr{
          $$ = ast_operation(AND, $1, $3);
        }
        ;

bexpr   :
        BOOL{
          $$ = ast_boolean($1);
        }
        | 
        expr LT expr{
            $$ = ast_roperation(LT, $1, $3); 
        }
        | 
        expr LTE expr{
            $$ = ast_roperation(LTE, $1, $3);
        }
        | 
        expr GT expr{
            $$ = ast_roperation(GT, $1, $3);
        }
        | 
        expr GTE expr{
            $$ = ast_roperation(GTE, $1, $3);
        }
        | 
        bexpr EQUAL bexpr{
            $$ = ast_rBoperation(EQUAL, $1, $3);
        }
        | 
        bexpr DIFFERENT bexpr{
            $$ = ast_rBoperation(DIFFERENT, $1, $3);
        }
        ;


%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
