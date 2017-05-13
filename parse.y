%{
/*
    module  : parse.y
    version : 1.2
    date    : 05/13/17
*/
#include <stdio.h>
#include "gc.h"
#include "node.h"

#define PARSER
#define YYSTACK_ALLOC	malloc
%}

%token PUBLIC	1
%token EQUAL	2
%token AND	3
%token BODY	4
%token CONS	5
%token DIP	6
%token DUP	7
%token GET	8
%token I	9
%token INDEX	10
%token NOT	11
%token NOTHING	12
%token OR	13
%token POP	14
%token PUT	15
%token SAMETYPE	16
%token SELECT	17
%token STACK	18
%token STEP	19
%token SWAP	20
%token UNCONS	21
%token UNSTACK	22
%token Symbol	23
%token Boolean	24
%token Char	25
%token Int	26
%token List	27
%token Defined	28
%token Function	29
%token BINREC	30
%token PRED	31
%token SMALL	32

%union {
    int num;
    char *str;
    struct node_t *ptr;
}

%type <num> Symbol Boolean Char Int
%type <str> Defined
%type <ptr> opt_term term factor list

%%

cycle	: cycle def_or_term '.'
	| /* empty */	{ vec_init(theStack); vec_init(theTable); }
	;

def_or_term
	: compound_def
	| opt_term	{ if (compiling) compile($1); else execute($1); }
	;

compound_def
	: PUBLIC { definition = 1; } seq_definition { definition = 0; }
	;

seq_definition
	: seq_definition ';' opt_definition
	| opt_definition
	;

opt_definition
	: Defined EQUAL opt_term	{ enterdef($1, $3); }
	| /* empty */
	;

opt_term
	: term		{ $$ = reverse($1); }
	| /* empty */	{ $$ = 0; }
	;

term	: term factor	{ $2->next = $1; $$ = $2; }
	| factor
	;

factor	: Symbol	{ $$ = newnode(Symbol, $1); }
	| Defined	{ $$ = entersym($1); }
	| Boolean	{ $$ = newnode(Boolean, $1); }
	| Char		{ $$ = newnode(Char, $1); }
	| Int		{ $$ = newnode(Int, $1); }
	| list		{ $$ = newlist($1); }
	;

list	: '[' opt_term ']'	{ $$ = $2; }
	;
