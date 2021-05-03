/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETRADIOGROUP_C
#define JSETRADIOGROUP_C

/**
jsetradiogroup  :  rbutton rgroup  ->
Sets radiobutton rbutton group to be the specified radiogroup rgroup. If the
radiobutton is already in a different radiogroup, it is first taken out of that
group.
*/
void do_jsetradiogroup(void)
{
    int rbutton, rgroup;

    COMPILE;
    rgroup = do_pop();
    rbutton = do_pop();
    j_setradiogroup(rbutton, rgroup);
}
#endif
