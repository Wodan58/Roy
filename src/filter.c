/*
    module  : filter.c
    version : 1.27
    date    : 10/02/23
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
    char *volatile ptr;
    Node list, aggr, node, temp, test;

    PARM(2, STEP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &aggr);
    temp = aggr;
    switch (aggr.op) {
    case LIST_:
	temp.u.lis = pvec_init();
	for (i = 0, j = pvec_cnt(aggr.u.lis); i < j; i++) {
	    /*
		push the element to be filtered
	    */
	    node = pvec_nth(aggr.u.lis, i);
	    env->stck = pvec_add(env->stck, node);
	    exeterm(env, list.u.lis);
	    env->stck = pvec_pop(env->stck, &test);
	    if (test.u.num)
		temp.u.lis = pvec_add(temp.u.lis, node);
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	temp.u.str = GC_strdup(aggr.u.str);
	node.op = CHAR_;
	ptr = aggr.u.str;
	for (k = i = 0, j = strlen(aggr.u.str); i < j; i++) {
	    /*
		push the element to be filtered
	    */
	    node.u.num = aggr.u.str[i];
	    env->stck = pvec_add(env->stck, node);
	    exeterm(env, list.u.lis);
	    env->stck = pvec_pop(env->stck, &test);
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
		env->stck = pvec_add(env->stck, node);
		exeterm(env, list.u.lis);
		env->stck = pvec_pop(env->stck, &test);
		if (test.u.num)
		    temp.u.set |= (uint64_t)1 << i;
	    }
	break;

    default:
	break;
    }
    env->stck = pvec_add(env->stck, temp);
}
#endif
