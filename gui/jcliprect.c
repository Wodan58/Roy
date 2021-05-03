/*
    module  : jcliprect.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JCLIPRECT_C
#define JCLIPRECT_C

/**
jcliprect  :  obj x y width height ->
Changes current clipping region to the specified rectangle (x, y, width,
height).
*/
void do_jcliprect(void)
{
    int obj, x, y, width, height;

    COMPILE;
    height = do_pop();
    width = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_cliprect(obj, x, y, width, height);
}
#endif
