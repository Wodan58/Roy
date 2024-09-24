/*
    module  : map.c
    version : 1.30
    date    : 09/18/24
*/
#ifndef MAP_C
#define MAP_C

/**
OK  2790  map  :  DDA  A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
void map_(pEnv env)
{
    int64_t i, j;
    char *volatile ptr;
    Node list, aggr, node, temp;

    PARM(2, STEP);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    temp = aggr;
    switch (aggr.op) {
    case LIST_:
	vec_init(temp.u.lis);
	for (i = 0, j = vec_size(aggr.u.lis); i < j; i++) {
	    /*
		push the element to be mapped
	    */
	    node = vec_at(aggr.u.lis, i);
	    vec_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    node = vec_pop(env->stck);
	    vec_push(temp.u.lis, node);
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	ptr = aggr.u.str;
	temp.u.str = GC_strdup(ptr);
	node.op = CHAR_;
	for (i = 0, j = strlen(ptr); i < j; i++) {
	    /*
		push the element to be mapped
	    */
	    node.u.num = ptr[i];
	    vec_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    node = vec_pop(env->stck);
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
		vec_push(env->stck, node);
		exeterm(env, list.u.lis);
		node = vec_pop(env->stck);
		temp.u.set |= (uint64_t)1 << node.u.num;
	    }
	vec_push(env->stck, temp);
	break;

    default:
	break;
    }
    vec_push(env->stck, temp);
}
#endif
