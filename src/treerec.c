/*
    module  : treerec.c
    version : 1.18
    date    : 10/02/23
*/
#ifndef TREEREC_C
#define TREEREC_C

/**
OK 2880  treerec  :  DDDU	T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerec(pEnv env)
{
    Node aggr, node, list, temp;

    PARM(2, DIP);
    env->stck = pvec_pop(env->stck, &aggr);	/* item on top of the stack */
    node = pvec_lst(env->stck);			/* 2nd item on the stack */
    if (node.op != LIST_) {
	list = pvec_lst(aggr.u.lis);		/* O */
	exeterm(env, list.u.lis);
    } else {
	env->stck = pvec_add(env->stck, aggr);	/* push [[O] C] back on stack */
	temp.u.lis = pvec_init();		/* [] */
	temp.op = LIST_;
	node.u.proc = treerec;			/* treerec */
	node.op = ANON_FUNCT_;
	temp.u.lis = pvec_add(temp.u.lis, node);/* [treerec] */
	env->stck = pvec_add(env->stck, temp);	/* push on stack */
	cons_(env);				/* build aggregate */
	temp.u.lis = pvec_init();
	pvec_shallow_copy(temp.u.lis, aggr.u.lis);
	temp.u.lis = pvec_del(temp.u.lis);	/* remove [O] */
	exeterm(env, temp.u.lis);		/* C */
    }
}

void treerec_(pEnv env)
{
    PARM(3, WHILE);
    cons_(env);
    treerec(env);
}
#endif
