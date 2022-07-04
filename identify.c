/*
    module  : identify.c
    version : 1.1
    date    : 06/21/22
*/
#include "joy.h"

/*
    identifier - return a string that is a valid C-identifier. Characters that
                 are allowed are: characters, digits, underscore. There is no
                 restriction on the first character, because the name will be
                 prefixed with 'do_'. Characters that are not allowed and the
                 underscore character are replaced with _ character name _.
                 This strategy allows translation to and from. This also means
                 that the names of builtins that were valid up till now have
                 to be replaced according to the new naming convention.
*/
#define MAXLEN        6        /* string length of an entry */
#define MAXTAB        32       /* number of entries */

/*
    Table with ascii names, as also used in HTML surrounded by & and ;
*/
static char *ascii[] = {
    "excl",       /* exclamation mark */
    "quot",       /* double quotation mark */
    "num",        /* number sign */
    "dollar",     /* dollar sign */
    "percnt",     /* percent sign */
    "amp",        /* ampersand */
    "apos",       /* apostrophe */
    "lpar",       /* left parenthesis */
    "rpar",       /* right parenthesis */
    "ast",        /* asterisk */
    "plus",       /* plus sign */
    "comma",      /* comma */
    "minus",      /* minus sign */
    "period",     /* period */
    "sol",        /* solidus */

    "colon",      /* colon */
    "semi",       /* semicolon */
    "lt",         /* less-than sign */
    "equals",     /* equals */
    "gt",         /* greater-than sign */
    "quest",      /* question mark */
    "commat",     /* commercial at sign */

    "lsqb",       /* left square bracket */
    "bsol",       /* reverse solidus */
    "rsqb",       /* right square bracket */
    "circ",       /* spacing circumflex accent */
    "lowbar",     /* spacing underscore */
    "grave",      /* spacing grave accent */

    "lcub",       /* left curly bracket */
    "verbar",     /* vertical bar */
    "rcub",       /* right curly bracket */
    "tilde"       /* tilde accent */
};

/*
    The same table as above, but now with ascii characters.
*/
static char *unascii[] = {
    "!",        /* exclamation mark */
    "\"",       /* double quotation mark */
    "#",        /* number sign */
    "$",        /* dollar sign */
    "%",        /* percent sign */
    "&",        /* ampersand */
    "'",        /* apostrophe */
    "(",        /* left parenthesis */
    ")",        /* right parenthesis */
    "*",        /* asterisk */
    "+",        /* plus sign */
    ",",        /* comma */
    "-",        /* minus sign */
    ".",        /* period */
    "/",        /* solidus */

    ":",        /* colon */
    ";",        /* semicolon */
    "<",        /* less-than sign */
    "=",        /* equals */
    ">",        /* greater-than sign */
    "?",        /* question mark */
    "@",        /* commercial at sign */

    "[",        /* left square bracket */
    "\\",       /* reverse solidus */
    "]",        /* right square bracket */
    "^",        /* spacing circumflex accent */
    "_",        /* spacing underscore */
    "`",        /* spacing grave accent */

    "{",        /* left curly bracket */
    "|",        /* vertical bar */
    "}",        /* right curly bracket */
    "~"         /* tilde accent */
};

/*
    Search a string in the ascii table. The string ends in _, so a local copy
    is made first. The copy will automatically stop when reaching MAXLEN, but
    really the terminating underscore should be present.
*/
static int search(const char *str)
{
    int i, j;
    char ptr[MAXLEN + 1];

    for (j = i = 0; str[i] != '_'; i++) {
        ptr[j++] = str[i];
        if (j == MAXLEN)
            break;
    }
    ptr[j] = 0;
    for (i = 0; i < MAXTAB; i++)
        if (!strcmp(ptr, ascii[i]))
            break;
    /* the underscored string should be found */
    assert(i < MAXTAB);
    return i;
}

static char *get_ascii_text(int num)
{
    if (iscntrl(num) || isspace(num))
        return 0;
    if (num >= '!' && num <= '/')
        return ascii[num - '!'];
/* here are digits located */
    if (num >= ':' && num <= '@')
        return ascii[num - ':' + 15];
/* here are uppercase characters located */
    if (num >= '[' && num <= '`')
        return ascii[num - '[' + 22];
/* here are lower case characters located */
    if (num >= '{' && num <= '~')
        return ascii[num - '{' + 28];
/* and here is only one control character */
    return 0;
}

/*
    identifier - first determine the required length of the resulting string.
                 The string might contain control characters: they are ignored,
                 but will then differ from the unidentified version.
*/
const char *identifier(const char *str)
{
    int i, j;
    char *ptr, *ascii;

    for (j = i = 0; str[i]; i++)
        if (isalnum((int)str[i]))
            j++;
        else if ((ascii = get_ascii_text(str[i])) != 0)
            j += strlen(ascii) + 2;
    if (j == strlen(str))
        return str;
    ptr = GC_malloc_atomic(j + 1);
    for (j = i = 0; str[i]; i++)
        if (isalnum((int)str[i]))
            ptr[j++] = str[i];
        else if ((ascii = get_ascii_text(str[i])) != 0) {
            /* the underscores are balanced here */
            sprintf(&ptr[j], "_%s_", ascii);
            j += strlen(ascii) + 2;
        }
    ptr[j] = 0;
    return ptr;
}

/*
    unidentify - reverse the transformation done by identifier. The result is
                 a string that can be printed without restriction as long as
                 it is surrounded by double quotes, as a normal C string.
*/
const char *unidentify(const char *str)
{
    char *ptr;
    int i, j, k, l;

    for (k = j = i = 0; str[i]; i++)
        if (!k && isalnum((int)str[i]))
            j++;
        else if (str[i] == '_') {
            if (k)
                k = 0;
            else {
                k = 1;
                j++;
            }
        }
    /* the underscores must be balanced */
    assert(k == 0);
    if (j == strlen(str))
        return str;
    ptr = GC_malloc_atomic(j + 1);
    for (k = j = i = 0; str[i]; i++) {
        if (!k && isalnum((int)str[i]))
            ptr[j++] = str[i];
        else if (str[i] == '_') {
            if (k)
                k = 0;
            else {
                k = 1;
                l = search(&str[i + 1]);
                /* the underscored string should be found */
                assert(l < MAXTAB);
                if (l < MAXTAB)
                    ptr[j++] = *unascii[l];
            }
        }
    }
    ptr[j] = 0;
    return ptr;
}
