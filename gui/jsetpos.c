/*
    module  : jsetpos.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETPOS_C
#define JSETPOS_C

/**
jsetpos  :  obj xpos ypos  ->
Relocates the component obj to the specified position (xpos, ypos).
*/
void do_jsetpos(void)
{
    int obj, xpos, ypos;

    COMPILE;
    ypos = do_pop();
    xpos = do_pop();
    obj = do_pop();
    j_setpos(obj, xpos, ypos);
}
#endif
