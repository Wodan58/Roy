/*
    module  : jgetypos.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETYPOS_C
#define JGETYPOS_C

/**
jgetypos  :  obj  ->  position
Returns the current vertical position of component obj in its parent's
coordinate space.
*/
void do_jgetypos(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getypos(obj);
    do_push(temp);
}
#endif
