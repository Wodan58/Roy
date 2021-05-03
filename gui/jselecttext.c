/*
    module  : jselecttext.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSELECTTEXT_C
#define JSELECTTEXT_C

/**
jselecttext  :  obj start end  ->
Selects text from starting position start to ending position end.
*/
void do_jselecttext(void)
{
    int obj, start, end;

    COMPILE;
    end = do_pop();
    start = do_pop();
    obj = do_pop();
    j_selecttext(obj, start, end);
}
#endif
