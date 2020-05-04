/*
    module  : formatf.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef FORMATF_C
#define FORMATF_C

/**
formatf  :  F C I J  ->  S
S is the formatted version of F in mode C
('e or 'E = exponential, 'f = fractional,
'g or G = general with lower or upper case letters)
with maximum width I and precision J.
*/
void do_formatf(void)
{
    real_t dbl;
    int prec, width, leng;
    char format[MAXNUM], *result;

    QUATERN;
    prec = do_pop();
    width = do_pop();
    strcpy(format, "%*.*g");
    format[4] = do_pop();
    if (!strchr("eEfgG", format[4]))
	execerror("one of: e E f g G", "formatf");
    dbl = unpack(stack[-1]);
    leng = snprintf(0, 0, format, width, prec, dbl) + 1;
    result = GC_malloc_atomic(leng + 2);
    result[0] = '"';
    snprintf(result + 1, leng, format, width, prec, dbl);
    stack[-1] = (intptr_t)result | JLAP_INVALID;
}
#endif
