/*
 *  module  : main.c
 *  version : 1.3
 *  date    : 10/11/24
 */
#include "globals.h"

extern table_t yytable[];	/* present in generated code */

static jmp_buf begin;		/* restart with empty program */

void joy(pEnv env);		/* result of compilation */

/*
 * abort execution and restart reading from srcfile; the stack is not cleared.
 */
void abortexecution_(int num)
{
    fflush(stdin);
    longjmp(begin, num);
}

/*
 * main uses some of the code that the interpreter also uses. It is assumed
 * that BDW is used.
 */
int main(int argc, char **argv)
{
    Env env;	/* global variables */
    int i, j;

    GC_INIT();	/* might be needed */
    memset(&env, 0, sizeof(env));
    /*
     * Start the clock.
     */
    env.startclock = clock();
    /*
     * Initial settings.
     */
    env.autoput = INIAUTOPUT;
    env.echoflag = INIECHOFLAG;
    env.undeferror = INIUNDEFERROR;
    env.tracegc = INITRACEGC;
    env.overwrite = INIWARNING;
    /*
     * First look for options. They start with -.
     */
    for (i = 1; i < argc; i++) {
	if (argv[i][0] == '-') {
	    for (j = 1; argv[i][j]; j++) {
		switch (argv[i][j]) {
		case 'd' : env.debugging = 1; break;
		} /* end switch */
	    } /* end for */
	    /*
	     * Overwrite the option(s) with subsequent parameters. Index i is
	     * decreased, because the next parameter is copied to the current
	     * index and i is increased in the for-loop.
	     */
	    for (--argc, j = i--; j < argc; j++)
		argv[j] = argv[j + 1];
	} /* end if */
    } /* end for */
    /*
     * determine argc and argv.
     */
    env.g_argc = argc;
    env.g_argv = argv;
    vec_init(env.stck);		/* start with an empty stack */
    vec_init(env.prog);		/* and an empty program */
    if (!setjmp(begin))	{	/* return here after error or abort */
	joy(&env);		/* evaluate */
	print(&env);		/* print */
    }
    return 0;
}

/*
 * operindex - return the optable entry for an operator.
 */
int operindex(pEnv env, proc_t proc)
{
    int i;

    for (i = 0; yytable[i].proc; i++)
	if (yytable[i].proc == proc)
	    return i;
    return 0;
}

/*
 * nickname - return the name of an operator.
 */
char *nickname(pEnv env, proc_t proc)
{
    int ch;

    ch = operindex(env, proc);
    return yytable[ch].name;
}

/*
 * opername - return the name of an operator.
 */
char *opername(pEnv env, proc_t proc)
{
    int ch;

    ch = operindex(env, proc);
    return yytable[ch].name;
}
