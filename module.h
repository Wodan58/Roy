/*
    module  : module.h
    version : 1.3
    date    : 11/30/20
*/
#ifndef MODULE_H
#define MODULE_H

void initmod(char *str);
void initpriv(void);
void stoppriv(void);
void exitpriv(void);
void exitmod(void);
char *iterate(char *name);
char *classify(char *name);
char *qualify(char *name);
#endif
