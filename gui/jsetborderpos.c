/*
    module  : jsetborderpos.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETBORDERPOS_C
#define JSETBORDERPOS_C

/**
jsetborderpos  :  obj pos  ->
Moves component obj at a certain position. The outer container needs a border
layout manager.
*/
void do_jsetborderpos(void)
{
    int obj, pos;

    COMPILE;
    pos = do_pop();
    obj = do_pop();
    j_setborderpos(obj, pos);
}
#endif
