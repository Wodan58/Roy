/*
    module  : fseek.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef FSEEK_C
#define FSEEK_C

/**
fseek  :  S P W  ->  S B
Stream S is repositioned to position P relative to whence-point W,
where W = 0, 1, 2 for beginning, current position, end respectively.
*/
void do_fseek(void)
{
    int whence, pos;

    COMPILE;
    whence = do_pop();
    pos = do_pop();
    whence = fseek((FILE *)stack[-1], pos, whence) != 0;
    do_push(whence);
}
#endif
