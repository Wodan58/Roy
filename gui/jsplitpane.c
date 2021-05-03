/*
    module  : jsplitpane.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSPLITPANE_C
#define JSPLITPANE_C

/**
jsplitpane  :  canvas xpos ypos  ->  event
Create a split pane at position (xpos, ypos).
*/
void do_jsplitpane(void)
{
    int canvas, xpos, ypos, temp;

    COMPILE;
    ypos = do_pop();
    xpos = do_pop();
    canvas = do_pop();
    temp = j_splitpane(canvas, xpos, ypos);
    do_push(temp);
}
#endif
