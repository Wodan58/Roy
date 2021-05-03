/*
    module  : jkeylistener.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JKEYLISTENER_C
#define JKEYLISTENER_C

/**
jkeylistener  :  obj  ->  event
Adds a new key listener to component obj, and returns its event number.
*/
void do_jkeylistener(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_keylistener(obj);
    do_push(temp);
}
#endif
