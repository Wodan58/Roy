/*
    module  : node.h
    version : 1.2
    date    : 05/13/17
*/
#include "vector.h"

#ifdef BIT_32
typedef long long_t;
#define PRINT_NUM	"%ld"
#define NUM_MAX		INT_MAX
#endif

#ifdef BIT_64
typedef long long long_t;
#define PRINT_NUM	"%lld"
#define NUM_MAX		LONG_MAX
#endif

/* linked list */
typedef struct node_t {
    union {
	int num;
	char *str;
	struct node_t *ptr;
	void (*fun)(void);
    };
    short type, index;

    struct node_t *next;
    short uniq, mark, recur;
} node_t;

/* array */
typedef struct value_t {
    union {
	int num;
	char *str;
	struct node_t *ptr;
	void (*fun)(void);
    };
    short type, index;
} value_t;

extern int compiling, definition, debugging;

/* declare vector type */
typedef vector(node_t) Table;

/* declare symbol table */
extern Table *theTable;

/* declare vector type */
typedef vector(value_t) Stack;

/* declare data stack */
extern Stack *theStack;

/* declare vector type */
typedef vector(char) String;

/* lexer.l, parse.y */
int yylex(), yyparse(), yyerror(char *str);

/* node.c */
void enterdef(char *str, node_t *next);
node_t *entersym(char *str);
node_t *newlist(node_t *ptr);
node_t *newnode(int type, int value);
node_t *concat(node_t *node, node_t *next);
node_t *copy(node_t *node);
node_t *cons(value_t *node, node_t *next);
node_t *stk2lst();
void lst2stk(node_t *root);
node_t *reverse(node_t *cur);
void writefactor(value_t *cur);
void writeterm(node_t *cur);
void dump();
void debug(node_t *cur);
void binrec(node_t *first, node_t *second, node_t *third, node_t *fourth);
void exeterm(node_t *cur);
void writestack();
void execute(node_t *cur);

/* eval.c */
void compile(node_t *cur);

/* memory.c */
node_t *mem_alloc();
void mem_free();
