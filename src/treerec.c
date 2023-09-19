/*
    module  : treerec.c
    version : 1.17
    date    : 09/19/23
*/
#ifndef TREEREC_C
#define TREEREC_C

/**
OK 2880  treerec  :  DDDU	T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void aux_treerec(pEnv env)
{
    Node aggr, node, list, temp;

    PARM(2, DIP);
    aggr = lst_pop(env->stck);			/* item on top of the stack */
    node = lst_back(env->stck);			/* 2nd item on the stack */
    if (node.op != LIST_) {
	list = lst_back(aggr.u.lis);		/* O */
	exeterm(env, list.u.lis);
    } else {
	lst_push(env->stck, aggr);		/* push [[O] C] back on stack */
	lst_init(temp.u.lis);			/* [] */
	temp.op = LIST_;
	node.u.proc = aux_treerec;		/* aux_treerec */
	node.op = ANON_FUNCT_;
	lst_push(temp.u.lis, node);		/* [aux_treerec] */
	lst_push(env->stck, temp);		/* push on stack */

	cons_(env);				/* build aggregate */
	lst_init(temp.u.lis);
	lst_shallow_copy(temp.u.lis, aggr.u.lis);
	(void)lst_pop(temp.u.lis);		/* remove [O] */
	exeterm(env, temp.u.lis);		/* C */
    }
}

void treerec_(pEnv env)
{
    PARM(3, WHILE);
    cons_(env);
    aux_treerec(env);
}
#endif
