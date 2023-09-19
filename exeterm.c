/*
    module  : exeterm.c
    version : 1.4
    date    : 09/18/23
*/
#include "globals.h"

/*
    exeterm - execute the fetch, decode, evaluate cycle.
*/
void exeterm(pEnv env, NodeList *prog)
{
    int i;
    Node node;

    for (i = lst_size(prog) - 1; i >= 0; i--) {
        node = lst_at(prog, i);
#ifdef TRACING
	if (env->debugging) {
	    writestack(env, env->stck, stdout);
	    printf(" : ");
	    writefactor(env, node, stdout);
	    putchar('\n');
	    fflush(stdout);
	}
#endif
        switch (node.op) {
	case USR_LIST_:
	    exeterm(env, node.u.lis);
	    break;
	case ANON_FUNCT_:
	    (*node.u.proc)(env);
	    break;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	case BIGNUM_:
	case USR_STRING_:
	    lst_push(env->stck, node);
	    break;
	}
    }
}
