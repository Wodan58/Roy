/*
    module  : jgetinheight.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETINHEIGHT_C
#define JGETINHEIGHT_C

/**
jgetinheight  :  cont  ->  height
Returns the height of the client size.
*/
void do_jgetinheight(void)
{
    int cont, temp;

    COMPILE;
    cont = do_pop();
    temp = j_getinheight(cont);
    do_push(temp);
}
#endif
