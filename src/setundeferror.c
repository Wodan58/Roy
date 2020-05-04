/*
    module  : setundeferror.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef SETUNDEFERROR_C
#define SETUNDEFERROR_C

/**
setundeferror  :  I  ->
Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
void do_setundeferror(void)
{
    UNARY;
    undeferror = do_pop();
}
#endif
