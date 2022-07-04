/*
    module  : print.c
    version : 1.26
    date    : 07/04/22
*/
#include "joy.h"

static int mode;

/*
    get_type - return the type of a value.
*/
int get_type(value_t v)
{
    char *ptr;

    switch (GET_TYPE_MASK(v)) {
    case NANBOX_POINTER    : if (nanbox_is_string(v)) {
                                 ptr = nanbox_to_string(v);
                                 return *ptr == '"' ? STRING_ : USR_;
                             }
                             if (nanbox_is_boolean(v))
                                 return BOOLEAN_;
                             return LIST_;
    case NANBOX_INDEX      : return INDEX_;
    case NANBOX_ANON_FUNCT : return ANON_FUNCT_;
    case NANBOX_FILE       : return FILE_;
    case NANBOX_CHAR       : return CHAR_;
    case NANBOX_SET        : return SET_;
    case NANBOX_INTEGER    : return INTEGER_;
    default                : return FLOAT_;
    }
}

/*
    get_string - return the contents of a string, excluding the leading ".
*/
char *get_string(value_t value)
{
    char *str;

    str = GET_AS_USR_STRING(value);
    if (*str == '"')
        str++;
    return str;
}

/*
    stringify - return a string with initial ".
*/
char *stringify(const char *str)
{
    int leng;
    char *ptr;

    leng = str ? strlen(str) : 0;
    ptr = GC_malloc_atomic(leng + 2);
    *ptr = '"';
    ptr[1] = 0;
    if (str)
        strcpy(ptr + 1, str);
    return ptr;
}

/*
    writechar - write a character. Reads the global variable mode.
*/
static void writechar(FILE *fp, int ch)
{
    if (ch >= 8 && ch <= 13) {
        fputc('\\', fp);
	switch (ch) {
	case 8:
	    fputc('b', fp);
	    break;
	case 9:
	    fputc('t', fp);
	    break;
	case 10:
	    fputc('n', fp);
	    break;
	case 11:
	    fputc('v', fp);
	    break;
	case 12:
	    fputc('f', fp);
	    break;
	case 13:
	    fputc('r', fp);
	    break;
	}
    } else if (iscntrl(ch))
	fprintf(fp, mode ? "\\%03d" : "\\%03o", ch); /* C string is octal */
    else
	fputc(ch, fp);
}

/*
    writestring - write a string, including surrounding " and including escapes.
		  A Joy string or a C string is printed, depending on mode.
*/
void writestring(FILE *fp, char *str)
{
    if (mode)
        fputc('"', fp);
    else
        fprintf(fp, "\"\\\""); /* C string is preceded by " */
    while (*++str)
	if (*str == '"' || *str == '\\') /* escape in string, not in char */
	    fprintf(fp, "\\%c", *str);
	else
	    writechar(fp, *str);
    fputc('"', fp);
}

/*
    writeterm - print the contents of a list in readable format.
*/
void writeterm(Stack *list, int i)
{
    if (i == -1)
        i += vec_size(list);
    for (; i >= 0; i--) {
        writefactor(vec_at(list, i));
        if (i)
            putchar(' ');
    }
}

/*
    writefactor - print a factor in readable format.
*/
void writefactor(value_t value)
{
    int i, type;
    uint64_t set, j;

    type = get_type(value);
    switch (type) {
    case INDEX_:
        printf("%s", str_locate(GET_AS_USR_INDEX(value)));
        break;
    case USR_:
        printf("%s", (char *)GET_AS_USR_STRING(value));
        break;
    case ANON_FUNCT_:
        printf("%s", find(GET_AS_ANON_FUNCT(value)));
        break;
    case BOOLEAN_:
        printf("%s", GET_AS_BOOLEAN(value) ? "true" : "false");
        break;
    case CHAR_:
	putchar('\'');
	mode = 1;
	writechar(stdout, GET_AS_CHAR(value));
	mode = 0;
        break;
    case INTEGER_:
        printf("%ld", (long)GET_AS_INTEGER(value));
        break;
    case SET_:
        set = GET_AS_SET(value);
        putchar('{');
        for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
            if (set & j) {
                printf("%d", i);
                if ((set &= ~j) == 0)
                    break;
                putchar(' ');
            }
        putchar('}');
        break;
    case STRING_:
        mode = 1;
        writestring(stdout, GET_AS_USR_STRING(value));
        mode = 0;
        break;
    case LIST_:
        putchar('[');
        writeterm((Stack *)GET_AS_LIST(value), -1);
        putchar(']');
        break;
    case FLOAT_:
        printf("%g", GET_AS_DOUBLE(value));
        break;
    case FILE_:
        if (GET_AS_FILE(value) == 0)
            printf("file:NULL");
        else if (GET_AS_FILE(value) == stdin)
            printf("file:stdin");
        else if (GET_AS_FILE(value) == stdout)
            printf("file:stdout");
        else if (GET_AS_FILE(value) == stderr)
            printf("file:stderr");
        else
            printf("file:%p", GET_AS_FILE(value));
        break;
    default:
	execerror("valid datatype", "writefactor");
	break;
    }
}
