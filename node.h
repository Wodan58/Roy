/*
    module  : node.h
    version : 1.2
    date    : 09/02/16
*/
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

typedef struct stack_t {
    union {
	int num;
	char *str;
	struct node_t *ptr;
    };
    short type, index;
} stack_t;

extern int compiling, definition;

extern int symptr;
extern node_t symtab[];

#ifdef _MSC_VER
extern int stkptr;
#else
register int stkptr asm("bl");
#endif
extern stack_t stktab[];

int yylex(), yyparse(), yyerror(char *str);

void enterdef(char *str, node_t *next);
node_t *entersym(char *str);
node_t *newlist(node_t *ptr);
node_t *newnode(int type, int value);
node_t *concat(node_t *node, node_t *next);
node_t *copy(node_t *node);
node_t *reverse(node_t *cur);
void writeterm(node_t *cur);
void writefactor(stack_t *cur);
void exeterm(node_t *cur);
void writestack();
void debug(node_t *cur);
void compile(node_t *cur);
node_t *cons(stack_t *node, node_t *next);
void table();
node_t *stk2lst();
void lst2stk(node_t *root);
void execute(node_t *cur);
node_t *mem_alloc();
void mem_free();
