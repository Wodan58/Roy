/*
    module  : split.c
    version : 1.30
    date    : 09/18/24
*/
#ifndef SPLIT_C
#define SPLIT_C

/**
OK  2840  split  :  DDAA  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
void split_(pEnv env)
{
    int i, j, k, l;
    char *volatile ptr;
    Node list, aggr, node, temp, test, rest;

    PARM(2, STEP);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    rest = temp = aggr;
    switch (aggr.op) {
    case LIST_:
	vec_init(temp.u.lis);
	vec_init(rest.u.lis);
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
	    else
		vec_push(rest.u.lis, node);
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
	    vec_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    test = vec_pop(env->stck);
	    if (test.u.num)
		temp.u.str[k++] = node.u.num;
	    else
		rest.u.str[l++] = node.u.num;
	}
	rest.u.str[l] = temp.u.str[k] = 0;
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
		vec_push(env->stck, node);
		exeterm(env, list.u.lis);
		test = vec_pop(env->stck);
		if (test.u.num)
		    temp.u.set |= (uint64_t)1 << i;
		else
		    rest.u.set |= (uint64_t)1 << i;
	    }
	break;

    default:
	break;
    }
    vec_push(env->stck, temp);
    vec_push(env->stck, rest);
}
#endif
