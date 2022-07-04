/*
    module  : intern.c
    version : 1.15
    date    : 06/21/22
*/
#ifndef INTERN_C
#define INTERN_C

/**
2190  intern  :  DA	"sym"  ->  sym
Pushes the item whose name is "sym".
*/
void do_intern(void)
{
    char *str, *ptr;

    ONEPARAM;
    STRING;
    ptr = str = get_string(stack[-1]);
    if (!strchr("\"#'().0123456789;[]{}", *ptr)) {
        if (*ptr == '-' && isdigit((int)ptr[1]))
            ;
        else
            for (ptr++; *ptr; ptr++)
                if (!isalnum((int)*ptr) && !strchr("-=_", *ptr))
                    break;
    }
    CHECKNAME(ptr);
    stack[-1] = qualify(GC_strdup(str));
}
#endif
