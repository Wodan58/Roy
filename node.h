/*
    module  : node.h
    version : 1.1
    date    : 10/23/16
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
    short type, index, uniq, mark;
    struct node_t *next;
} node_t;

/* array */
typedef struct value_t {
    union {
	int num;
	char *str;
	struct node_t *ptr;
    };
    short type, index;
} value_t;

extern int compiling, definition;

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

int yylex(), yyparse(), yyerror(char *str);

void enterdef(char *str, node_t *next);
node_t *entersym(char *str);
node_t *newlist(node_t *ptr);
node_t *newnode(int type, int value);
node_t *concat(node_t *node, node_t *next);
node_t *copy(node_t *node);
node_t *reverse(node_t *cur);
void writeterm(node_t *cur);
void writefactor(value_t *cur);
void exeterm(node_t *cur);
void writestack();
void debug(node_t *cur);
void compile(node_t *cur);
node_t *cons(value_t *node, node_t *next);
void dump();
node_t *stk2lst();
void lst2stk(node_t *root);
void execute(node_t *cur);
node_t *mem_alloc();
void mem_free();

#ifdef BENCHMARK
void binrec(node_t *first, node_t *second, node_t *third, node_t *fourth);
#endif
