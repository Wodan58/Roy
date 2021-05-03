/*
    module  : jsetdebug.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETDEBUG_C
#define JSETDEBUG_C

/**
jsetdebug  :  level  ->
Sets the debuglevel to level.
*/
void do_jsetdebug(void)
{
    int level;

    COMPILE;
    level = do_pop();
    j_setdebug(level);
}
#endif
