/*
    module  : fgets.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef FGETS_C
#define FGETS_C

/**
1890  fgets  :  A	S  ->  S L
L is the next available line (as a string) from stream S.
*/
void do_fgets(void)
{
    FILE *fp;
    char *buf;
    int leng = 1, size = INPLINEMAX;

    COMPILE;
    ONEPARAM;
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    buf = GC_malloc_atomic(size);
    *buf = '"';
    while (fgets(buf + leng, size - leng, fp)) {
        if ((leng = strlen(buf)) > 0 && buf[leng - 1] == '\n')
            break;
        buf = GC_realloc(buf, size <<= 1);
    }
    do_push(MAKE_USR_STRING(buf));
}
#endif
