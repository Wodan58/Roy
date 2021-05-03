/*
    module  : jprogressbar.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JPROGRESSBAR_C
#define JPROGRESSBAR_C

/**
jprogressbar  :  obj orient  ->  event
Creats a new progress bar with the specified orientation and returns its event
number. Orientation can be J_HORIZONTAL or J_VERTICAL. The progress bar has
predefined values from 0 to 100. This can be changed via jsetmin and jsetmax.
*/
void do_jprogressbar(void)
{
    int obj, orient, temp;

    COMPILE;
    orient = do_pop();
    obj = do_pop();
    temp = j_progressbar(obj, orient);
    do_push(temp);
}
#endif
