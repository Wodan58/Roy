/*
    module  : genrec.c
    version : 1.23
    date    : 10/12/23
*/
#ifndef GENREC_C
#define GENREC_C

/**
OK 2740  genrec  :  DDDDU	[B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
void genrec(pEnv env)
{
    int i, j, size;
    Node first, second, third, aggr, node, list;

    PARM(1, DIP);
    env->stck = pvec_pop(env->stck, &aggr);	/* item on top of the stack */
    first = pvec_lst(aggr.u.lis);
    size = pvec_cnt(aggr.u.lis);
    second = pvec_nth(aggr.u.lis, size - 2);
    third = pvec_nth(aggr.u.lis, size - 3);
    exeterm(env, first.u.lis);			/* B */
    env->stck = pvec_pop(env->stck, &node);
    if (node.u.num)
	exeterm(env, second.u.lis);		/* T */
    else {
	exeterm(env, third.u.lis);		/* R1 */
	env->stck = pvec_add(env->stck, aggr);	/* [[[B] [T] [R1] R2] */
	list.u.lis = pvec_init();		/* [] */
	list.op = LIST_;
	node.u.proc = aux_genrec;		/* aux_genrec */
	node.op = ANON_FUNCT_;
	list.u.lis = pvec_add(list.u.lis, node);/* [aux_genrec] */
	env->stck = pvec_add(env->stck, list);	/* push on stack */

	cons_(env);				/* build aggregate */
	pvec_shallow_copy(list.u.lis, aggr.u.lis);
	list.u.lis = pvec_del(list.u.lis);	/* remove [B] [T] [R1] */
	list.u.lis = pvec_del(list.u.lis);
	list.u.lis = pvec_del(list.u.lis);
	exeterm(env, list.u.lis);		/* R2 */
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
