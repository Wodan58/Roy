/*
    module  : jgetinwidth.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETINWIDTH_C
#define JGETINWIDTH_C

/**
jgetinwidth  :  cont  ->  width
Returns the width of the client size.
*/
void do_jgetinwidth(void)
{
    int cont, temp;

    COMPILE;
    cont = do_pop();
    temp = j_getinwidth(cont);
    do_push(temp);
}
#endif
