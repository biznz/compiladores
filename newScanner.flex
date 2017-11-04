/** structure of an input file to flex (scanner generator)
	check ftp://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_mono/flex.html

definitions
%%
rules
%%
user code

**/

%{
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int yyline=1;
//int yytabs=1;
%}

%option noyywrap

	/* definitions */

VAR [a-zA-Z][a-zA-Z0-9]*
RESERVED if|else|for|var
BRACES \{|\}
DIGIT [0-9]
BOOLEAN true|false
OP \+|\-|\*|\/|\%|\=
LOP \&\&|\|\|
ROP \<|\>|\<\=|\>\=|\!\=|\=\=
L_COMMENT #.*
NW \n
W_SPACE [ \t]
ENDLINE ;
%%

	/* rules */

{DIGIT}+	{
			yylval.intValue = atoi(yytext);
			return INT;
			}

{BOOLEAN}	{
			if(strcmp(yytext,"true")==0){
				yylval.boolValue = 1;
			}
			else{
				yylval.boolValue = 0;
			}
			return BOOL;
			}		

{VAR}		{
			yylval.varValue = strdup(yytext);
			return VAR;
			}

{BRACES}	{
			char c = yytext[0];
			if(c=='{'){
				return LBRACE;
				}
			else{
				return RBRACE;
				}
			}

{RESERVED}	{
			yylval.key = strdup(yytext);
			if(strcmp(yytext,"if")==0){
				return IF;
				}
			if(strcmp(yytext,"else")==0){
				return ELSE;
				}
			if(strcmp(yytext,"for")==0){
				return FOR;
				}
			if(strcmp(yytext,"var")==0){
				return DECLARATION;
				}
			}		

{OP} 		{
			char c = yytext[0];
			if(c=='-'){
				return MINUS;
			}
			if(c=='+'){
				return PLUS;
				}
			if(c=='*'){
				return TIMES;
			}
			if(c=='/'){
				return DIVISION;
			}
			if(c=='='){
				return ATTRIB;
			}

			else{
				return MOD;
				}	
			}

{ROP}		{
			if(strcmp(yytext,"!=")==0){
				return DIFFERENT;
				}
			if(strcmp(yytext,"==")==0){
				return EQUAL;
				}
			if(strcmp(yytext,"<")==0){
				printf("LT\n");
				return LT;
				}
			if(strcmp(yytext,">")==0){
				return GT;
				}
			if(strcmp(yytext,"<=")==0){
				return LTE;
				}
			if(strcmp(yytext,">=")==0){
				return GTE;
				}
			}

{LOP}		{
			if(strcmp(yytext,"||")==0){
				return OR;
				}
			if(strcmp(yytext,"&&")==0){
				return AND;
				}
			}

{L_COMMENT}	{
	
			}

{W_SPACE}	{
			//yyline++;
			}

{NW}		{
			yyline++;
			}

{ENDLINE}	{
			return ENDLINE;
			}

%%

	/* actions */
