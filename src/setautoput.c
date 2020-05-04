/*
    module  : setautoput.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef SETAUTOPUT_C
#define SETAUTOPUT_C

/**
setautoput  :  I  ->
Sets value of flag for automatic put to I (if I = 0, none;
if I = 1, put; if I = 2, stack).
*/
void do_setautoput(void)
{
    COMPILE;
    autoput = do_pop();
}
#endif
