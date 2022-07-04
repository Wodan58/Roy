/*
    module  : formatf.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef FORMATF_C
#define FORMATF_C

/**
1770  formatf  :  DDDDA 	F C I J  ->  S
S is the formatted version of F in mode C
('e or 'E = exponential, 'f = fractional,
'g or G = general with lower or upper case letters)
with maximum width I and precision J.
*/
void do_formatf(void)
{
    double dbl;
    int prec, width, type, leng;
    char format[MAXNUM], *result;

    FOURPARAMS;
    INTEGERS2;
    prec = GET_AS_INTEGER(stack_pop());
    width = GET_AS_INTEGER(stack_pop());
    CHARACTER;
    type = GET_AS_CHAR(stack_pop());
    CHECKFORMATF(type);
    strcpy(format, "%*.*g");
    format[4] = type;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    leng = snprintf(0, 0, format, width, prec, dbl) + 1;
    result = GC_malloc_atomic(leng + 2);
    *result = '"';
    snprintf(result + 1, leng, format, width, prec, dbl);
    stack[-1] = MAKE_USR_STRING(result);
}
#endif
