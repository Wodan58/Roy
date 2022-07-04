/*
    module  : stop.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef STOP_C
#define STOP_C

void do_stop(void)
{
    COMPILE;
    if (!stack_empty()) {
        switch (autoput) {
        case 0:
            break;
        case 1:
            writefactor(stack_pop());
            break;
        case 2:
            writestack();
            break;
        }
        if (autoput)
            putchar('\n');
    }
}
#endif
