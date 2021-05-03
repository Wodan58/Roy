/*
    module  : jseteditable.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETEDITABLE_C
#define JSETEDITABLE_C

/**
jseteditable  :  obj bool  ->
Allows to make the component editable (bool=J_TRUE) or read-only (bool=J_FALSE).
*/
void do_jseteditable(void)
{
    int obj, bool;

    COMPILE;
    bool = do_pop();
    obj = do_pop();
    j_seteditable(obj, bool);
}
#endif
