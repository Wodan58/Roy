/*
    module  : jdrawline.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWLINE_C
#define JDRAWLINE_C

/**
jdrawline  :  obj x1 y1 x2 y2  ->
Draws a line connecting (x1, y1) and (x2, y2).
*/
void do_jdrawline(void)
{
    int obj, x1, y1, x2, y2;

    COMPILE;
    y2 = do_pop();
    x2 = do_pop();
    y1 = do_pop();
    x1 = do_pop();
    obj = do_pop();
    j_drawline(obj, x1, y1, x2, y2);
}
#endif
