/*
    module  : jsetxor.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETXOR_C
#define JSETXOR_C

/**
jsetxor  :  obj bool  ->
Changes painting mode to XOR mode, if bool = J_TRUE. In this mode, drawing the
same object in the same color at the same location twice has no net effect.
*/
void do_jsetxor(void)
{
    int obj, bool;

    COMPILE;
    bool = do_pop();
    obj = do_pop();
    j_setxor(obj, bool);
}
#endif
