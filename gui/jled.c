/*
    module  : jled.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JLED_C
#define JLED_C

/**
jled  :  obj style color  ->  event
Creates a new led component and returns its event number. The LED's shape could
be round if style=J_ROUND or a rectangle of style=J_RECT. The color could be
one of the predefined colors (e.g. J_RED, J_GREEN).
*/
void do_jled(void)
{
    int obj, style, color, temp;

    COMPILE;
    color = do_pop();
    style = do_pop();
    obj = do_pop();
    temp = j_led(obj, style, color);
    do_push(temp);
}
#endif
