/*
    module  : compare.c
    version : 1.1
    date    : 06/21/22
*/
#include "joy.h"

static const char *nickname(const char *str)
{
    if (isalnum((int)*str) || *str == '_')
	return str;
    switch (*str) {
    case '+' :
	return "plus";
    case '-' :
	return "minus";
    case '*' :
	return "ast";
    case '/' :
	return "divide";
    case '>' :
	if (str[1] == '=')
	    return "geql";
	return "greater";
    case '<' :
	if (str[1] == '=')
	    return "leql";
	return "less";
    case '!' :
	return "neql";
    case '=' :
	return "equals";
    }
    return str;
}

/*
    BOOLEAN, CHAR, INTEGER, FLOAT are lumped together allowing numerical
    compare; INDEX, USR, STRING, ANON_FUNCT are lumped together allowing string
    compare; SET can only be compared with SET; FILE can only be compared with
    FILE; LIST cannot be compared with anything.
*/
int Compare(value_t first, value_t second)
{
    FILE *fp1, *fp2;
    int type1, type2;
    double dbl, dbl1, dbl2;
    int64_t num, num1, num2;
    const char *name1, *name2;

    type1 = get_type(first);
    type2 = get_type(second);
    switch (type1) {
    case INDEX_:
        name1 = nickname(str_locate(GET_AS_USR_INDEX(first)));
        switch (type2) {
        case INDEX_:
            name2 = nickname(str_locate(GET_AS_USR_INDEX(second)));
            goto cmpstr;
        case USR_:
        case STRING_:
            name2 = get_string(second);
            goto cmpstr;
        case ANON_FUNCT_:
            name2 = nickname(find(GET_AS_ANON_FUNCT(second)));
            goto cmpstr;
        default:
            return 1; /* unequal */
        }
        break;
    case USR_:
    case STRING_:
        name1 = get_string(first);
        switch (type2) {
        case INDEX_:
            name2 = nickname(str_locate(GET_AS_USR_INDEX(second)));
            goto cmpstr;
        case USR_:
        case STRING_:
            name2 = get_string(second);
            goto cmpstr;
        case ANON_FUNCT_:
            name2 = nickname(find(GET_AS_ANON_FUNCT(second)));
            goto cmpstr;
        default:
            return 1; /* unequal */
        }
        break;
    case ANON_FUNCT_:
        name1 = nickname(find(GET_AS_ANON_FUNCT(first)));
        switch (type2) {
        case INDEX_:
            name2 = nickname(str_locate(GET_AS_USR_INDEX(second)));
            goto cmpstr;
        case USR_:
        case STRING_:
            name2 = get_string(second);
            goto cmpstr;
        case ANON_FUNCT_:
            name2 = nickname(find(GET_AS_ANON_FUNCT(second)));
            goto cmpstr;
        default:
            return 1; /* unequal */
        }
        break;
    case BOOLEAN_:
        num1 = GET_AS_BOOLEAN(first);
        switch (type2) {
        case BOOLEAN_:
            num2 = GET_AS_BOOLEAN(second);
            goto cmpnum;
        case CHAR_:
            num2 = GET_AS_CHAR(second);
            goto cmpnum;
        case INTEGER_:
            num2 = GET_AS_INTEGER(second);
            goto cmpnum;
        case FLOAT_:
            dbl1 = num1;
            dbl2 = GET_AS_DOUBLE(second);
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case CHAR_:
        num1 = GET_AS_CHAR(first);
        switch (type2) {
        case BOOLEAN_:
            num2 = GET_AS_BOOLEAN(second);
            goto cmpnum;
        case CHAR_:
            num2 = GET_AS_CHAR(second);
            goto cmpnum;
        case INTEGER_:
            num2 = GET_AS_INTEGER(second);
            goto cmpnum;
        case FLOAT_:
            dbl1 = num1;
            dbl2 = GET_AS_DOUBLE(second);
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case INTEGER_:
        num1 = GET_AS_INTEGER(first);
        switch (type2) {
        case BOOLEAN_:
            num2 = GET_AS_BOOLEAN(second);
            goto cmpnum;
        case CHAR_:
            num2 = GET_AS_CHAR(second);
            goto cmpnum;
        case INTEGER_:
            num2 = GET_AS_INTEGER(second);
            goto cmpnum;
        case FLOAT_:
            dbl1 = num1;
            dbl2 = GET_AS_DOUBLE(second);
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case SET_:
        num1 = GET_AS_SET(first);
        switch (type2) {
        case SET_:
            num2 = GET_AS_SET(second);
            goto cmpnum;
        default:
            return 1; /* unequal */
        }
        break;
    case LIST_:
        return 1; /* unequal */
        break;
    case FLOAT_:
        dbl1 = GET_AS_DOUBLE(first);
        switch (type2) {
        case BOOLEAN_:
            dbl2 = GET_AS_BOOLEAN(second);
            goto cmpdbl;
        case CHAR_:
            dbl2 = GET_AS_CHAR(second);
            goto cmpdbl;
        case INTEGER_:
            dbl2 = GET_AS_INTEGER(second);
            goto cmpdbl;
        case FLOAT_:
            dbl2 = GET_AS_DOUBLE(second);
            goto cmpdbl;
        default:
            return 1; /* unequal */
        }
        break;
    case FILE_:
        fp1 = GET_AS_FILE(first);
        switch (type2) {
        case FILE_:
            fp2 = GET_AS_FILE(second);
            return fp1 - fp2 < 0 ? -1 : fp1 - fp2 > 0;
        default:
            return 1; /* unequal */
        }
        break;
    default:
        num1 = GET_AS_OBJECT(first);
        num2 = GET_AS_OBJECT(second);
        goto cmpnum;
    }
cmpdbl:
    dbl = dbl1 - dbl2;
    return dbl < 0 ? -1 : dbl > 0;
cmpstr:
    num = strcmp(name1, name2);
    return num < 0 ? -1 : num > 0;
cmpnum:
    num = num1 - num2;
    return num < 0 ? -1 : num > 0;
}
