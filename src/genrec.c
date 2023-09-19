/*
    module  : genrec.c
    version : 1.21
    date    : 09/19/23
*/
#ifndef GENREC_C
#define GENREC_C

/**
OK 2740  genrec  :  DDDDU	[B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
void aux_genrec(pEnv env)
{
    int i, j, size;
    Node first, second, third, aggr, node, list;

    PARM(1, DIP);
    aggr = lst_pop(env->stck);			/* item on top of the stack */
    first = lst_back(aggr.u.lis);
    size = lst_size(aggr.u.lis);
    second = lst_at(aggr.u.lis, size - 2);
    third = lst_at(aggr.u.lis, size - 3);
    exeterm(env, first.u.lis);			/* B */
    node = lst_pop(env->stck);
    if (node.u.num)
	exeterm(env, second.u.lis);		/* T */
    else {
	exeterm(env, third.u.lis);		/* R1 */
	lst_push(env->stck, aggr);		/* [[[B] [T] [R1] R2] */
	lst_init(list.u.lis);			/* [] */
	list.op = LIST_;
	node.u.proc = aux_genrec;		/* aux_genrec */
	node.op = ANON_FUNCT_;
	lst_push(list.u.lis, node);		/* [aux_genrec] */
	lst_push(env->stck, list);		/* push on stack */

	cons_(env);				/* build aggregate */
	lst_shallow_copy(list.u.lis, aggr.u.lis);
	(void)lst_pop(list.u.lis);		/* remove [B] [T] [R1] */
	(void)lst_pop(list.u.lis);
	(void)lst_pop(list.u.lis);
	exeterm(env, list.u.lis);		/* R2 */
    }
}

void genrec_(pEnv env)
{
    PARM(4, LINREC);
    cons_(env);
    cons_(env);
    cons_(env);
    aux_genrec(env);
}
#endif
