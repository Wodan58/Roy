/*
    module  : strftime.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef STRFTIME_C
#define STRFTIME_C

#ifdef MKTIME_X
#undef MKTIME_X
#undef MKTIME_C
#endif

#include "mktime.c"

/**
1730  strftime  :  DDA	T S1  ->  S2
Formats a list T in the format of localtime or gmtime
using string S1 and pushes the result S2.
*/
void do_strftime(void)
{
    int length;
    struct tm t;
    char *fmt, *result;

    TWOPARAMS;
    STRING;
    fmt = get_string(stack_pop());
    decode_time(&t);
    length = INPLINEMAX;
    result = GC_malloc_atomic(length);
    strftime(result, length, fmt, &t);
    stack[-1] = MAKE_USR_STRING(stringify(result));
}
#endif
