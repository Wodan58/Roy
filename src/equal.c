/*
    module  : equal.c
    version : 1.12
    date    : 11/20/24
*/
#ifndef EQUAL_C
#define EQUAL_C

#include "compare.h"

/**
Q0  OK  2280  equal  :  DDA  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
int compatible(int first, int second)
{
    switch (first) {
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case SET_:
    case FLOAT_:
	switch (second) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case FLOAT_:
	case BIGNUM_:
	    return 1;

	default:
	    return 0;
	}
	break;

    case USR_:
    case ANON_FUNCT_:
    case STRING_:
    case USR_STRING_:
	switch (second) {
	case USR_:
	case ANON_FUNCT_:
	case STRING_:
	case BIGNUM_:
	case USR_STRING_:
	    return 1;

	default:
	    return 0;
	}
	break;

#ifdef USE_BIGNUM_ARITHMETIC
    case BIGNUM_:
	switch (second) {
	case USR_:
	case ANON_FUNCT_:
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case STRING_:
	case FLOAT_:
	case BIGNUM_:
	case USR_STRING_:
	    return 1;

	default:
	    return 0;
	}
	break;
#endif
    }
    return first == second;
}

int is_equal(pEnv env, Node first, Node second)
{
    int i, size;
    vector(Node) *stackf = 0, *stacks = 0;

    if (!compatible(first.op, second.op))
	return 0;		/* unequal */
    if (first.op != LIST_)
	return Compare(env, first, second) == 0;
    if ((size = vec_size(first.u.lis)) != vec_size(second.u.lis))
	return 0;		/* unequal */
    if (size) {
	vec_init(stackf);	/* collect nodes in a vector */
	vec_init(stacks);
    }
    for (i = 0; i < size; i++) {
	vec_push(stackf, vec_at(first.u.lis, i));
	vec_push(stacks, vec_at(second.u.lis, i));
    }
    while (vec_size(stackf)) {
	first = vec_pop(stackf);
	second = vec_pop(stacks);
	if (!compatible(first.op, second.op))
	    return 0;		/* unequal */
	if (first.op != LIST_) {
	    if (Compare(env, first, second))
		return 0;	/* unequal */
	} else {
	    if ((size = vec_size(first.u.lis)) != vec_size(second.u.lis))
		return 0;	/* unequal */
	    for (i = 0; i < size; i++) {
		vec_push(stackf, vec_at(first.u.lis, i));
		vec_push(stacks, vec_at(second.u.lis, i));
	    }	    
	}
    }
    return 1;			/* equal */
}

void equal_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first.u.num = is_equal(env, first, second);
    first.op = BOOLEAN_;
    vec_push(env->stck, first);
}
#endif
