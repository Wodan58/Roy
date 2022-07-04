/*
    module  : fputchars.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef FPUTCHARS_C
#define FPUTCHARS_C

/**
1970  fputchars  :  D 	S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
void do_fputchars(void)
{
    FILE *fp;
    char *str;

    COMPILE;
    TWOPARAMS;
    STRING;
    str = get_string(stack_pop());
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    fprintf(fp, "%s", str);
}
#endif
