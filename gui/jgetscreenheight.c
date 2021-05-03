/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETSCREENHEIGHT_C
#define JGETSCREENHEIGHT_C

/**
jgetscreenheight  :  ->  height
Returns the screen height in pixels. If a virtual screen is installed, the
virtual height will be returned.
*/
void do_jgetscreenheight(void)
{
    COMPILE;
    do_push(j_getscreenheight());
}
#endif
