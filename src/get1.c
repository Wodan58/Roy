/*
    module  : get1.c
    version : 1.2
    date    : 01/20/20
*/
#ifndef GET1_C
#define GET1_C

/**
get1  :  ->  F
Reads a factor from input and pushes it onto stack.
*/
void do_get1(void)
{
    int type;
    intptr_t Value;
    Stack *List = 0;

    vec_push(List, type = yylex());
    switch (type) {
    case MODULE:
    case JPRIVATE:
    case JPUBLIC:
    case JEQUAL:
    case END:
	Value = 0;
	break;
    case USR_:
	Value = (intptr_t)yylval.str;
	break;
    case ANON_FUNCT_:
	Value = (intptr_t)yylval.fun;
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case SET_:
	Value = yylval.num;
	break;
    case STRING_:
	Value = (intptr_t)yylval.str;
	break;
    case LIST_:
	Value = (intptr_t)yylval.ptr;
	break;
    case FLOAT_:
	memcpy(&Value, &yylval.dbl, sizeof(intptr_t));
	break;
    case FILE_:
	Value = (intptr_t)yylval.fil;
	break;
    }
    vec_push(List, Value);
    do_push((intptr_t)List);
}
#endif
