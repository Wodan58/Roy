/*
    module  : jgetmousey.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETMOUSEY_C
#define JGETMOUSEY_C

/**
jgetmousey  :  mouselistener  ->  ypos
Returns the current vertical position of the mouse in its parent's coordinate
space.
*/
void do_jgetmousey(void)
{
    int mouselistener, temp;

    COMPILE;
    mouselistener = do_pop();
    temp = j_getmousey(mouselistener);
    do_push(temp);
}
#endif
