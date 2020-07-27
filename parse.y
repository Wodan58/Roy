%{
/*
    module  : parse.y
    version : 1.16
    date    : 06/21/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "stack.h"
#include "module.h"
#include "khash.h"
#include "symbol.h"
#include "yylex.h"
#include "builtin.h"

void execute(Stack *List);	/* builtin.c */
intptr_t pack(real_t dbl);
%}

%token MODULE JPRIVATE JPUBLIC JEQUAL END

%token <num> UNKNOWN_		1
%token <str> USR_		2
%token <fun> ANON_FUNCT_	3
%token <num> BOOLEAN_		4
%token <num> CHAR_		5
%token <num> INTEGER_		6
%token <num> SET_		7
%token <str> STRING_		8
%token <ptr> LIST_		9
%token <dbl> FLOAT_		10
%token <fil> FILE_		11

%type <num> char_or_int
%type <num> opt_set set factor
%type <ptr> opt_term term list

%union {
    char *str;
    FILE *fil;
    Stack *ptr;
    real_t dbl;
    intptr_t num;
    void (*fun)(void);
};

%%

/*
    Cycle is the top-level target of the grammar.
*/
cycle : cycle def_or_term END | /* empty */ { initsym(); }

def_or_term : compound_def | opt_term { execute($1); do_stop(); } ;

/*
    A compound definition is an optional module, followed by an optional
    private section, followed by a public section.
*/
compound_def : opt_module opt_private public { exitmod(); } ;

opt_module : module | /* empty */ ;

module : MODULE USR_ { initmod($2); } ;

opt_private : private | /* empty */ ;

private : JPRIVATE { initpriv(); } seq_definition { stoppriv(); } ;

opt_public : public | /* empty */ ;

public : JPUBLIC seq_definition ;

/*
    A definition sequence is one or more definitions, separated by ';' .
*/
seq_definition : seq_definition ';' opt_definition | opt_definition ;

/*
    A definition is an atomic symbol and a term, separated by '==' .
*/
opt_definition : USR_ { enterdef($1, (Stack *)1); } JEQUAL opt_term
		 { enterdef($1, $4); }
	       | private public END { exitpriv(); }
	       | module opt_private opt_public END { exitmod(); }
	       | /* empty */ ;

opt_term : term { vec_push($1, 0); vec_reverse($1); }
	 | /* empty */ { $$ = 0; } ;

/*
    A term is one or more factors.
*/
term	: term factor	{ vec_push($1, $2); }
	| factor	{ Stack *List = 0; vec_push(List, $1); $$ = List; } ;

/*
    A factor is a constant, or a list, or a set.
*/
factor  : USR_		{ $$ = (intptr_t)qualify($1); }
	| BOOLEAN_
	| CHAR_	
	| INTEGER_
	| STRING_	{ $$ = (intptr_t)$1; }
	| FLOAT_	{ $$ = pack($1);  }
	| list		{ $$ = (intptr_t)$1; }
	| set ;

list : '[' opt_term ']' { $$ = $2; } ;

set : '{' opt_set '}' { $$ = $2; } ;

opt_set : opt_set char_or_int { $$ |= 1 << $2; } | /* empty */ { $$ = 0; } ;

char_or_int : CHAR_ | INTEGER_ ;
