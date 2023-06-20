%{
#include "y.tab.h"
#include <string.h>

%}

digit [0-9]
number {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?
letter [A-Za-z]
id {letter}({letter}|{digit})*

%%

{number} { strcpy(yylval.string, yytext); return NUMBER;}
int { return INTEGER; }
float { return FLOAT; }
{id} { strcpy(yylval.string, yytext); return ID;}
[ ] {}
\n|. { return yytext[0]; }

%%
