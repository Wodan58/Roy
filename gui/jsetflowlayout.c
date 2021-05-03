/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETFLOWLAYOUT_C
#define JSETFLOWLAYOUT_C

/**
jsetflowlayout  :  obj align  ->
Adds a flowlayout manager to component obj with the specified alignment.
*/
void do_jsetflowlayout(void)
{
    int obj, align;

    COMPILE;
    align = do_pop();
    obj = do_pop();
    j_setflowlayout(obj, align);
}
#endif
