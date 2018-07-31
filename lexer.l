%{
/*
    module  : lexer.l
    version : 1.5
    date    : 07/31/18
*/
#include <string.h>
#include <stdlib.h>
#include "joygc.h"
#include "parse.h"

#define YY_NO_UNPUT
#define YY_NO_INPUT
%}

alpha		[A-Z_a-z]
alphanum	[A-Z_a-z0-9]
symbol		{alpha}{alphanum}*

%%

DEFINE		{ return PUBLIC; }
==		{ return EQUAL; }
LET		{ return LET; }
IN		{ return IN; }
END		{ return END; }

'\\[0-9]+	{ yylval.num = atoi(yytext+2); return Char; }
'.		{ yylval.num = yytext[1]; return Char; }
[-]?[0-9]+	{ yylval.num = atoi(yytext); return Int; }
[*+/<=-]	|
[<=>]+		|
{symbol}	{ yylval.str = strdup(yytext); return Symbol; }
[ \t\n]+	|
#.*		;
[.;[\]]		|
.		{ return yytext[0]; }

%%

int yyerror(char *str)
{
    fprintf(stderr, "%s\n", str);
    return 1;
}

int yywrap()
{
    return 1;
}
