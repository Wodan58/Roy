/*
    module  : jgetxpos.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETXPOS_C
#define JGETXPOS_C

/**
jgetxpos  :  obj  ->  position
Returns the horizontal position of component obj in its parent's coordinate
space.
*/
void do_jgetxpos(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getxpos(obj);
    do_push(temp);
}
#endif
