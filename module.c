/*
    module  : module.c
    version : 1.19
    date    : 01/19/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

intptr_t lookup(const char *str);	/* symbol.c */

static char *module;
static int hide_stack[DISPLAYMAX], hide_index, hide_count, inside_hide;

/*
 * initmod registers str as module name. Modules within modules are not
 * supported.
 */
void initmod(char *str)
{
    module = str;
}

/*
 * initpriv registers the current hide number.
 */
void initpriv(void)
{
    if (++hide_index >= DISPLAYMAX)
	execerror("index", "display");
    hide_stack[hide_index] = ++hide_count;
    inside_hide = 1;
}

/*
 * stoppriv registers the transition from private to public definitions.
 */
void stoppriv(void)
{
    inside_hide = 0;
}

/*
 * exitpriv lowers the hide_index.
 */
void exitpriv(void)
{
    if (hide_index)
	hide_index--;
}

/*
 * exitmod deregisters the module. It also ends all outstanding private
 * sections.
 */
void exitmod(void)
{
    exitpriv();
    module = 0;
}

/*
 * iterate traverses the hide stack followed by module and ends with 0.
 */
char *iterate(char *name)
{
    static int index, done;
    int leng;
    char buf[MAXNUM], *ptr, *str;

    if ((ptr = strchr(name, '.')) == 0) {
	index = hide_index;
	done = 0;
	ptr = name;
    } else
	ptr++;
    if (index) {
	sprintf(buf, "%d", hide_stack[index--]);
	leng = strlen(buf) + strlen(ptr) + 2;
	str = GC_malloc_atomic(leng);
	sprintf(str, "%s.%s", buf, ptr);
	return str;
    }
    if (module && !done) {
	done = 1;
	leng = strlen(module) + strlen(ptr) + 2;
	str = GC_malloc_atomic(leng);
	sprintf(str, "%s.%s", module, ptr);
	return str;
    }
    return 0;
}

/*
 * classify prepends a name with private section or module name, whichever
 * comes first.
 */
char *classify(char *name)
{
    size_t leng;
    char buf[MAXNUM], *str;

    if (inside_hide) {
	sprintf(buf, "%d", hide_stack[hide_index]);
	leng = strlen(buf) + strlen(name) + 2;
	str = GC_malloc_atomic(leng);
	sprintf(str, "%s.%s", buf, name);
	name = str;
    } else if (module) {
	leng = strlen(module) + strlen(name) + 2;
	str = GC_malloc_atomic(leng);
	sprintf(str, "%s.%s", module, name);
	name = str;
    }
    return name;
}

/*
 * qualify returns the qualified name.
 *
 * a lookup is done first, verifying that this is not an already defined name.
 * if not already defined, the name can be classified.
 */
char *qualify(char *name)
{
    char *str;

    if (strchr(str = name, '.') == 0)
	while ((str = iterate(str)) != 0)
	    if (lookup(str)) {
		name = str;
		break;
	    }
    return (char *)((intptr_t)name | JLAP_INVALID);
}
