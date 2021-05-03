/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETSCREENWIDTH_C
#define JGETSCREENWIDTH_C

/**
jgetscreenwidth  :  ->  width
Returns the screen width in pixels. If a virtual screen is installed, the
virtual width will be returned.
*/
void do_jgetscreenwidth(void)
{
    COMPILE;
    do_push(j_getscreenwidth());
}
#endif
