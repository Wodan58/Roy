/*
    module  : putchars.c
    version : 1.11
    date    : 06/23/20
*/
#ifndef PUTCHARS_C
#define PUTCHARS_C

/**
putchars  :  "abc.."  ->
Writes abc.. (without quotes)
*/
void do_putchars(void)
{
    intptr_t Value;

    COMPILE;
    if ((Value = do_pop()) != 0)
	printf("%s", (char *)Value);
}
#endif
