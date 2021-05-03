/*
    module  : jsetcurpos.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETCURPOS_C
#define JSETCURPOS_C

/**
jsetcurpos  :  obj pos  ->
Change the location of the text cursor to the specified position pos.
*/
void do_jsetcurpos(void)
{
    int obj, pos;

    COMPILE;
    pos = do_pop();
    obj = do_pop();
    j_setcurpos(obj, pos);
}
#endif
