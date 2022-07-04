%{
/*
    module  : parse.y
    version : 1.18
    date    : 06/21/22
*/
#include "joy.h"
%}

%token MODULE JPRIVATE JPUBLIC JEQUAL END

%token <num> UNKNOWN_		0
%token <num> INDEX_		1
%token <str> USR_		2
%token <fun> ANON_FUNCT_	3
%token <num> BOOLEAN_		4
%token <num> CHAR_		5
%token <num> INTEGER_		6
%token <set> SET_		7
%token <str> STRING_		8
%token <ptr> LIST_		9
%token <dbl> FLOAT_		10
%token <fil> FILE_		11

%type <num> char_or_int
%type <set> opt_set set
%type <ptr> opt_term term list
%type <val> factor

%union {
    char *str;		/* USR, STRING */
    void (*fun)(void);	/* ANON_FUNC */
    int64_t num;	/* INDEX, BOOLEAN, CHAR, INTEGER */
    uint64_t set;	/* SET */
    Stack *ptr;		/* LIST */
    double dbl;		/* FLOAT */
    FILE *fil;		/* FILE */
    value_t val;	/* NANBOX */
};

%%

/*
    Cycle is the top-level target of the grammar.
*/
cycle : cycle def_or_term END | /* empty */ { initsym(); }

def_or_term : compound_def | opt_term { execute($1); do_stop(); } ;

/*
    A compound definition is an optional module, followed by an optional
    private section, followed by an optional public section.
*/
compound_def : public
             | private opt_public { exitpriv(); }
             | module opt_private opt_public { exitmod(); } ;

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
    An optional definition is a definition or nothing at all.
*/
opt_definition : definition | /* empty */ ;

/*
    A definition is an atomic symbol and a term, separated by '=='
    or it is a compound definition.
*/
definition : USR_ { enterdef($1, 0); } JEQUAL opt_term { enterdef($1, $4); }
	   | private opt_public END { exitpriv(); }
	   | module opt_private opt_public END { exitmod(); } ;

opt_term : term { value_t v; MK_INITIAL(v); vec_push($1, v); vec_reverse($1); }
	 | /* empty */ { Stack *list; vec_init(list); $$ = list; } ;

/*
    A term is one or more factors.
*/
term	: term factor	{ vec_push($1, $2); }
	| factor	{ Stack *list; vec_init(list); vec_push(list, $1);
                          $$ = list; } ;

/*
    A factor is a constant, or a list, or a set.
*/
factor  : USR_		{ $$ = qualify($1); }
	| BOOLEAN_	{ $$ = MAKE_BOOLEAN($1); }
	| CHAR_		{ $$ = MAKE_CHAR($1); }
	| INTEGER_	{ $$ = MAKE_INTEGER($1); }
	| STRING_	{ $$ = MAKE_USR_STRING($1); }
	| FLOAT_	{ $$ = MAKE_DOUBLE($1); }
	| list		{ $$ = MAKE_LIST($1); }
	| set 		{ $$ = MAKE_SET($1); } ;

list	: '[' opt_term ']' { $$ = $2; } ;

set	: '{' opt_set '}' { $$ = $2; } ;

opt_set : opt_set char_or_int { if ($2 < 0 || $2 >= SETSIZE_)
				yyerror("small numeric expected in set");
				else $$ |= (uint64_t)1 << $2; }
	| /* empty */ { $$ = 0; } ;

char_or_int : CHAR_ | INTEGER_ ;
