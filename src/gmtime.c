/*
    module  : gmtime.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef GMTIME_C
#define GMTIME_C

#ifdef _MSC_VER
void gmtime_r(time_t *t, struct tm *tm) { *tm = *gmtime(t); }
#endif

/**
1710  gmtime  :  DA	I  ->  T
Converts a time I into a list T representing universal time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is false; weekday is 1 = Monday ... 7 = Sunday.
*/
void do_gmtime(void)
{
    static int daynums[] = { 7, 1, 2, 3, 4, 5, 6 };
    int wday;
    struct tm t;
    time_t timval;
    Stack *list = 0;

    ONEPARAM;
    INTEGER;
    timval = GET_AS_INTEGER(stack[-1]);
    gmtime_r(&timval, &t);
    wday = daynums[t.tm_wday];
    vec_push(list, MAKE_INTEGER(wday));
    vec_push(list, MAKE_INTEGER(t.tm_yday));
    vec_push(list, MAKE_BOOLEAN(t.tm_isdst));
    vec_push(list, MAKE_INTEGER(t.tm_sec));
    vec_push(list, MAKE_INTEGER(t.tm_min));
    vec_push(list, MAKE_INTEGER(t.tm_hour));
    vec_push(list, MAKE_INTEGER(t.tm_mday));
    vec_push(list, MAKE_INTEGER(t.tm_mon + 1));
    vec_push(list, MAKE_INTEGER(t.tm_year + 1900));
    stack[-1] = MAKE_LIST(list);
}
#endif
