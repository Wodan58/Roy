/*
    module  : putchars.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef PUTCHARS_C
#define PUTCHARS_C

/**
3130  putchars  :  D	"abc.."  ->
Writes abc.. (without quotes)
*/
void do_putchars(void)
{
    COMPILE;
    printf("%s", get_string(stack_pop()));
}
#endif
