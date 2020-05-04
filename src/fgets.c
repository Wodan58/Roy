/*
    module  : fgets.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef FGETS_C
#define FGETS_C

/**
fgets  :  S  ->  S L
L is the next available line (as a string) from stream S.
*/
void do_fgets(void)
{
    char *buf;
    size_t leng = 1, size = INPLINEMAX;

    COMPILE;
    buf = GC_malloc_atomic(size);
    strcpy(buf, "\"");
    while (fgets(buf + leng, size - leng, (FILE *)stack[-1])) {
	if ((leng = strlen(buf)) > 0 && buf[leng - 1] == '\n')
	    break;
	buf = GC_realloc(buf, size <<= 1);
    }
    do_push((intptr_t)buf | JLAP_INVALID);
}
#endif
