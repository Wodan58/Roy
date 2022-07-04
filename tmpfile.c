/*
    module  : tmpfile.c
    version : 1.1
    date    : 06/21/22
*/
#include "joy.h"

static int bucket, filenum;

/*
    remove_tmpfiles - remove temporary files and report failures.
*/
void remove_tmpfiles(void)
{
    int i, j = 0;
    char str[MAXNUM];

    i = bucket ? 0 : 1;
    for (; i <= filenum; i++) {
        sprintf(str, "t%d", i);
        if (remove(str))
            j++;
    }
    if (j)
        fprintf(stderr, "removing %d temporary files failed\n", j);
}

/*
    my_tmpfile - create a temporary file or die trying. This can only happen if
                 the file already exists as a readonly file.
*/
FILE *my_tmpfile(void)
{
    FILE *fp;
    char str[MAXNUM];

    sprintf(str, "t%d", ++filenum);
    if ((fp = fopen(str, "w+")) == 0) {
        fprintf(stderr, "error creating tmpfile\n");
        exit(0);
    }
    return fp;
}

/*
    print_tmpfile - print the contents of the temporary file to the bucket
                    file t0. The temporary file pointer is program, that is
                    restored to the old value.
*/
void print_tmpfile(FILE *old)
{
    int ch;
    FILE *fp;

    if (!bucket)
        bucket = 1;
    rewind(program);
    if ((fp = fopen("t0", "a")) == 0)
        fp = stdout;
    while ((ch = getc(program)) != EOF)
        putc(ch, fp);
    if (fp != stdout)
        fclose(fp);
    fclose(program);
    program = old;
}

/*
    print_bucket - print the contents of the collected temporary files to
                   stdout.
*/
void print_bucket(void)
{
    int ch;
    FILE *fp;

    if (!bucket)
        return;
    if ((fp = fopen("t0", "r")) == 0)
        return;
    while ((ch = getc(fp)) != EOF)
        putchar(ch);
    fclose(fp);
}
