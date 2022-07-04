/*
    module  : false.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef FALSE_C
#define FALSE_C

/**
1000  false  :  A	->  false
Pushes the value false.
*/
void do_false(void)
{
    do_push(MAKE_BOOLEAN(0));
}
/* false.c */
#endif
