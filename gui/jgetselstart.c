/*
    module  : jgetselstart.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETSELSTART_C
#define JGETSELSTART_C

/**
jgetselstart  :  obj  ->  position
Returns the initial position of any selected text.
*/
void do_jgetselstart(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getselstart(obj);
    do_push(temp);
}
#endif
