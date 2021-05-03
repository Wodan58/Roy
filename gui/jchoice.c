/*
    module  : jchoice.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JCHOICE_C
#define JCHOICE_C

/**
jchoice  :  obj  ->  event
Creates a new choice component and returns its event number.
*/
void do_jchoice(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_choice(obj);
    do_push(temp);
}
#endif
