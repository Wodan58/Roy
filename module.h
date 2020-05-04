/*
    module  : module.h
    version : 1.2
    date    : 01/19/20
*/
void initmod(char *str);
void initpriv(void);
void stoppriv(void);
void exitpriv(void);
void exitmod(void);
char *iterate(char *name);
char *classify(char *name);
char *qualify(char *name);
