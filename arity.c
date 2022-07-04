/*
    module  : arity.c
    version : 1.1
    date    : 06/21/22
*/
#include "joy.h"

/*
    Check the arity of a quotation. Parameter num is the initial value.
    The desired outcome is 1. In case of an error -1 is returned.
    The rules are that num cannot become negative and that unknown effects are
    handled by returning -1. Unknown only means that it is considered too
    difficult to try to figure out what the stack effect is.
*/
int arity(Stack *quot, int num)
{
    Stack *list;
    value_t value;
    const char *str;
    int i, type, found;
    void (*proc)(void);

    for (i = vec_size(quot) - 1; i >= 0; i--) {
        value = vec_at(quot, i);
        type = get_type(value);
        switch (type) {
        case INDEX_:
            value = locate(GET_AS_USR_INDEX(value));
            if (IS_LIST(value)) {
                list = (Stack *)GET_AS_LIST(value);
                if ((num = arity(list, num)) < 0)
                    return -1;
            }
            break;
        case USR_:
            str = GET_AS_USR_STRING(value);
            value = lookup(str, &found);
            if (found && IS_LIST(value)) {
                list = (Stack *)GET_AS_LIST(value);
                if ((num = arity(list, num)) < 0)
                    return -1;
            }
            break;
        case ANON_FUNCT_:
            proc = GET_AS_ANON_FUNCT(value);
            str = get_arity(proc);
            for (; *str; str++)
                if (*str == 'A') /* add */
                    ++num;
                else if (*str == 'D') { /* delete */
                    if (--num < 0)
                        return -1;
                } else if (*str == 'U') /* unknown */
                    return -1;
            break;
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
        case SET_:
        case STRING_:
        case LIST_:
        case FLOAT_:
        case FILE_:
            ++num;
            break;
        }
    }
    return num;
}
