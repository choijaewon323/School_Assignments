%{
#include <ctype.h>
#include <stdio.h>
#define YYSTYPE double

extern FILE *yyin, *yyout;
%}
%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS
%%
lines	: lines expr ';''\n'	{ fprintf(yyout, "%g\n", $2); }
      	| lines '\n'
      	| /* empty */
      	;

expr	: expr '+' expr		{ $$ = $1 + $3; }
     	| expr '-' expr		{ $$ = $1 - $3; }
	| expr '*' expr		{ $$ = $1 * $3; }
	| expr '/' expr		{ $$ = $1 / $3; }
	| '(' expr ')'		{ $$ = $2; }
	| '-' expr %prec UMINUS	{ $$ = -$2; }
	| NUMBER
	;
%%
int main()
{
	FILE *in, *out;
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "a");
	yyin = in;
	yyout = out;	

	if (yyparse() != 0)
		fprintf(stderr, "abnormal exit\n");
	return 0;
}

int yyerror(char *s)
{
	fprintf(yyout, "error\n");
}
