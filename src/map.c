/*
    module  : map.c
    version : 1.28
    date    : 10/02/23
*/
#ifndef MAP_C
#define MAP_C

/**
OK 2790  map  :  DDA	A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
void map_(pEnv env)
{
    int64_t i, j;
    char *volatile ptr;
    Node list, aggr, node, temp;

    PARM(2, STEP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &aggr);
    temp = aggr;
    switch (aggr.op) {
    case LIST_:
	temp.u.lis = pvec_init();
	for (i = 0, j = pvec_cnt(aggr.u.lis); i < j; i++) {
	    /*
		push the element to be mapped
	    */
	    node = pvec_nth(aggr.u.lis, i);
	    env->stck = pvec_add(env->stck, node);
	    exeterm(env, list.u.lis);
	    env->stck = pvec_pop(env->stck, &node);
	    temp.u.lis = pvec_add(temp.u.lis, node);
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	temp.u.str = GC_strdup(aggr.u.str);
	node.op = CHAR_;
	ptr = aggr.u.str;
	for (i = 0, j = strlen(aggr.u.str); i < j; i++) {
	    /*
		push the element to be mapped
	    */
	    node.u.num = aggr.u.str[i];
	    env->stck = pvec_add(env->stck, node);
	    exeterm(env, list.u.lis);
	    env->stck = pvec_pop(env->stck, &node);
	    temp.u.str[i] = node.u.num;
	}
	break;

    case SET_:
	temp.u.set = 0;
	node.op = INTEGER_;
	for (j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		/*
		    push the element to be mapped
		*/
		node.u.num = i;
		env->stck = pvec_add(env->stck, node);
		exeterm(env, list.u.lis);
		env->stck = pvec_pop(env->stck, &node);
		temp.u.set |= (uint64_t)1 << node.u.num;
	    }
	lst_push(env->stck, temp);
	break;

    default:
	break;
    }
    env->stck = pvec_add(env->stck, temp);
}
#endif
