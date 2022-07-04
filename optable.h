/*
    module  : optable.h
    version : 1.1
    date    : 06/21/22
*/
#ifndef OPTABLE_H
#define OPTABLE_H

typedef struct optable_t {
    char *name;
    void (*proc)(void);
    char *arity, *messg1, *messg2;
} optable_t;

/* optable.c */
extern optable_t optable[];

char *opername(int o);
void (*operproc(int o))(void);
char *opertype(int o);
#endif
