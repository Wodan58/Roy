/*
    module  : jgetkeychar.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETKEYCHAR_C
#define JGETKEYCHAR_C

/**
jgetkeychar  :  obj  ->  ascii
Return the ascii value of the last key pressed.
*/
void do_jgetkeychar(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getkeychar(obj);
    do_push(temp);
}
#endif
