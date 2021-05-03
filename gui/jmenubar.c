/*
    module  : jmenubar.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JMENUBAR_C
#define JMENUBAR_C

/**
jmenubar  :  obj  ->  event
Creates a new menubar and returns its event number.
*/
void do_jmenubar(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_menubar(obj);
    do_push(temp);
}
#endif
