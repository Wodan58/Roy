/*
    module  : getenv.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef GETENV_C
#define GETENV_C

/**
3050  getenv  :  DA	"variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
void do_getenv(void)
{
    char *str;

    COMPILE;
    ONEPARAM;
    STRING;
    str = getenv(get_string(stack[-1]));
    stack[-1] = MAKE_USR_STRING(stringify(str));
}
#endif
