/*
    module  : jsetinsets.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETINSETS_C
#define JSETINSETS_C

/**
jsetinsets  :  obj top bottom left right  ->
Sets the insets to the specified values.
*/
void do_jsetinsets(void)
{
    int obj, top, bottom, left, right;

    COMPILE;
    right = do_pop();
    left = do_pop();
    bottom = do_pop();
    top = do_pop();
    obj = do_pop();
    j_setinsets(obj, top, bottom, left, right);
}
#endif
