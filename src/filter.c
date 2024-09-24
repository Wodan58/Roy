/*
    module  : filter.c
    version : 1.29
    date    : 09/18/24
*/
#ifndef FILTER_C
#define FILTER_C

/**
OK  2830  filter  :  DDA  A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
void filter_(pEnv env)
{
    int64_t i, j, k;
    char *volatile ptr;
    Node list, aggr, node, temp, test;

    PARM(2, STEP);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    temp = aggr;
    switch (aggr.op) {
    case LIST_:
	vec_init(temp.u.lis);
	for (i = 0, j = vec_size(aggr.u.lis); i < j; i++) {
	    /*
		push the element to be filtered
	    */
	    node = vec_at(aggr.u.lis, i);
	    vec_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    test = vec_pop(env->stck);
	    if (test.u.num)
		vec_push(temp.u.lis, node);
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	ptr = aggr.u.str;
	temp.u.str = GC_strdup(ptr);
	node.op = CHAR_;
	for (k = i = 0, j = strlen(ptr); i < j; i++) {
	    /*
		push the element to be filtered
	    */
	    node.u.num = ptr[i];
	    vec_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    test = vec_pop(env->stck);
	    if (test.u.num)
		temp.u.str[k++] = node.u.num;
	}
	temp.u.str[k] = 0;
	break;

    case SET_:
	temp.u.set = 0;
	node.op = INTEGER_;
	for (j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		/*
		    push the element to be filtered
		*/
		node.u.num = i;
		vec_push(env->stck, node);
		exeterm(env, list.u.lis);
		test = vec_pop(env->stck);
		if (test.u.num)
		    temp.u.set |= (uint64_t)1 << i;
	    }
	break;

    default:
	break;
    }
    vec_push(env->stck, temp);
}
#endif
