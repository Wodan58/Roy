/*
    module  : jgetpos.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETPOS_C
#define JGETPOS_C

/**
jgetpos  :  obj  ->  xpos ypos
Returns the current position (xpos, ypos).
*/
void do_jgetpos(void)
{
    int obj, xpos, ypos;

    COMPILE;
    obj = do_pop();
    j_getpos(obj, &xpos, &ypos);
    do_push(xpos);
    do_push(ypos);
}
#endif
