/*
    module  : jisparent.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JISPARENT_C
#define JISPARENT_C

/**
jisparent  :  obj cont  ->  status
Returns J_TRUE if cont is parent of obj, J_FALSE otherwise.
*/
void do_jisparent(void)
{
    int obj, cont, temp;

    COMPILE;
    cont = do_pop();
    obj = do_pop();
    temp = j_isparent(obj, cont);
    do_push(temp);
}
#endif
