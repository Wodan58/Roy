/*
    module  : name.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef NAME_C
#define NAME_C

/**
2180  name  :  DA	sym  ->  "sym"
For operators and combinators, the string "sym" is the name of item sym,
for literals sym the result string is its type.
*/
void do_name(void)
{
    int type;
    const char *str = "";

    ONEPARAM;
    type = get_type(stack[-1]);
    switch (type) {
#ifdef COMPILING
    case INDEX_:
        str = str_locate(GET_AS_USR_INDEX(stack[-1]));
        break;
    case USR_:
        str = GET_AS_USR_STRING(stack[-1]);
        break;
#endif
    case ANON_FUNCT_:
        str = find(GET_AS_ANON_FUNCT(stack[-1]));
        break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case SET_:
    case STRING_:
    case LIST_:
    case FLOAT_:
    case FILE_:
        str = optable[type].name;
        break;
    }
    stack[-1] = MAKE_USR_STRING(stringify(str));
}
#endif
