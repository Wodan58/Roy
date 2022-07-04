/*
    module  : fseek.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef FSEEK_C
#define FSEEK_C

/**
1990  fseek  :  DDA	S P W  ->  S B
Stream S is repositioned to position P relative to whence-point W,
where W = 0, 1, 2 for beginning, current position, end respectively.
*/
void do_fseek(void)
{
    FILE *fp;
    int whence, pos;

    COMPILE;
    THREEPARAMS;
    INTEGERS2;
    whence = GET_AS_INTEGER(stack_pop());
    pos = GET_AS_INTEGER(stack[-1]);
    FILE2;
    fp = GET_AS_FILE(stack[-2]);
    stack[-1] = MAKE_BOOLEAN(fseek(fp, pos, whence) != 0);
}
#endif
