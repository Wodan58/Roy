/*
    module  : some.c
    version : 1.14
    date    : 09/18/24
*/
#ifndef SOME_C
#define SOME_C

/**
OK  2850  some  :  DDA  A [B]  ->  X
Applies test B to members of aggregate A, X = true if some pass.
*/
void some_(pEnv env)
{
    Node list, aggr, node;
    int64_t i, j, result = 0;	/* assume false */

    PARM(2, STEP);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	for (i = 0, j = vec_size(aggr.u.lis); i < j; i++) {
	    /*
		push the element to be tested
	    */
	    node = vec_at(aggr.u.lis, i);
	    vec_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    node = vec_pop(env->stck);
	    if (node.u.num) {
		result = 1;
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
	    vec_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    node = vec_pop(env->stck);
	    if (node.u.num) {
		result = 1;
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
		vec_push(env->stck, node);
		exeterm(env, list.u.lis);
		node = vec_pop(env->stck);
		if (node.u.num) {
		    result = 1;
		    break;
		}
	    }
	break;

    default:
	break;
    }
    node.u.num = result;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
