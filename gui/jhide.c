/*
    module  : jhide.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JHIDE_C
#define JHIDE_C

/**
jhide  :  obj  ->
Hides the component obj.
*/
void do_jhide(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_hide(obj);
}
#endif
