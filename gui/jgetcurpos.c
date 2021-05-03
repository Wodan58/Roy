/*
    module  : jgetcurpos.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETCURPOS_C
#define JGETCURPOS_C

/**
jgetcurpos  :  obj  ->  position
Returns the position, in characters, of the text cursor.
*/
void do_jgetcurpos(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getcurpos(obj);
    do_push(temp);
}
#endif
