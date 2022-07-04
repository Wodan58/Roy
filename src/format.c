/*
    module  : format.c
    version : 1.13
    date    : 06/21/22
*/
#ifndef FORMAT_C
#define FORMAT_C

/**
1760  format  :  DDDDA	N C I J  ->  S
S is the formatted version of N in mode C
('d or 'i = decimal, 'o = octal, 'x or
'X = hex with lower or upper case letters)
with maximum width I and minimum width J.
*/
void do_format(void)
{
    int prec, width, type, leng;
    char format[MAXNUM], *result;

    FOURPARAMS;
    INTEGERS2;
    prec = GET_AS_INTEGER(stack_pop());
    width = GET_AS_INTEGER(stack_pop());
    CHARACTER;
    type = GET_AS_CHAR(stack_pop());
    CHECKFORMAT(type);
    strcpy(format, "%*.*ld");
    format[5] = type;
    NUMERICTYPE;
    leng = snprintf(0, 0, format, width, prec, GET_AS_INTEGER(stack[-1])) + 1;
    result = GC_malloc_atomic(leng + 2);
    *result = '"';
    snprintf(result + 1, leng, format, width, prec, GET_AS_INTEGER(stack[-1]));
    stack[-1] = MAKE_USR_STRING(result);
}
#endif
