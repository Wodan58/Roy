/*
    module  : fclose.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef FCLOSE_C
#define FCLOSE_C

/**
1830  fclose  :  D	S  ->
Stream S is closed and removed from the stack.
*/
void do_fclose(void)
{
    COMPILE;
    ONEPARAM;
    FILE1;
    fclose(GET_AS_FILE(stack_pop()));
}
#endif
