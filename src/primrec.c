/*
    module  : primrec.c
    version : 1.15
    date    : 09/19/23
*/
#ifndef PRIMREC_C
#define PRIMREC_C

/**
OK 2820  primrec  :  DDDA	X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
void primrec_(pEnv env)
{
    char *str;
    int64_t i, j, num = 0;
    Node first, second, third, node;

    PARM(3, PRIMREC);
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    switch (first.op) {
    case LIST_:
	for (i = lst_size(first.u.lis) - 1; i >= 0; i--) {
	    node = lst_at(first.u.lis, i);
	    lst_push(env->stck, node);
	    num++;
	}
	break;
 
    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.op = CHAR_;
	for (str = first.u.str; *str; str++) {
	    node.u.num = *str;
	    lst_push(env->stck, node);
	    num++;
	}
	break;

    case SET_:
	node.op = INTEGER_;
	for (i = 0, j = 1; i < SETSIZE; i++, j <<= 1)
	    if (first.u.set & j) {
		node.u.num = i;
		lst_push(env->stck, node);
		num++;
	    }
	break;
 
    case INTEGER_:
	node.op = INTEGER_;
	for (i = first.u.num; i > 0; i--) {
	    node.u.num = i;
	    lst_push(env->stck, node);
	    num++;
	}
	break;

    default:
	break;
    }
    exeterm(env, second.u.lis);
    for (i = 0; i < num; i++)
	exeterm(env, third.u.lis);
}
#endif
