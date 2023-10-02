/*
    module  : treegenrec.c
    version : 1.17
    date    : 10/02/23
*/
#ifndef TREEGENREC_C
#define TREEGENREC_C

/**
OK 2890  treegenrec  :  DDDDU	T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
void treegenrec(pEnv env)
{
    Node prog, node, list, temp;

    PARM(1, DIP);
    env->stck = pvec_pop(env->stck, &prog);	/* item on top of the stack */
    node = pvec_lst(env->stck);				/* 2nd item on stack */
    if (node.op != LIST_) {
	list = pvec_lst(prog.u.lis);			/* O1 */
	exeterm(env, list.u.lis);
    } else {
	list = pvec_nth(prog.u.lis, 1);			/* O2 */
	exeterm(env, list.u.lis);
	env->stck = pvec_add(env->stck, prog);		/* push [[O1] [O2] C] */
	temp.u.lis = pvec_init();			/* [] */
	temp.op = LIST_;
	node.u.proc = treegenrec;			/* treegenrec */
	node.op = ANON_FUNCT_;
	temp.u.lis = pvec_add(temp.u.lis, node);	/* [treegenrec] */
	env->stck = pvec_add(env->stck, temp);		/* push on stack */
	cons_(env);					/* build aggregate */
	list.u.lis = pvec_init();
	pvec_shallow_copy(list.u.lis, prog.u.lis);
	list.u.lis = pvec_del(list.u.lis);		/* remove [O1] */
	list.u.lis = pvec_del(list.u.lis);		/* remove [O2] */
	exeterm(env, list.u.lis);			/* C */
    }
}

void treegenrec_(pEnv env)
{			/* T [O1] [O2] [C] */
    PARM(4, IFTE);
    cons_(env);
    cons_(env);
    treegenrec(env);
}
#endif
