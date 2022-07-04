/*
    module  : yylex.c
    version : 1.20
    date    : 06/22/22
*/
#include "joy.h"

static FILE *yyin;
static char line[INPLINEMAX], unget[2];
static int echoflag = INIECHOFLAG, ilevel, linenum, linepos;

static struct {
    FILE *fp;
    char *name;
    int linenum;
} infile[INPSTACKMAX];

/*
    inilinebuffer - initialise the stack of input files. Filename is set but
                    not used anywhere.
*/
static void inilinebuffer(void)
{
    infile[0].fp = yyin = stdin;
    infile[0].name = filename ? filename : "stdin";
    infile[0].linenum = 0;
}

/*
    redirect - change input to a new file.
*/
static void redirect(FILE *fp, char *name)
{
    infile[ilevel].linenum = linenum;
    if (ilevel + 1 == INPSTACKMAX)
        execerror("fewer include files", "include");
    infile[++ilevel].fp = yyin = fp;
    infile[ilevel].name = name;
    infile[ilevel].linenum = linenum = 0;
}

/*
    include - insert the contents of a file in the input. If the file cannot be
              found in the current directory, it is searched in the same
              directory as the executable.
*/
void include(char *filnam, int error)
{
    FILE *fp;
    int leng;
    char *path, *str;

    if ((fp = fopen(filnam, "r")) != 0) {
        redirect(fp, GC_strdup(filnam));
        return;
    }
    if ((path = strrchr(g_argv[0], '/')) != 0) {
        leng = path - g_argv[0];
        str = GC_malloc_atomic(leng + strlen(filnam) + 2);
        sprintf(str, "%.*s/%s", leng, g_argv[0], filnam);
        if ((fp = fopen(str, "r")) != 0) {
            redirect(fp, filnam);
            return;
        }
    }
    if (error)
        execerror("valid file name", "include");
}

/*
    yywrap - end of file processing, returning to a previous input.
*/
int yywrap(void)
{
    if (yyin != stdin)
        fclose(yyin);
    if (!ilevel)
        exit(0);
    yyin = infile[--ilevel].fp;
    linenum = infile[ilevel].linenum;
    return 0;
}

/*
    putline - echo an input line.
*/
static void putline(void)
{
    if (echoflag > 2)
        printf("%4d", linenum);
    if (echoflag > 1)
        putchar('\t');
    printf("%s", line);
}

/*
    restofline - handle %PUT and %INCLUDE.
*/
static int restofline(void)
{
    int i;

    if (!strncmp(line, "%PUT", 4))
        fprintf(stderr, "%s", &line[4]);
    else {
        for (i = 0; line[i]; i++)          /* find end of line */
            ;
        while (--i > 0)                    /* remove trailing spaces */
            if (isspace(line[i]))
                line[i] = 0;
            else
                break;
        for (i = 8; isspace(line[i]); i++) /* skip leading spaces */
            ;
        include(&line[i], 1);
    }
    memset(line, 0, INPLINEMAX);
    return 0;
}

/*
    getch - return one character.
*/
static int getch(void)
{
    static int init;
    int ch;

    if (unget[1]) {
        ch = unget[0];
        unget[0] = unget[1];
        unget[1] = 0;
        return ch;
    }
    if (unget[0]) {
        ch = unget[0];
        unget[0] = 0;
        return ch;
    }
    if (!init) {
	init = 1;
	inilinebuffer();
    }
    if (!line[linepos]) {
again:
        if (fgets(line, INPLINEMAX, yyin))
            linenum++;
        else {
            yywrap();
            goto again;
        }
        linepos = 0;
        if (echoflag)
            putline();
        if (line[0] == SHELLESCAPE) {
            system(&line[1]);
            goto again;
        }
    }
    return line[linepos++];
}

/*
    ungetch - stack an unwanted character. A maximum of 2 characters need to
              be remembered here.
*/
static void ungetch(int ch)
{
    if (unget[0])
        unget[1] = unget[0];
    unget[0] = ch;
}

/*
    specialchar - handle character escape sequences.
*/
static int specialchar(void)
{
    int ch, i, num = 0;

    if (strchr("\"'\\btnvfr", ch = getch()))
        switch (ch) {
        case 'b':
            return 8;
        case 't':
            return 9;
        case 'n':
            return 10;
        case 'v':
            return 11;
        case 'f':
            return 12;
        case 'r':
            return 13;
        default:
            return ch;
        }
    if (isdigit(ch)) {
        num = ch - '0';
        for (i = 0; i < 2; i++) {
            ch = getch();
            if (!isdigit(ch)) {
                ungetch(ch);
                yyerror("digit expected");
                return num;
            }
            num = 10 * num + ch - '0';
        }
        return num;
    }
    return ch;
}

/*
    read_char - read one character and return type and value.
*/
static int read_char(void)
{
    int ch;

    if ((ch = getch()) == '\\')
        ch = specialchar();
    yylval.num = ch;
    return CHAR_;
}

/*
    read_string - read a string and return type and value.
*/
static int read_string(void)
{
    int ch, i = 0;
    char string[INPLINEMAX + 1];

    string[i++] = '"';
    while ((ch = getch()) != '"') {
        if (ch == '\\')
            ch = specialchar();
        if (i < INPLINEMAX)
            string[i++] = ch;
    }
    string[i] = 0;
    yylval.str = GC_strdup(string);
    return STRING_;
}

/*
    read_number - read a number and return type and value.
*/
static int read_number(int ch)
{
    int i = 0, dot = 0;
    char string[INPLINEMAX + 1];

    do {
        if (i < INPLINEMAX)
            string[i++] = ch;
        ch = getch();
    } while (isdigit(ch));
    if (ch == '.') {
        ch = getch();
        dot = 1;
    }
    if (isdigit(ch)) {
        if (i < INPLINEMAX)
            string[i++] = '.';
        do {
            if (i < INPLINEMAX)
                string[i++] = ch;
            ch = getch();
        } while (isdigit(ch));
        if (ch == 'e' || ch == 'E') {
            if (i < INPLINEMAX)
                string[i++] = ch;
            if ((ch = getch()) == '-' || ch == '+') {
                if (i < INPLINEMAX)
                    string[i++] = ch;
                ch = getch();
            }
            while (isdigit(ch)) {
                if (i < INPLINEMAX)
                    string[i++] = ch;
                ch = getch();
            }
        }
        ungetch(ch);
        string[i] = 0;
        yylval.dbl = strtod(string, NULL);
        return FLOAT_;
    }
    ungetch(ch);
    if (dot)
        ungetch('.');
    string[i] = 0;
    yylval.num = strtol(string, NULL, 0);
    return INTEGER_;
}

/*
    read_symbol - read a symbol and return type and value.
*/
static int read_symbol(int ch)
{
    int i = 0;
    char string[INPLINEMAX + 1];

    do {
        if (i < INPLINEMAX)
            string[i++] = ch;
        ch = getch();
    } while (isalnum(ch) || strchr("-=_", ch));
    if (ch == '.') {
        if (strchr("-=_", ch = getch()) || isalnum(ch)) {
            if (i < INPLINEMAX)
                string[i++] = '.';
            do {
                if (i < INPLINEMAX)
                    string[i++] = ch;
                ch = getch();
            } while (isalnum(ch) || strchr("-=_", ch));
        } else {
            ungetch(ch);
            ch = '.';
        }
    }
    ungetch(ch);
    string[i] = 0;
    if (isupper((int)string[1])) {
        if (!strcmp(string, "%PUT") || !strcmp(string, "%INCLUDE"))
            return restofline();
        if (!strcmp(string, "END"))
            return END;
        if (!strcmp(string, "LIBRA") || !strcmp(string, "DEFINE")
            || !strcmp(string, "IN") || !strcmp(string, "PUBLIC"))
            return JPUBLIC;
        if (!strcmp(string, "HIDE") || !strcmp(string, "PRIVATE"))
            return JPRIVATE;
        if (!strcmp(string, "MODULE"))
            return MODULE;
    }
    if (!strcmp(string, "=="))
        return JEQUAL;
    if (!strcmp(string, "true")) {
        yylval.num = 1;
        return BOOLEAN_;
    }
    if (!strcmp(string, "false")) {
        yylval.num = 0;
        return BOOLEAN_;
    }
    if (!strcmp(string, "maxint")) {
        yylval.num = MAXINT_;
        return INTEGER_;
    }
    yylval.str = GC_strdup(string);
    return USR_;
}

/*
    read_end - read and return the end symbol, but no symbols start with '.'.
*/
#if 0
static int read_end(void)
{
    int ch;

    ungetch(ch = getch());
    if (isalnum(ch) || ch == '_')
        return read_symbol('.');
    return END;
}
#endif

/*
    read_minus - read either a number or a symbol.
*/
static int read_minus(void)
{
    int ch;

    ungetch(ch = getch());
    if (isdigit(ch))
        return read_number('-');
    return read_symbol('-');
}

/*
    read_octal - read and return an octal or hexadecimal number.
*/
static int read_octal(void)
{
    int ch, i = 0;
    char string[INPLINEMAX + 1];

    string[i++] = '0';
    if ((ch = getch()) == 'x' || ch == 'X') {
        do {
            if (i < INPLINEMAX)
                string[i++] = ch;
            ch = getch();
        } while (isxdigit(ch));
    } else if (isdigit(ch)) {
        while (ch >= '0' && ch <= '7') {
            if (i < INPLINEMAX)
                string[i++] = ch;
            ch = getch();
        }
    }
    string[i] = 0;
    ungetch(ch);
    if (ch == '.')
        return '0';
    yylval.num = strtol(string, NULL, 0);
    return INTEGER_;
}

/*
    yylex - lexical analyzer, filling yylval and returning the token type.
*/
int yylex(void)
{
    int ch;

start:
    while ((ch = getch()) <= ' ')
        ;
    switch (ch) {
    case '(':
        if ((ch = getch()) == '*') {
            ch = getch();
            do
                while (ch != '*')
                    ch = getch();
            while ((ch = getch()) != ')');
            goto start;
        }
        ungetch(ch);
        return '(';
    case '#':
        while ((ch = getch()) != '\n')
            ;
        goto start;
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
    case ';':
        return ch;
    case '.':
        return END;
    case '\'':
        return read_char();
    case '"':
        return read_string();
    case '-':
        return read_minus();
    case '0':
        if ((ch = read_octal()) != '0')
            return ch;
        return read_number(ch);
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return read_number(ch);
    default:
        if ((ch = read_symbol(ch)) == 0)
            goto start;
        return ch;
    }
}

/*
    getechoflag - function that accesses the echo flag.
*/
int getechoflag(void)
{
    return echoflag;
}

/*
    setechoflag - function that sets the echo flag.
*/
void setechoflag(int flag)
{
    echoflag = flag;
}

/*
    yyerror - error processing during source file reads.
*/
int yyerror(char *str)
{
    int i, pos;

    if (!echoflag)
        putline();
    if (echoflag > 1)
        putchar('\t');
    for (i = 0, pos = linepos - 2; i < pos; i++)
        if (line[i] <= ' ')
            putchar(line[i]);
        else
            putchar(' ');
    printf("^\n\t%s\n", str);
    return 0;
}
