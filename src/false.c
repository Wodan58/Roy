/*
    module  : false.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef FALSE_C
#define FALSE_C

/**
false  :  ->  false
Pushes the value false.
*/
void do_false(void)
{
    COMPILE;
    do_push(0);
}
#endif
