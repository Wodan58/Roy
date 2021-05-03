/*
    module  : jshowpopup.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSHOWPOPUP_C
#define JSHOWPOPUP_C

/**
jshowpopup  :  obj xpos ypos  ->
Shows the component at specified position (xpos, ypos).
*/
void do_jshowpopup(void)
{
    int obj, xpos, ypos;

    COMPILE;
    ypos = do_pop();
    xpos = do_pop();
    obj = do_pop();
    j_showpopup(obj, xpos, ypos);
}
#endif
