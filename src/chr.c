/*
    module  : chr.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef CHR_C
#define CHR_C

/**
1470  chr  :  DA	I  ->  C
C is the character whose Ascii value is integer I (or logical or character).
*/
void do_chr(void)
{
    int ch = 0;

    ONEPARAM;
    NUMERICTYPE;
    if (IS_INTEGER(stack[-1]))
        ch = GET_AS_INTEGER(stack[-1]);
    else if (IS_CHAR(stack[-1]))
        ch = GET_AS_CHAR(stack[-1]);
    else if (IS_BOOLEAN(stack[-1]))
        ch = GET_AS_BOOLEAN(stack[-1]);
    stack[-1] = MAKE_CHAR(ch);
}
#endif
