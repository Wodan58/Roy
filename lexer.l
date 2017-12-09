%{
/*
    module  : lexer.l
    version : 1.2
    date    : 05/13/17
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

and		{ yylval.num = AND; return Symbol; }
body		{ yylval.num = BODY; return Symbol; }
cons		{ yylval.num = CONS; return Symbol; }
dip		{ yylval.num = DIP; return Symbol; }
dup		{ yylval.num = DUP; return Symbol; }
false		{ yylval.num = 0; return Boolean; }
get		{ yylval.num = GET; return Symbol; }
i		{ yylval.num = I; return Symbol; }
index		{ yylval.num = INDEX; return Symbol; }
not		{ yylval.num = NOT; return Symbol; }
nothing		{ yylval.num = NOTHING; return Symbol; }
or		{ yylval.num = OR; return Symbol; }
pop		{ yylval.num = POP; return Symbol; }
put		{ yylval.num = PUT; return Symbol; }
sametype	{ yylval.num = SAMETYPE; return Symbol; }
select		{ yylval.num = SELECT; return Symbol; }
stack		{ yylval.num = STACK; return Symbol; }
step		{ yylval.num = STEP; return Symbol; }
swap		{ yylval.num = SWAP; return Symbol; }
true		{ yylval.num = 1; return Boolean; }
uncons		{ yylval.num = UNCONS; return Symbol; }
unstack		{ yylval.num = UNSTACK; return Symbol; }

binrec		{ yylval.num = BINREC; return Symbol; }
pred		{ yylval.num = PRED; return Symbol; }
small		{ yylval.num = SMALL; return Symbol; }

'\\[0-9]+	{ yylval.num = atoi(yytext+2); return Char; }
'.		{ yylval.num = yytext[1]; return Char; }
[-]?[0-9]+	{ yylval.num = atoi(yytext); return Int; }
[*+/<=-]	{ yylval.num = yytext[0]; return Symbol; }
[<=>]+		|
{symbol}	{ yylval.str = strdup(yytext); return Defined; }
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
