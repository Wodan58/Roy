/*
    module  : jsetstate.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETSTATE_C
#define JSETSTATE_C

/**
jsetstate  :  obj bool  ->
The component becomes selected, if bool is J_TRUE.
*/
void do_jsetstate(void)
{
    int obj, bool;

    COMPILE;
    bool = do_pop();
    obj = do_pop();
    j_setstate(obj, bool);
}
#endif
