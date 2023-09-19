/*
    module  : treegenrec.c
    version : 1.16
    date    : 09/19/23
*/
#ifndef TREEGENREC_C
#define TREEGENREC_C

/**
OK 2890  treegenrec  :  DDDDU	T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
void aux_treegenrec(pEnv env)
{
    Node prog, node, list, temp;

    PARM(1, DIP);
    prog = lst_pop(env->stck);		/* item on top of the stack */
    node = lst_back(env->stck);		/* 2nd item on the stack */
    if (node.op != LIST_) {
	list = lst_back(prog.u.lis);	/* O1 */
	exeterm(env, list.u.lis);
    } else {
	list = lst_at(prog.u.lis, 1);	/* O2 */
	exeterm(env, list.u.lis);
	lst_push(env->stck, prog);	/* push [[O1] [O2] C] */
	lst_init(temp.u.lis);		/* [] */
	temp.op = LIST_;
	node.u.proc = aux_treegenrec;	/* aux_treegenrec */
	node.op = ANON_FUNCT_;
	lst_push(temp.u.lis, node);	/* [aux_treegenrec] */
	lst_push(env->stck, temp);	/* push on stack */
	cons_(env);			/* build aggregate */

	vec_init(list.u.lis);
	lst_shallow_copy(list.u.lis, prog.u.lis);
	(void)lst_pop(list.u.lis);	/* remove [O1] */
	(void)lst_pop(list.u.lis);	/* remove [O2] */
	exeterm(env, list.u.lis);	/* C */
    }
}

void treegenrec_(pEnv env)
{			/* T [O1] [O2] [C] */
    PARM(4, IFTE);
    cons_(env);
    cons_(env);
    aux_treegenrec(env);
}
#endif
