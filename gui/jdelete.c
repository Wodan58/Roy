/*
    module  : jdelete.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDELETE_C
#define JDELETE_C

/**
jdelete  :  obj start end  ->
Deletes text from starting position start to ending position end.
*/
PRIVATE void do_jdelete(void)
{
    int obj, start, end;

    COMPILE;
    end = do_pop();
    start = do_pop();
    obj = do_pop();
    j_delete(obj, start, end);
}
#endif
