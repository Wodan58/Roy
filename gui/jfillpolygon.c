/*
    module  : jfillpolygon.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JFILLPOLYGON_C
#define JFILLPOLYGON_C

/**
jfillpolygon  :  obj len x y  ->
Draws a filled polygon based on first len elements in x and y.
*/
void do_jfillpolygon(void)
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
    j_fillpolygon(obj, len, x, y);
}
#endif
