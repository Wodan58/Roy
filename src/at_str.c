/*
    module  : at_str.c
    version : 1.1
    date    : 03/15/20
*/
#ifndef AT_STR_C
#define AT_STR_C

/**
at_str  :  A I  ->  X
X (= A[I]) is the member of A at position I.
*/
void do_at_str(void)
{
    int index;
    char *str;

    BINARY;
    index = do_pop();
    str = (char *)stack[-1];
    stack[-1] = str[index];
}
#endif
