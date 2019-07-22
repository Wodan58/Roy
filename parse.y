%{
/*
    module  : parse.y
    version : 1.7
    date    : 07/08/19
*/
#include <stdio.h>
#include "stack.h"
#include "builtin.h"

void initsym(void);		/* symbol.c */
void enterdef(char *name, Stack *List);

int yylex(void);		/* yylex.c */
void yyerror(char *str);

void execute(Stack *List);	/* builtin.c */
void reverse(Stack *List);
%}

%token PUBLIC
%token EQUAL

%token <num> Boolean Char Int
%token <str> Symbol
%token <ptr> List

%type <num> factor
%type <ptr> opt_term term list

%union {
    char *str;
    Stack *ptr;
    intptr_t num;
}

%%

cycle	: cycle def_or_term '.'
	| /* empty */	{ initsym(); }
	;

def_or_term
	: compound_def
	| opt_term	{ execute($1); do_stop(); }
	;

compound_def
	: PUBLIC seq_definition
	;

seq_definition
	: seq_definition ';' opt_definition
	| opt_definition
	;

opt_definition
	: Symbol EQUAL opt_term	{ enterdef($1, $3); }
	| /* empty */
	;

opt_term
	: term		{ reverse($1); }
	| /* empty */	{ $$ = 0; }
	;

term	: term factor	{ vec_add($1, $2); }
	| factor	{ Stack *List; vec_init(List); vec_add(List, $1); $$ = List; }
	;

factor	: Symbol	{ $$ = (intptr_t)$1; }
	| Boolean
	| Char
	| Int
	| list		{ $$ = (intptr_t)$1; }
	;

list	: '[' opt_term ']'	{ $$ = $2; }
	;
