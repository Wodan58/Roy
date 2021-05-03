/*
    module  : jgetkeycode.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETKEYCODE_C
#define JGETKEYCODE_C

/**
jgetkeycode  :  obj  ->  code
Return the integer key code of the last key pressed.
*/
void do_jgetkeycode(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getkeycode(obj);
    do_push(temp);
}
#endif
