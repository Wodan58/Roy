/*
    module  : jgetinsets.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETINSETS_C
#define JGETINSETS_C

/**
jgetinsets  :  obj side  ->  height
Returns the width of the specified inset. Side can take the following values:
J_TOP: returns the height of the top inset; J_BOTTOM: returns the height of the
bottom inset; J_LEFT: returns the width of the left inset; J_RIGHT: returns the
width of the right inset.
*/
void do_jgetinsets(void)
{
    int obj, side, temp;

    COMPILE;
    side = do_pop();
    obj = do_pop();
    temp = j_getinsets(obj, side);
    do_push(temp);
}
#endif
