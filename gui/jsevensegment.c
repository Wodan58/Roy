/*
    module  : jsevensegment.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSEVENSEGMENT_C
#define JSEVENSEGMENT_C

/**
jsevensegment  :  obj color  ->  event
Creates a new sevensegment display and returns its event number. The color
can be one of the predefined colors (e.g. J_RED, J_GREEN).
*/
void do_jsevensegment(void)
{
    int obj, color, temp;

    COMPILE;
    color = do_pop();
    obj = do_pop();
    temp = j_sevensegment(obj, color);
    do_push(temp);
}
#endif
