/*
    module  : localtime.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef LOCALTIME_C
#define LOCALTIME_C

#ifdef _MSC_VER
void localtime_r(time_t *t, struct tm *tm)
{
    *tm = *localtime(t);
}
#endif

/**
1700  localtime  :  DA	I  ->  T
Converts a time I into a list T representing local time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is a Boolean flagging daylight savings/summer time;
weekday is 1 = Monday ... 7 = Sunday.
*/
void do_localtime(void)
{
    static int daynums[] = { 7, 1, 2, 3, 4, 5, 6 };
    int wday;
    struct tm t;
    time_t timval;
    Stack *list = 0;

    ONEPARAM;
    INTEGER;
    timval = GET_AS_INTEGER(stack[-1]);
    localtime_r(&timval, &t);
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
