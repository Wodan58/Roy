/*
    module  : jplay.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JPLAY_C
#define JPLAY_C

/**
jplay  :  obj  ->
Play a sound object.
*/
void do_jplay(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_play(obj);
}
#endif
