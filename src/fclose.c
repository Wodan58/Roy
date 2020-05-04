/*
    module  : fclose.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef FCLOSE_C
#define FCLOSE_C

/**
fclose  :  S  ->
Stream S is closed and removed from the stack.
*/
void do_fclose(void)
{
    FILE *fp;

    COMPILE;
    if ((fp = (FILE *)do_pop()) != 0)
	fclose(fp);
}
#endif
