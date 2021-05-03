/*
    module  : jgetmousex.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETMOUSEX_C
#define JGETMOUSEX_C

/**
jgetmousex  :  mouselistener  ->  xpos
Returns the current horizontal position of the mouse in its parent's coordinate
space.
*/
void do_jgetmousex(void)
{
    int mouselistener, temp;

    COMPILE;
    mouselistener = do_pop();
    temp = j_getmousex(mouselistener);
    do_push(temp);
}
#endif
