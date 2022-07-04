/*
    module  : lookup.h
    version : 1.2
    date    : 06/21/22
*/
#ifndef LOOKUP_H
#define LOOKUP_H

/*
    This file contains some definitions that are needed in compiled programs.
*/
typedef struct table_t {
    void (*proc)(void);
    char *name;
} table_t;

extern table_t yytable[]; /* present in generated code */

value_t lookup(const char *name, int *location);
value_t qualify(char *name);
const char *find(void (*proc)(void));
void dump_table(void);
int arity(Stack *quot, int num);
void print(const char *str);
const char *str_locate(int location);
#endif
