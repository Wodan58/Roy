/*
    module  : strftime.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef STRFTIME_C
#define STRFTIME_C

#ifdef MKTIME_X
#undef MKTIME_X
#undef MKTIME_C
#endif

#include "mktime.c"

/**
strftime  :  T S1  ->  S2
Formats a list T in the format of localtime or gmtime
using string S1 and pushes the result S2.
*/
void do_strftime(void)
{
    struct tm t;
    size_t length;
    char *fmt, *result;

    BINARY;
    fmt = (char *)do_pop();
    decode_time(&t);
    length = INPLINEMAX;
    result = GC_malloc_atomic(length);
    strftime(result + 1, length, fmt, &t);
    result[0] = '"';
    stack[-1] = (intptr_t)result | JLAP_INVALID;
}
#endif
