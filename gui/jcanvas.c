/*
    module  : jcanvas.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JCANVAS_C
#define JCANVAS_C

/**
jcanvas  :  obj width height  ->  event
Creates a new canvas component with the given width and height and returns its
event number. A canvas can be used for general drawing functions. A canvas
generates an event, if its size changes. On error -1 will be returned.
*/
void do_jcanvas(void)
{
    int obj, width, height, temp;

    COMPILE;
    height = do_pop();
    width = do_pop();
    obj = do_pop();
    temp = j_canvas(obj, width, height);
    do_push(temp);
}
#endif
