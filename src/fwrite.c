/*
    module  : fwrite.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef FWRITE_C
#define FWRITE_C

/**
1920  fwrite  :  D	S L  ->  S
A list of integers are written as bytes to the current position of stream S.
*/
void do_fwrite(void)
{
    FILE *fp;
    Stack *list;
    int i, leng;
    unsigned char *buf;

    COMPILE;
    TWOPARAMS;
    LIST;
    list = (Stack *)GET_AS_LIST(stack_pop());
    leng = vec_size(list);
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    for (i = 0; i < leng; i++)
        CHECKNUMERIC(vec_at(list, i));
    buf = GC_malloc_atomic(leng);
    for (i = leng - 1; i >= 0; i--)
        buf[leng - 1 - i] = GET_AS_INTEGER(vec_at(list, i));
    fwrite(buf, leng, 1, fp);
}
#endif
