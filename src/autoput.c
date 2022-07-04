/*
    module  : autoput.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef AUTOPUT_C
#define AUTOPUT_C

/**
1090  autoput  :  A	->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
void do_autoput(void)
{
    COMPILE;
    do_push(MAKE_INTEGER(autoput));
}
#endif
