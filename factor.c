/*
    module  : factor.c
    version : 1.5
    date    : 06/22/22
*/
#include "joy.h"

/*
    readfactor - read a factor from stdin and push it on the stack.

    yylex: USR_, BOOLEAN_, CHAR_, INTEGER_, STRING_, FLOAT_
*/
void readfactor(int sym)
{
    uint64_t set = 0;

    switch (sym) {
    case '{':
        while ((sym = yylex()) != '}')
            if ((sym != CHAR_ && sym != INTEGER_) || yylval.num < 0
                || yylval.num >= SETSIZE_)
                yyerror("small numeric expected in set");
            else
                set |= (int64_t)1 << yylval.num;
        do_push(MAKE_SET(set));
        break;
    case '[':
        readterm(yylex());
        break;
    case INDEX_:
        do_push(MAKE_USR_INDEX(yylval.num));
        break;
    case USR_:
        do_push(qualify(yylval.str));
        break;
    case BOOLEAN_:
        do_push(MAKE_BOOLEAN(yylval.num));
        break;
    case CHAR_:
        do_push(MAKE_CHAR(yylval.num));
        break;
    case INTEGER_:
        do_push(MAKE_INTEGER(yylval.num));
        break;
    case STRING_:
        do_push(MAKE_USR_STRING(yylval.str));
        break;
    case FLOAT_:
        do_push(MAKE_DOUBLE(yylval.dbl));
        break;
    default:
	do_push(MAKE_INTEGER(sym));
	break;
    }
}

/*
    readterm - read a term from stdin and push this on the stack as a list.
*/
void readterm(int sym)
{
    Stack *list;
    value_t value;

    vec_init(list);
    MK_INITIAL(value);
    if (sym != ']') {
        do {
            readfactor(sym);
            vec_push(list, stack_pop());
        } while ((sym = yylex()) != ']');
        vec_push(list, value);
        vec_reverse(list);
    }
    do_push(MAKE_LIST(list));
}
