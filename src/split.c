/*
    module  : split.c
    version : 1.29
    date    : 10/12/23
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
    char *volatile ptr;
    Node list, aggr, node, temp, test, rest;

    PARM(2, STEP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &aggr);
    rest = temp = aggr;
    switch (aggr.op) {
    case LIST_:
	temp.u.lis = pvec_init();
	rest.u.lis = pvec_init();
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
	    else
		rest.u.lis = pvec_add(rest.u.lis, node);
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	ptr = aggr.u.str;
	temp.u.str = GC_strdup(ptr);
	rest.u.str = GC_strdup(ptr);
	node.op = CHAR_;
	for (l = k = i = 0, j = strlen(ptr); i < j; i++) {
	    /*
		push the element to be filtered
	    */
	    node.u.num = ptr[i];
	    env->stck = pvec_add(env->stck, node);
	    exeterm(env, list.u.lis);
	    env->stck = pvec_pop(env->stck, &test);
	    if (test.u.num)
		temp.u.str[k++] = node.u.num;
	    else
		rest.u.str[l++] = node.u.num;
	}
	rest.u.str[l] = temp.u.str[k] = 0;
	env->stck = pvec_push(env->stck, temp);
	env->stck = pvec_push(env->stck, rest);
	break;

    case SET_:
	rest.u.set = temp.u.set = 0;
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
		else
		    rest.u.set |= (uint64_t)1 << i;
	    }
	break;

    default:
	break;
    }
    env->stck = pvec_add(env->stck, temp);
    env->stck = pvec_add(env->stck, rest);
}
#endif
