/*
    module  : casting.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef CASTING_C
#define CASTING_C

/**
3170  casting  :  DDA 	X Y  ->  Z
Z takes the value from X and the type from Y.
*/
void do_casting(void)
{
    int type;
    FILE *fp;
    double dbl;
    Stack *list;
    uint64_t value;
    char str[MAXSTR];

    TWOPARAMS;
    type = get_type(stack_pop());
    value = GET_AS_OBJECT(stack[-1]);
    switch (type) {
    case INDEX_:
        stack[-1] = MAKE_USR_INDEX(value);
        break;
    case USR_:
        sprintf(str, "%ld", value);
        stack[-1] = MAKE_USR_STRING(GC_strdup(str));
        break;
    case ANON_FUNCT_:
        stack[-1] = MAKE_ANON_FUNCT(value);
        break;
    case BOOLEAN_:
        stack[-1] = MAKE_BOOLEAN(value);
        break;
    case CHAR_:
        stack[-1] = MAKE_CHAR(value);
        break;
    case INTEGER_:
        stack[-1] = MAKE_INTEGER(value);
        break;
    case SET_:
        stack[-1] = MAKE_SET(value);
        break;
    case STRING_:
        sprintf(str, "%ld", value);
        stack[-1] = MAKE_USR_STRING(stringify(str));
        break;
    case LIST_:
        if (value)
            list = (Stack *)value;
        else
            vec_init(list);
        stack[-1] = MAKE_LIST(list);
        break;
    case FLOAT_:
	memcpy(&dbl, &value, sizeof(dbl));
        stack[-1] = MAKE_DOUBLE(dbl);
        break;
    case FILE_:
        fp = (FILE *)value;
        stack[-1] = MAKE_FILE(fp);
        break;
    }
}
#endif
