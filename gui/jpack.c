/*
    module  : jpack.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JPACK_C
#define JPACK_C

/**
jpack  :  obj  ->
Resizes component to the minimal size of contained components.
*/
void do_jpack(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_pack(obj);
}
#endif
