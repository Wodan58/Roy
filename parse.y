%{
/*
    module  : parse.y
    version : 1.5
    date    : 07/31/18
*/
#include <stdio.h>
#include "node.h"

static int inlet;
%}

%token PUBLIC
%token EQUAL
%token LET
%token IN
%token END

%token Unknown
%token Builtin
%token Defined
%token Function
%token Expression
%token Parameter

%token <num> Boolean Char Int
%token <str> Symbol
%token <ptr> List

%type <ptr> opt_term term factor list

%union {
    int num;
    char *str;
    struct node_t *ptr;
}

%%

cycle	: cycle def_or_term '.'
	| /* empty */	{ vec_init(theStack); }
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
	: Symbol EQUAL opt_term	{ enterdef($1, $3); }
	| /* empty */
	;

opt_term
	: term		{ $$ = reverse($1); }
	| /* empty */	{ $$ = 0; }
	;

term	: term factor	{ $2->next = $1; $$ = $2; }
	| factor
	;

factor	: Symbol	{ if (inlet) $$ = newparameter($1); else
			  $$ = newnode(Unknown, enterdef($1, 0)); }
	| Boolean	{ $$ = newnode(Boolean, $1); }
	| Char		{ $$ = newnode(Char, $1); }
	| Int		{ $$ = newnode(Int, $1); }
	| list		{ $$ = newlist($1); }
	| LET { inlet = 1; } term IN opt_term { inlet = 0; } END
			{ $$ = newexpression($3, $5); }
	;

list	: '[' opt_term ']'	{ $$ = $2; }
	;
