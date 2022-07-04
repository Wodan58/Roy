/*
    module  : null.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef NULL_C
#define NULL_C

/**
2210  null  :  DA	X  ->  B
Tests for empty aggregate X or zero numeric.
*/
void do_null(void)
{
    Stack *list;
    const char *str;

    ONEPARAM;
    switch (get_type(stack[-1])) {
#ifdef COMPILING
    case INDEX_:
        str = str_locate(GET_AS_USR_INDEX(stack[-1]));
        stack[-1] = MAKE_BOOLEAN(!*str);
        break;
#endif
    case ANON_FUNCT_:
        stack[-1] = MAKE_BOOLEAN(!GET_AS_ANON_FUNCT(stack[-1]));
        break;
    case BOOLEAN_:
        stack[-1] = MAKE_BOOLEAN(!GET_AS_BOOLEAN(stack[-1]));
        break;
    case CHAR_:
        stack[-1] = MAKE_BOOLEAN(!GET_AS_CHAR(stack[-1]));
        break;
    case INTEGER_:
        stack[-1] = MAKE_BOOLEAN(!GET_AS_INTEGER(stack[-1]));
        break;
    case SET_:
        stack[-1] = MAKE_BOOLEAN(!GET_AS_SET(stack[-1]));
        break;
#ifdef COMPILING
    case USR_:
#endif
    case STRING_:
        str = get_string(stack[-1]);
        stack[-1] = MAKE_BOOLEAN(!*str);
        break;
    case LIST_:
        list = (Stack *)GET_AS_LIST(stack[-1]);
        stack[-1] = MAKE_BOOLEAN(!vec_size(list));
        break;
    case FLOAT_:
        stack[-1] = MAKE_BOOLEAN(!GET_AS_DOUBLE(stack[-1]));
        break;
    case FILE_:
        stack[-1] = MAKE_BOOLEAN(!GET_AS_FILE(stack[-1]));
        break;
    }
}
#endif
