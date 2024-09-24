/*
    module  : treegenrec.c
    version : 1.18
    date    : 09/18/24
*/
#ifndef TREEGENREC_C
#define TREEGENREC_C

/**
OK  2890  treegenrec  :  DDDDU  T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
void treegenrec(pEnv env)
{
    Node prog, node, list, temp;

    PARM(1, DIP);
    prog = vec_pop(env->stck);			/* item on top of the stack */
    node = vec_back(env->stck);			/* 2nd item on stack */
    if (node.op != LIST_) {
	list = vec_back(prog.u.lis);		/* O1 */
	exeterm(env, list.u.lis);
    } else {
	list = vec_at(prog.u.lis, 1);		/* O2 */
	exeterm(env, list.u.lis);
	vec_push(env->stck, prog);		/* push [[O1] [O2] C] */
	vec_init(temp.u.lis);			/* [] */
	temp.op = LIST_;
	node.u.proc = treegenrec;		/* treegenrec */
	node.op = ANON_FUNCT_;
	vec_push(temp.u.lis, node);		/* [treegenrec] */
	vec_push(env->stck, temp);		/* push on stack */
	cons_(env);				/* build aggregate */
	vec_shallow_copy(list.u.lis, prog.u.lis);
	(void)vec_pop(list.u.lis);		/* remove [O1] */
	(void)vec_pop(list.u.lis);		/* remove [O2] */
	exeterm(env, list.u.lis);		/* C */
    }
}

void treegenrec_(pEnv env)
{						/* T [O1] [O2] [C] */
    PARM(4, IFTE);
    cons_(env);
    cons_(env);
    treegenrec(env);
}
#endif
