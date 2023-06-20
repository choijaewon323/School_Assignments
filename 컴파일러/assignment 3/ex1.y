%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern FILE *yyin, *yyout;

char symtab[100][30];
int symIndex = 0;
int tempIndex = 0;

int isSymbolExist(char *id) {
	for (int i = 0; i < 100; i++) {
		int temp;
		temp = strcmp(symtab[i], id);
		if (temp == 0)
			return i;
	}
	return -1;
}

void makeCode(char *oper1, char *oper2, char oper, char *result) {
	sprintf(result, "t%d", tempIndex);
	tempIndex++;
	fprintf(yyout, "%s = %s %c %s\n", result, oper1, oper, oper2);
}
%}

%union {
	char string[30];
}

%left '+' '-'
%left '*' '/'
%right UMINUS

%token <string> ID NUMBER
%token INTEGER
%token FLOAT
%type <string> expr

%%

prog	: 
     	| prog stmt '\n'
	| prog '\n'
	;

stmt 	: ID '=' expr ';' { int temp = isSymbolExist($1);
				if (temp != -1) {
					fprintf(yyout, "%s = %s\n", $1, $3);
				}
				else {
					yyerror("no declaration");
					return 0;
				}
			}
     	| decl ';'
	;

decl	: type ID { int temp = isSymbolExist($2);
     			if (temp != -1) {
				yyerror("multiple declaration");
				return 0;
			}
			else {
				strcpy(symtab[symIndex], $2);
				symIndex++;
			}
		}			
    	;

type 	: INTEGER
      	| FLOAT
	;

expr	: NUMBER
     	| ID		{ int temp = isSymbolExist($1);
				if (temp != -1)
					strcpy($$, symtab[temp]);
				else {
					yyerror("no declaration");
					return 0;
				}
			}
	| expr '+' expr { char result[30]; makeCode($1, $3, '+', result);
				strcpy($$, result); }
	| expr '-' expr { char result[30]; makeCode($1, $3, '-', result);
				strcpy($$, result); }
	| expr '*' expr { char result[30]; makeCode($1, $3, '*', result);
				strcpy($$, result); }
	| expr '/' expr	{ char result[30]; makeCode($1, $3, '/', result);
				strcpy($$, result); }
	| '-' expr %prec UMINUS { char result[30];
				sprintf(result, "t%d", tempIndex++);
				fprintf(yyout, "%s = -%s\n", result, $2);
				strcpy($$, result); }
	;

%%

void yyerror(char *s) {
	fprintf(yyout, "%s\n", s);
}

int yywrap() {
	return 1;
}

int main() {
	FILE *in, *out;
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "a");
	yyin = in;
	yyout = out;
	
	yyparse();
	return 0;
}
