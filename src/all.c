/*
    module  : all.c
    version : 1.12
    date    : 09/19/23
*/
#ifndef ALL_C
#define ALL_C

/**
OK 2860  all  :  DDA	A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
void all_(pEnv env)
{
    Node aggr, list, node;
    int64_t i, j, result = 1;	/* assume true */

    PARM(2, STEP);
    list = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	for (i = lst_size(aggr.u.lis) - 1; i >= 0; i--) {
	    /*
		push the element to be tested
	    */
	    node = lst_at(aggr.u.lis, i);
	    lst_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    node = lst_pop(env->stck);
	    if (node.u.num != result) {
		result = 0;
		break;
	    }
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.op = CHAR_;
	for (i = 0, j = strlen(aggr.u.str); i < j; i++) {
	    /*
		push the element to be tested
	    */
	    node.u.num = aggr.u.str[i];
	    lst_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    node = lst_pop(env->stck);
	    if (node.u.num != result) {
		result = 0;
		break;
	    }
	}
	break;

    case SET_:
	node.op = INTEGER_;
	for (i = 0, j = 1; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		/*
		    push the element to be tested
		*/
		node.u.num = i;
		lst_push(env->stck, node);
		exeterm(env, list.u.lis);
		node = lst_pop(env->stck);
		if (node.u.num != result) {
		    result = 0;
		    break;
		}
	    }
	break;

    default:
	break;
    }
    node.u.num = result;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
