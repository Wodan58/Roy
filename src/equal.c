/*
    module  : equal.c
    version : 1.14
    date    : 06/23/20
*/
#ifndef EQUAL_C
#define EQUAL_C

int get_type(intptr_t temp);	/* print.c */

int is_equal_list(Stack *first, Stack *second);

int is_equal_item(intptr_t first, intptr_t second)
{
    int type1, type2;
    real_t dbl1, dbl2;
    char *name1, *name2;

    type1 = get_type(first);
    type2 = get_type(second);
    switch (type1) {
    case USR_:
	name1 = (char *)first;
	switch (type2) {
	case USR_:
	    name2 = (char *)second;
	    return !strcmp(name1, name2);
	case ANON_FUNCT_:
	    if ((name2 = procname(second)) == 0)
		name2 = (char *)second;
	    return !strcmp(name1, name2);
	case STRING_:
	    name2 = (char *)(second & ~JLAP_INVALID);
	    return !strcmp(name1, name2);
	default:
	    break;
	}
	break;
    case ANON_FUNCT_:
	if ((name1 = procname(first)) == 0)
	    name1 = (char *)first;
	switch (type2) {
	case USR_:
	    name2 = (char *)second;
	    return !strcmp(name1, name2);
	case ANON_FUNCT_:
	    if ((name2 = procname(second)) == 0)
		name2 = (char *)second;
	    return !strcmp(name1, name2);
	case STRING_:
	    name2 = (char *)(second & ~JLAP_INVALID);
	    return !strcmp(name1, name2);
	default:
	    break;
	}
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case SET_:
	switch (type2) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    return first == second;
	case FLOAT_:
	    dbl2 = unpack(second);
	    return first == dbl2;
	    break;
	default:
	    break;
	}
	break;
    case STRING_:
	name1 = (char *)(first & ~JLAP_INVALID);
	switch (type2) {
	case USR_:
	    name2 = (char *)second;
	    return !strcmp(name1, name2);
	case ANON_FUNCT_:
	    if ((name2 = procname(second)) == 0)
		name2 = (char *)second;
	    return !strcmp(name1, name2);
	case STRING_:
	    name2 = (char *)(second & ~JLAP_INVALID);
	    return !strcmp(name1, name2);
	default:
	    break;
	}
	break;
    case LIST_:
	switch (type2) {
	case LIST_:
	    return is_equal_list((Stack *)first, (Stack *)second);
	default:
	    break;
	}
	break;
    case FLOAT_:
	dbl1 = unpack(first);
	switch (type2) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    return dbl1 == second;
	case FLOAT_:
	    dbl2 = unpack(second);
	    return dbl1 == dbl2;
	default:
	    break;
	}
	break;
    case FILE_:
	switch (type2) {
	case FILE_:
	    return first == second;
	default:
	    break;
	}
	break;
    default:
	return first == second;
	break;
    }
    return 0;
}

int is_equal_list(Stack *first, Stack *second)
{
    int i;
    intptr_t First, Second;

    if ((i = vec_size(first)) != vec_size(second))
	return 0;
    for (--i; i >= 0; i--) {
	First = vec_at(first, i);
	Second = vec_at(second, i);
	if (!is_equal_item(First, Second))
	    return 0;
    }
    return 1;
}

/**
equal  :  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
void do_equal(void)
{
    intptr_t first, second;

    BINARY;
    second = do_pop();
    first = stack[-1];
    stack[-1] = is_equal_item(first, second);
}
#endif
