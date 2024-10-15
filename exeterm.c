/*
    module  : exeterm.c
    version : 1.11
    date    : 10/11/24
*/
#include "globals.h"

#ifdef TRACING
static void my_trace(pEnv env, Node node, FILE *fp)
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
 * exeterm - execute the fetch, decode, evaluate cycle.
 */
void exeterm(pEnv env, NodeList prog)
{
    int i;
    Node node;

    for (i = vec_size(prog) - 1; i >= 0; i--) {
        node = vec_at(prog, i);
#ifdef TRACING
	my_trace(env, node, stdout);
#endif
	if (node.op == ANON_FUNCT_)
	    (*node.u.proc)(env);
	else
	    vec_push(env->stck, node);
    }
}
