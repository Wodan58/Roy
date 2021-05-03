/*
    module  : jradiogroup.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JRADIOGROUP_C
#define JRADIOGROUP_C

/**
jradiogroup  :  obj  ->  event
Creates a new radiogroup and returns its event number.
*/
void do_jradiogroup(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_radiogroup(obj);
    do_push(temp);
}
#endif
