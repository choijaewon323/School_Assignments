%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER 256
#define OPER 257
#define ERROR 258
%}

ws	[ \t\n]+
op	[+-]
errorNum	0[0-9]+
number	0|[1-9][0-9]*
other	[a-zA-Z*/]+

%%

{ws}		{ }
{errorNum}	{ return ERROR; }
{other}		{ return ERROR; }
{number}	{ return NUMBER; }
{op}		{ return OPER; }

%%

int main()
{
	int isErrored = 0;
	int token, i;
	int numberIndex = 0, operIndex = 0;
	int numbers[100];
	int format[100];
	char opers[100];
	char *cop;
	
	for (i = 0; i < 100; i++)
	{
		format[i] = 0;
		numbers[i] = 0;
		opers[i] = 0;
	}
	
	i = 0;
	while ((token = yylex())) 
	{	
		switch (token)
		{
		case NUMBER:
			if (i != 0)
			{
				if (format[i - 1] == 1)
				{
					isErrored = 1;
					break;
				}
			}
						
			cop = strdup(yytext);
			numbers[numberIndex++] = atoi(cop);
			format[i++] = 1;
			break;
		case OPER:
			if (i > 1)
			{
				if (format[i - 1] == 2)
				{
					isErrored = 1;
					break;
				}
			}
			cop = strdup(yytext);
			opers[operIndex++] = *cop;
			format[i++] = 2;
			break;
		default:
			isErrored = 1;
		}
	}

	if (isErrored)
	{
		printf("error\n");
		return 0;
	}

	if (numberIndex - 1 != operIndex)
	{
		printf("error\n");
		return 0;
	}
	
	i = 0;
	printf("%d ", numbers[i]);
	
	for (i = 1; i < numberIndex; i++)
	{
		printf("%d %c ", numbers[i], opers[i - 1]);
	}
	printf("\n");
	
	return 0;
}
