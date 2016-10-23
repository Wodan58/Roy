%{
/*
    module  : lexer.l
    version : 1.1
    date    : 10/23/16
*/
#include <string.h>
#include <stdlib.h>
#include "memory.h"
#include "parse.h"

#define YY_NO_UNPUT
#define YY_NO_INPUT

#ifdef free
#undef free
#define free(X)		(!X?X++:0)
#endif
%}

alpha		[A-Z_a-z]
alphanum	[A-Z_a-z0-9]
symbol		{alpha}{alphanum}*

%%

DEFINE		{ return PUBLIC; }
and		{ yylval.num = AND; return Symbol; }
binrec		{
#ifdef BENCHMARK
		  yylval.num = BINREC; return Symbol;
#else
		  yylval.str = strdup(yytext); return Defined;
#endif
		}
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
pred		{
#ifdef BENCHMARK
		  yylval.num = PRED; return Symbol;
#else
		  yylval.str = strdup(yytext); return Defined;
#endif
		}
put		{ yylval.num = PUT; return Symbol; }
sametype	{ yylval.num = SAMETYPE; return Symbol; }
select		{ yylval.num = SELECT; return Symbol; }
small		{
#ifdef BENCHMARK
		  yylval.num = SMALL; return Symbol;
#else
		  yylval.str = strdup(yytext); return Defined;
#endif
		}
stack		{ yylval.num = STACK; return Symbol; }
step		{ yylval.num = STEP; return Symbol; }
swap		{ yylval.num = SWAP; return Symbol; }
true		{ yylval.num = 1; return Boolean; }
uncons		{ yylval.num = UNCONS; return Symbol; }
unstack		{ yylval.num = UNSTACK; return Symbol; }

'\\[0-9]+	{ yylval.num = atoi(yytext+2); return Char; }
'.		{ yylval.num = yytext[1]; return Char; }
[0-9]+		{ yylval.num = atoi(yytext); return Int; }
[ \t\n]+	;
==		{ return EQUAL; }
[*+/<=-]	{ yylval.num = yytext[0]; return Symbol; }
[<=>]+		|
{symbol}	{ yylval.str = strdup(yytext); return Defined; }
#.*		;
[.[\]]		|
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
