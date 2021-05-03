/*
    module  : jsetslidesize.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETSLIDESIZE_C
#define JSETSLIDESIZE_C

/**
jsetslidesize  :  obj val  ->
Changes the slide size to val.
*/
void do_jsetslidesize(void)
{
    int obj, val;

    COMPILE;
    val = do_pop();
    obj = do_pop();
    j_setslidesize(obj, val);
}
#endif
