/*
    module  : jgetmousepos.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETMOUSEPOS_C
#define JGETMOUSEPOS_C

/**
jgetmousepos  :  mouselistener  ->  xpos ypos
Returns the current mouse position (xpos, ypos).
*/
void do_jgetmousepos(void)
{
    int mouselistener, xpos, ypos;

    COMPILE;
    mouselistener = do_pop();
    j_getmousepos(mouselistener, &xpos, &ypos);
    do_push(xpos);
    do_push(ypos);
}
#endif
