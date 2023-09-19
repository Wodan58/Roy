/*
    module  : map.c
    version : 1.27
    date    : 09/19/23
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
    Node aggr, list, node, temp;

    PARM(2, STEP);
    list = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    temp.op = aggr.op;
    switch (aggr.op) {
    case LIST_:
	lst_init(temp.u.lis);
	for (i = 0, j = lst_size(aggr.u.lis); i < j; i++) {
	    /*
		push the element to be mapped
	    */
	    node = lst_at(aggr.u.lis, i);
	    lst_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    node = lst_pop(env->stck);
	    lst_push(temp.u.lis, node);
	}
	lst_push(env->stck, temp);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	temp.u.str = GC_strdup(aggr.u.str);
	node.op = CHAR_;
	for (i = 0, j = strlen(aggr.u.str); i < j; i++) {
	    /*
		push the element to be mapped
	    */
	    node.u.num = aggr.u.str[i];
	    lst_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    node = lst_pop(env->stck);
	    temp.u.str[i] = node.u.num;
	}
	lst_push(env->stck, temp);
	break;

    case SET_:
	temp.u.set = 0;
	node.op = INTEGER_;
	for (i = 0, j = 1; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		/*
		    push the element to be mapped
		*/
		node.u.num = i;
		lst_push(env->stck, node);
		exeterm(env, list.u.lis);
		node = lst_pop(env->stck);
		temp.u.set |= (uint64_t)1 << node.u.num;
	    }
	lst_push(env->stck, temp);
	break;

    default:
	break;
    }
}
#endif
