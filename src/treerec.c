/*
    module  : treerec.c
    version : 1.19
    date    : 09/18/24
*/
#ifndef TREEREC_C
#define TREEREC_C

/**
OK  2880  treerec  :  DDDU  T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerec(pEnv env)
{
    Node aggr, node, list, temp;

    PARM(2, DIP);
    aggr = vec_pop(env->stck);		/* item on top of the stack */
    node = vec_back(env->stck);		/* 2nd item on the stack */
    if (node.op != LIST_) {
	list = vec_back(aggr.u.lis);	/* O */
	exeterm(env, list.u.lis);
    } else {
	vec_push(env->stck, aggr);	/* push [[O] C] back on stack */
	vec_init(temp.u.lis);		/* [] */
	temp.op = LIST_;
	node.u.proc = treerec;		/* treerec */
	node.op = ANON_FUNCT_;
	vec_push(temp.u.lis, node);	/* [treerec] */
	vec_push(env->stck, temp);	/* push on stack */
	cons_(env);			/* build aggregate */
	vec_shallow_copy(temp.u.lis, aggr.u.lis);
	(void)vec_pop(temp.u.lis);	/* remove [O] */
	exeterm(env, temp.u.lis);	/* C */
    }
}

void treerec_(pEnv env)
{
    PARM(3, WHILE);
    cons_(env);
    treerec(env);
}
#endif
