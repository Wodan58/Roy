/*
    module  : jgetaction.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETACTION_C
#define JGETACTION_C

/**
jgetaction  :  ->  event
Returns the next event, or 0 of no event available.
*/
void do_jgetaction(void)
{
    COMPILE;
    do_push(j_getaction());
}
#endif
