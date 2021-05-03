/*
    module  : jdrawpolygon.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWPOLYGON_C
#define JDRAWPOLYGON_C

/**
jdrawpolygon  :  obj len x y  ->
Draws an unfilled polygon based on first len elements in x and y.
*/
void do_jdrawpolygon(void)
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
    j_drawpolygon(obj, len, x, y);
}
#endif
