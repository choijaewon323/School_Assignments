%option noyywrap
%{
#include "y.tab.h"

%}
digit [0-9]
number {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%

[ ]	{ }
{number}	{ sscanf(yytext, "%lf", &yylval);
		  return NUMBER;
		}
\n|.		{ return yytext[0]; }
