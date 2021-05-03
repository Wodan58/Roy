/*
    module  : jdrawpolyline.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWPOLYLINE_C
#define JDRAWPOLYLINE_C

/**
jdrawpolyline  :  obj len x y  ->
Draws a series of line segments based on first len elements in x and y.
*/
void do_jdrawpolyline(void)
{
    Stack *temp;
    int obj, len, *x, *y;

    COMPILE;
    temp = (Stack *)do_pop();
    y = VectorToArray(temp);
    temp = (Stack *)do_pop();
    x = VectorToArray(temp);
    len = do_pop();
    obj = do_pop();
    j_drawpolyline(obj, len, x, y);
}
#endif
