/*
    module  : helpdetail.c
    version : 1.15
    date    : 01/19/20
*/
#ifndef HELPDETAIL_C
#define HELPDETAIL_C

#ifdef COMPILING
int search(const char *name)
{
    int i;

    for (i = 0; optable[i].name; i++)
	if (!strcmp(name, optable[i].name))
	    return i;
    return 0;
}
#endif

/**
helpdetail  :  [ S1 S2 .. ]  ->
Gives brief help on each symbol S in the list.
*/
void do_helpdetail(void)
{
#ifdef COMPILING
    int i, j;
    Stack *List;
    intptr_t Value;
    const char *Name;

    printf("\n");
    List = (Stack *)do_pop();
    for (i = vec_size(List) - 1; i >= 0; i--) {
	Value = vec_at(List, i);
	if (Value >= 2 && Value < 12)
	    printf("%s  :  %s.\n%s\n", optable[Value].name,
		   optable[Value].messg1, optable[Value].messg2);
	else {
	    if (!Value) {
		Name = "false";
		Value = 1;
	    } else if (Value == 1)
		Name = "true";
	    else {
		Name = (const char *)(Value & ~JLAP_INVALID);
		Value = lookup(Name);
	    }
	    if (Value & JLAP_INVALID) {
		j = search(Name);
		printf("%s  :  %s.\n%s\n", Name, optable[j].messg1,
		       optable[j].messg2);
	    } else {
		printf("%s  ==  ", Name);
		writeterm((Stack *)Value, -1);
		printf("\n");
	    }
	}
    }
#endif
}
#endif
