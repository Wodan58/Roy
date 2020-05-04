/*
    module  : body.c
    version : 1.12
    date    : 01/19/20
*/
#ifndef BODY_C
#define BODY_C

/**
body  :  U  ->  [P]
Quotation [P] is the body of user-defined symbol U.
*/
void do_body(void)
{
#ifdef COMPILING
    const char *Name;

    UNARY;
#ifdef COMPILING
    Name = (const char *)(stack[-1] & ~JLAP_INVALID);
#else
    Name = (const char *)stack[-1];
#endif
    stack[-1] = lookup(Name);
#endif
}
#endif
