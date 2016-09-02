%{
/*
    module  : parse.y
    version : 1.2
    date    : 09/02/16
*/
#include <stdio.h>
#include "memory.h"
#include "node.h"
%}

%token PUBLIC EQUAL
%token AND BODY CONS DIP DUP GET I INDEX NOT NOTHING OR POP PUT SAMETYPE SELECT
%token STACK STEP SWAP UNCONS UNSTACK SMALL PRED BINREC

%token Symbol Boolean Char Int List Defined Function

%union {
    int num;
    char *str;
    struct node_t *ptr;
}

%type <num> Symbol Boolean Char Int
%type <str> Defined
%type <ptr> factor quot opt_quot list term opt_term

%%

script	: { stkptr = 0; } cycle
	;

cycle	: cycle def_or_term '.'
	| /* empty */
	;

def_or_term
	: compound_def
	| opt_term	{ if (compiling) compile($1); else execute($1); }
	;

compound_def
	: public	{ definition = 0; }
	| /* empty */	{ if (compiling) compile(0); else writestack(); }
	;

public	: PUBLIC { definition = 1; } seq_definition
	;

seq_definition
	: seq_definition ';' opt_definition
	| opt_definition
	;

opt_definition
	: Defined EQUAL opt_quot	{ enterdef($1, $3); }
	| /* empty */
	;

opt_term
	: term		{ if (!compiling) $$ = reverse($1); }
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

list	: '[' opt_quot ']'	{ $$ = $2; }
	;

opt_quot
	: quot		{ if (!compiling) $$ = reverse($1); }
	| /* empty */	{ $$ = 0; }
	;

quot	: quot factor	{ $2->next = $1; $$ = $2; }
	| factor
	;
