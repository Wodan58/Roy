/*
    module  : fread.c
    version : 1.14
    date    : 01/20/20
*/
#ifndef FREAD_C
#define FREAD_C

/**
fread  :  S I  ->  S L
I bytes are read from the current position of stream S
and returned as a list of I integers.
*/
void do_fread(void)
{
    int i, count;
    Stack *root = 0;
    unsigned char *buf;

    COMPILE;
    count = do_pop();
    buf = GC_malloc_atomic(count);
    for (i = fread(buf, 1, count, (FILE *)stack[-1]) - 1; i >= 0; i--)
	vec_push(root, buf[i]);
    do_push((intptr_t)root);
}
#endif
