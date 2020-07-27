/*
    module  : typeof.c
    version : 1.1
    date    : 07/23/20
*/
#ifndef TYPEOF_C
#define TYPEOF_C

/*
    USR_ = 2,
    ANON_FUNCT_ = 3,
    BOOLEAN_ = 4,
    CHAR_ = 5,
    INTEGER_ = 6,
    SET_ = 7,
    STRING_ = 8,
    LIST_ = 9,
    FLOAT_ = 10,
    FILE_ = 11
*/

/**
typeof  :  X  ->  I
Replace X by its type.
*/
void do_typeof(void)
{
    int type;
    intptr_t temp;

    UNARY;
    temp = stack[-1];
    if (is_boolean(temp))
	type = BOOLEAN_;	// 4
    else if (is_char(temp))
	type = CHAR_;		// 5
    else if (is_integer(temp))
	type = INTEGER_;	// 6, or SET_, 7
    else if (is_file(temp))
	type = FILE_;		// 11
    else if (is_code(temp))
	type = ANON_FUNCT_;	// 3
    else if (is_string(temp))
	type = STRING_;		// 8, or USR_, 2
    else if (is_float(temp))
	type = FLOAT_;		// 10
    else if (is_list(temp))
	type = LIST_;		// 9
    else
	type = 1;		// 1
    stack[-1] = type;
}
#endif
