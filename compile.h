/*
    module  : compile.h
    version : 1.1
    date    : 06/21/22
*/
#ifndef COMPILE_H
#define COMPILE_H

extern FILE *program;

int FindNode(Stack *node);
void printstack(void);
void initcompile(void);
void printvalue(value_t value);
void print(const char *str);
void compile_rest(Stack *list, int i);
void compile(Stack *list);
void compile_cond(Stack *list, int start);
#endif
