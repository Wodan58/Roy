/*
    module  : ord.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef ORD_C
#define ORD_C

/**
1460  ord  :  DA	C  ->  I
Integer I is the Ascii value of character C (or logical or integer).
*/
void do_ord(void)
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
    stack[-1] = MAKE_INTEGER(ch);
}
#endif
