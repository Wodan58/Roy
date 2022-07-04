/*
    module  : module.h
    version : 1.4
    date    : 06/21/22
*/
#ifndef MODULE_H
#define MODULE_H

void initmod(char *str);
void initpriv(void);
void stoppriv(void);
void exitpriv(void);
void exitmod(void);
char *classify(char *name);
value_t qualify(char *name);
#endif
