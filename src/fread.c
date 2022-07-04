/*
    module  : fread.c
    version : 1.15
    date    : 06/21/22
*/
#ifndef FREAD_C
#define FREAD_C

/**
1910  fread  :  DA	S I  ->  S L
I bytes are read from the current position of stream S
and returned as a list of I integers.
*/
void do_fread(void)
{
    FILE *fp;
    Stack *root;
    int i, count;
    unsigned char *volatile buf;

    COMPILE;
    TWOPARAMS;
    INTEGER;
    count = GET_AS_INTEGER(stack_pop());
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    buf = GC_malloc_atomic(count);
    vec_init(root);
    for (i = fread(buf, 1, count, fp) - 1; i >= 0; i--)
        vec_push(root, MAKE_INTEGER(buf[i]));
    stack[-1] = MAKE_LIST(root);
}
#endif
