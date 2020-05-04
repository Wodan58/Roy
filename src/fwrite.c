/*
    module  : fwrite.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef FWRITE_C
#define FWRITE_C

/**
fwrite  :  S L  ->  S
A list of integers are written as bytes to the current position of stream S.
*/
void do_fwrite(void)
{
    Stack *root;
    int i, leng;
    unsigned char *buf;

    COMPILE;
    root = (Stack *)do_pop();
    leng = vec_size(root);
    buf = GC_malloc_atomic(leng);
    for (i = leng - 1; i >= 0; i--)
	buf[leng - 1 - i] = vec_at(root, i);
    fwrite(buf, leng, 1, (FILE *)stack[-1]);
}
#endif
