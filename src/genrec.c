/*
    module  : genrec.c
    version : 1.24
    date    : 09/18/24
*/
#ifndef GENREC_C
#define GENREC_C

/**
OK  2740  genrec  :  DDDDU  [B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
void genrec(pEnv env)
{
    int i, j, size;
    Node first, second, third, aggr, node, list;

    PARM(1, DIP);
    aggr = vec_pop(env->stck);		/* item on top of the stack */
    first = vec_back(aggr.u.lis);
    size = vec_size(aggr.u.lis);
    second = vec_at(aggr.u.lis, size - 2);
    third = vec_at(aggr.u.lis, size - 3);
    exeterm(env, first.u.lis);		/* B */
    node = vec_pop(env->stck);
    if (node.u.num)
	exeterm(env, second.u.lis);	/* T */
    else {
	exeterm(env, third.u.lis);	/* R1 */
	vec_push(env->stck, aggr);	/* [[[B] [T] [R1] R2] */
	vec_init(list.u.lis);		/* [] */
	list.op = LIST_;
	node.u.proc = aux_genrec;	/* aux_genrec */
	node.op = ANON_FUNCT_;
	vec_push(list.u.lis, node);	/* [aux_genrec] */
	vec_push(env->stck, list);	/* push on stack */
	cons_(env);			/* build aggregate */
	vec_shallow_copy(list.u.lis, aggr.u.lis);
	size = vec_size(list.u.lis) - 3;
	vec_setsize(list.u.lis, size);	/* remove [B] [T] [R1] */
	exeterm(env, list.u.lis);	/* R2 */
    }
}

void genrec_(pEnv env)
{
    PARM(4, LINREC);
    cons_(env);
    cons_(env);
    cons_(env);
    genrec(env);
}
#endif
