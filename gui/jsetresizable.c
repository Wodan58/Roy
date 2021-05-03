/*
    module  : jsetresizable.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETRESIZABLE_C
#define JSETRESIZABLE_C

/**
jsetresizable  :  obj resizable  ->
The component cannot be resized, if resizable is J_FALSE.
*/
void do_jsetresizable(void)
{
    int obj, resizable;

    COMPILE;
    resizable = do_pop();
    obj = do_pop();
    j_setresizable(obj, resizable);
}
#endif
