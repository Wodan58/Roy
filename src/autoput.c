/*
    module  : autoput.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef AUTOPUT_C
#define AUTOPUT_C

/**
autoput  :  ->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
void do_autoput(void)
{
    COMPILE;
    do_push(autoput);
}
#endif
