/*
    module  : jadd.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JADD_C
#define JADD_C

/**
jadd  :  obj cont  ->
Adds component obj to container cont.
*/
void do_jadd(void)
{
    int obj, cont;

    COMPILE;
    cont = do_pop();
    obj = do_pop();
    j_add(obj, cont);
}
#endif
