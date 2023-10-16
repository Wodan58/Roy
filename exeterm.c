/*
    module  : exeterm.c
    version : 1.6
    date    : 10/12/23
*/
#include "globals.h"

#ifdef TRACING
static void trace(pEnv env, Node node, FILE *fp)
{
    if (!env->debugging)
	return;
    writestack(env, env->stck, fp);
    fprintf(fp, " : ");
    writefactor(env, node, fp);
    fputc('\n', fp);
    fflush(fp);
}
#endif

/*
    exeterm - execute the fetch, decode, evaluate cycle.
*/
void exeterm(pEnv env, NodeList *prog)
{
    int i;
    Node node;

    for (i = pvec_cnt(prog) - 1; i >= 0; i--) {
        node = pvec_nth(prog, i);
#ifdef TRACING
	trace(env, node, stdout);
#endif
	if (node.op == ANON_FUNCT_)
	    (*node.u.proc)(env);
        else if (node.op == USR_LIST_)
	    exeterm(env, node.u.lis);
	else
	    env->stck = pvec_add(env->stck, node);
    }
}
