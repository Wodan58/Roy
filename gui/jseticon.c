/*
    module  : jseticon.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETICON_C
#define JSETICON_C

/**
jseticon  :  frame icon  ->
Sets the image icon to display when the frame is iconized. Not all platforms
support the concept of iconizing a window.
*/
void do_jseticon(void)
{
    int frame, icon;

    COMPILE;
    icon = do_pop();
    frame = do_pop();
    j_seticon(frame, icon);
}
#endif
