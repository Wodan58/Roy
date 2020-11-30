/*
    module  : symbol.h
    version : 1.2
    date    : 11/30/20
*/
#ifndef SYMBOL_H
#define SYMBOL_H

int symtabmax(void);
int symtabindex(void);
int inuse(const char *str);
intptr_t lookup(const char *str);
void enter(char *str, void (*proc)(void));
void initsym(void);
void enterdef(char *Name, Stack *List);
char *strupr(const char *str);
void dump(void);
const char *dump1(int start, khiter_t *key);
const char *dump2(int start, khiter_t *key);
#endif
