/*
    module  : split.c
    version : 1.27
    date    : 09/19/23
*/
#ifndef SPLIT_C
#define SPLIT_C

/**
OK 2840  split  :  DDAA	A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
void split_(pEnv env)
{
    int64_t i, j, k, l;
    Node list, aggr, node, temp, test, rest;

    PARM(2, STEP);
    list = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    rest.op = temp.op = aggr.op;
    switch (aggr.op) {
    case LIST_:
	lst_init(temp.u.lis);
	lst_init(rest.u.lis);
	for (i = 0, j = lst_size(aggr.u.lis); i < j; i++) {
	    /*
		push the element to be filtered
	    */
	    node = lst_at(aggr.u.lis, i);
	    lst_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    test = lst_pop(env->stck);
	    if (test.u.num)
		lst_push(temp.u.lis, node);
	    else
		lst_push(rest.u.lis, node);
	}
	lst_push(env->stck, temp);
	lst_push(env->stck, rest);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	temp.u.str = GC_strdup(aggr.u.str);
	rest.u.str = GC_strdup(aggr.u.str);
	node.op = CHAR_;
	for (l = k = i = 0, j = strlen(aggr.u.str); i < j; i++) {
	    /*
		push the element to be filtered
	    */
	    node.u.num = aggr.u.str[i];
	    lst_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    test = lst_pop(env->stck);
	    if (test.u.num)
		temp.u.str[k++] = node.u.num;
	    else
		rest.u.str[l++] = node.u.num;
	}
	rest.u.str[l] = temp.u.str[k] = 0;
	lst_push(env->stck, temp);
	lst_push(env->stck, rest);
	break;

    case SET_:
	rest.u.set = temp.u.set = 0;
	node.op = INTEGER_;
	for (i = 0, j = 1; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		/*
		    push the element to be filtered
		*/
		node.u.num = i;
		lst_push(env->stck, node);
		exeterm(env, list.u.lis);
		test = lst_pop(env->stck);
		if (test.u.num)
		    temp.u.set |= (uint64_t)1 << i;
		else
		    rest.u.set |= (uint64_t)1 << i;
	    }
	lst_push(env->stck, temp);
	lst_push(env->stck, rest);
	break;

    default:
	break;
    }
}
#endif
