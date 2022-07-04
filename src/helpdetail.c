/*
    module  : helpdetail.c
    version : 1.16
    date    : 06/21/22
*/
#ifndef HELPDETAIL_C
#define HELPDETAIL_C

/**
2940  helpdetail  :  D	[ S1 S2 .. ]  ->
Gives brief help on each symbol S in the list.
*/
#ifdef COMPILING
int search(const char *name)
{
    int i;

    for (i = 0; optable[i].name; i++)
        if (!strcmp(name, optable[i].name))
            return i;
    return 0;
}

void printline(int i)
{
    printf("%s  :  %s.\n%s\n", optable[i].name, optable[i].messg1,
        optable[i].messg2);
}
#endif

void do_helpdetail(void)
{
#ifdef COMPILING
    Stack *list;
    value_t temp;
    const char *name;
    int i, j, type, found;

    COMPILE;
    ONEPARAM;
    LIST;
    list = (Stack *)GET_AS_LIST(stack_pop());
    for (printf("\n"), i = vec_size(list) - 1; i >= 0; i--) {
        temp = vec_at(list, i);
        switch (type = get_type(temp)) {
        case INDEX_:
            name = str_locate(GET_AS_USR_INDEX(temp));
            temp = locate(GET_AS_USR_INDEX(temp));
            if (IS_LIST(temp)) {
                printf("%s  ==  \n    ", name);
                writeterm((Stack *)GET_AS_LIST(temp), -1);
                printf("\n\n");
            }
            break;
        case USR_:
            name = get_string(temp);
	    if ((j = search(name)) == 0)
                printf("%s  ==  \n    \n\n", name);
	    else
		printline(j);
            break;
        case ANON_FUNCT_:
            printline(search(find(GET_AS_ANON_FUNCT(temp))));
            break;
        case BOOLEAN_:
            printline(search(GET_AS_BOOLEAN(temp) ? "true" : "false"));
            break;
        case INTEGER_:
            if (GET_AS_INTEGER(temp) == MAXINT_) {
                printline(search("maxint"));
                break;
            }
            printline(type);
            break;
        case CHAR_:
        case SET_:
        case LIST_:
        case STRING_:
        case FLOAT_:
        case FILE_:
            printline(type);
            break;
        }
    }
#endif
}
#endif
