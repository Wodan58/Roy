/*
    module  : format.c
    version : 1.12
    date    : 01/19/20
*/
#ifndef FORMAT_C
#define FORMAT_C

/**
format  :  N C I J  ->  S
S is the formatted version of N in mode C
('d or 'i = decimal, 'o = octal, 'x or
'X = hex with lower or upper case letters)
with maximum width I and minimum width J.
*/
void do_format(void)
{
    int prec, width, type, leng;
    char format[MAXNUM], *result;

    QUATERN;
    prec = do_pop();
    width = do_pop();
    type = do_pop();
    strcpy(format, "%*.*");
    switch (type) {
    case 'd'  : strcat(format, PRIdPTR);
		break;
    case 'i'  : strcat(format, PRIiPTR);
		break;
    case 'o'  : strcat(format, PRIoPTR);
		break;
    case 'x'  : strcat(format, PRIxPTR);
		break;
    case 'X'  : strcat(format, PRIXPTR);
		break;
    default   : execerror("one of: d i o x X", "format");
		break;
    }
    leng = snprintf(0, 0, format, width, prec, stack[-1]) + 1;
    result = GC_malloc_atomic(leng + 2);
    result[0] = '"';
    snprintf(result + 1, leng, format, width, prec, stack[-1]);
    stack[-1] = (intptr_t)result | JLAP_INVALID;
}
#endif
