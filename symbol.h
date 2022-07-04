/*
    module  : symbol.h
    version : 1.5
    date    : 06/21/22
*/
#ifndef SYMBOL_H
#define SYMBOL_H

int symtabmax(void);
int symtabindex(void);
void set_inuse(const char *str);
value_t locate(int location);
const char *str_locate(int location);
int get_location(const char *name);
value_t lookup(const char *str, int *found);
int is_builtin(const char *str);
void enter(char *str, char *arity, void (*proc)(void));
void initsym(void);
void enterdef(char *Name, Stack *List);
void dump(int mode);
const char *find(void (*proc)(void));
const char *get_arity(void (*proc)(void));
const char *dump_help(int start, long *k);
void dump_table(void);
#endif
