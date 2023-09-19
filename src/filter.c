/*
    module  : filter.c
    version : 1.26
    date    : 09/19/23
*/
#ifndef FILTER_C
#define FILTER_C

/**
OK 2830  filter  :  DDA	A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
void filter_(pEnv env)
{
    int64_t i, j, k;
    Node list, aggr, node, temp, test;

    PARM(2, STEP);
    list = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    temp.op = aggr.op;
    switch (aggr.op) {
    case LIST_:
	lst_init(temp.u.lis);
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
	}
	lst_push(env->stck, temp);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	temp.u.str = GC_strdup(aggr.u.str);
	node.op = CHAR_;
	for (k = i = 0, j = strlen(aggr.u.str); i < j; i++) {
	    /*
		push the element to be filtered
	    */
	    node.u.num = aggr.u.str[i];
	    lst_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    test = lst_pop(env->stck);
	    if (test.u.num)
		temp.u.str[k++] = node.u.num;
	}
	temp.u.str[k] = 0;
	lst_push(env->stck, temp);
	break;

    case SET_:
	temp.u.set = 0;
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
	    }
	lst_push(env->stck, temp);
	break;

    default:
	break;
    }
}
#endif
