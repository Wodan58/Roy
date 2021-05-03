/*
    module  : jsetalign.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETALIGN_C
#define JSETALIGN_C

/**
jsetalign  :  obj align  ->
Sets the alignment in component obj to align. Needs a flowlayout manager.
*/
void do_jsetalign(void)
{
    int obj, align;

    COMPILE;
    align = do_pop();
    obj = do_pop();
    j_setalign(obj, align);
}
#endif
