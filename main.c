/*
    module  : main.c
    version : 1.19
    date    : 06/29/22
*/
#include "joy.h"

int autoput = INIAUTOPUT, tracegc = INITRACEGC, undeferror = INIUNDEFERR;
int g_argc, library, compiling, debugging;
char **g_argv, *filename;
clock_t startclock;
static jmp_buf begin;

/*
    Abort execution and resume main loop.
*/
void abortexecution()
{
    longjmp(begin, 1);
}

/*
    fatal terminates the program after a stack overflow, likely to result in
    heap corruption that makes it impossible to continue.
*/
#ifndef GC_BDW
void fatal(void)
{
    fflush(stdout);
    fprintf(stderr, "fatal error: memory overflow\n");
    exit(EXIT_FAILURE);
}
#endif

/*
    execerror - print a runtime error to stderr. When compiling print the
		function instead of generating an error.
*/
void execerror(char *message, const char *op)
{
    int leng;
    char str[MAXSTR], *ptr;

    if (!strncmp(op, "do_", 3))
	op += 3;
    leng = strlen(op);
    if ((ptr = strchr(op, '_')) != 0 && ptr != op)
	leng = ptr - op;
    if (!compiling) {
	fflush(stdout);
	fprintf(stderr, "run time error: %s needed for %.*s\n",
		message, leng, op);
	abortexecution();
    }
    if (strncmp(message, "definition", 10)) {
	sprintf(str, "do_%.*s", leng, op);
	print(str);
    }
}

/*
    report_clock - report the amount of time spent and the number of
		   garbage collections.
*/
#ifdef REPORT
void report_clock(void)
{
    double timediff;

    timediff = clock() - startclock;
    timediff /= CLOCKS_PER_SEC;
    fprintf(stderr, "%.2f seconds CPU to execute\n", timediff);
    fprintf(stderr, "%.0f garbage collections\n", (double)GC_get_gc_no());
}
#endif

/*
    copyright - report copyright and compilation date and time.
*/
static void copyright(void)
{
    printf("JOY  -  compiled at %s on %s", __TIME__, __DATE__);
    printf(JVERSION ? " (%s)\n" : "\n", JVERSION);
    printf("Copyright 2022 by Ruurd Wiersma\n");
}

/*
    Test whether it is the interpreter that is executing.
*/
static int is_interpreter(char *argv)
{
    char *ptr;

    if ((ptr = strrchr(argv, '/')) != 0)
	ptr++;
    else
	ptr = argv;
    return !strncmp(ptr, "joy", 3);
}

/*
    options - print help on startup options and exit: options are those that
	      cannot be set from within the language itself.
*/
static void options(int interpreter)
{
    printf("Usage: joy [options] [filename] [parameters]\n");
    printf("options, filename, parameters can be given in any order\n");
    printf("options start with '-' and are all given together\n");
    printf("parameters start with a digit\n");
    printf("the filename parameter cannot start with '-' or a digit\n");
    printf("Options:\n");
    printf("  -h : print this help text and exit\n");
    if (interpreter)
	printf("  -c : compile with compile time evaluation\n");
    printf("  -d : print a trace of program execution\n");
    if (interpreter)
	printf("  -l : compile in library mode\n");
    printf("  -s : dump user-defined functions after execution\n");
    printf("  -v : print a copyright notice\n");
    exit(0);
}

static int start_main(int argc, char *argv[])
{
    int i, j;
    unsigned char verbose = 0, symdump = 0, helping = 0, interpreter;

    /*
	First start the clock.
    */
    startclock = clock();
#ifdef REPORT
    atexit(report_clock);
#endif
    /*
	Initialise the stack. The stack is either a vector or a static array.
	In both cases it needs to be initialised.
    */
    stack_init();
    /*
	Determine whether this is the interpreter executing.
    */
    interpreter = is_interpreter(argv[0]);
    /*
	First look for options. They start with -.
    */
    for (i = 0; i < argc; i++)
	if (argv[i][0] == '-') {
	    for (j = 1; argv[i][j]; j++)
		switch (argv[i][j]) {
		case 'c' : compiling = 1; break;
		case 'd' : debugging = 1; break;
		case 'h' : helping = 1; break;
		case 'l' : library = compiling = 1; break;
		case 's' : symdump = 1; break;
		case 'v' : verbose = 1; break;
		}
	    /*
		Overwrite the options with subsequent parameters.
	    */
	    for (--argc; i < argc; i++)
		argv[i] = argv[i + 1];
	    break;
	}
    /*
	Look for a possible filename parameter. Filenames cannot start with -
	and cannot start with a digit, unless preceded by a path: e.g. './'.
    */
    for (i = 1; i < argc; i++)
	if (!isdigit(argv[i][0])) {
	    if (freopen(filename = argv[i], "r", stdin) == 0) {
		fprintf(stderr, "failed to open the file '%s'.\n", filename);
		return 0;
	    }
	    /*
		Overwrite argv[0] with the filename and shift subsequent
		parameters.
	    */
	    argv[0] = filename;
	    for (--argc; i < argc; i++)
		argv[i] = argv[i + 1];
	    break;
	}
    g_argc = argc;
    g_argv = argv;
    if (verbose)
	copyright();
    if (symdump)
	atexit(dump_table);
    if (helping)
	options(interpreter);
    if (setjmp(begin) && !interpreter)
	return 0;
    do
	yyparse();
    while (interpreter);
    return 0; /* main doesn't return */
}

int main(int argc, char **argv)
{
    int (*volatile m)(int, char **) = start_main;

#ifdef GC_BDW
    GC_INIT();
#else
    GC_init(&argc, fatal);
#endif
    return (*m)(argc, argv);
}
