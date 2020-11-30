/*
    module  : localtime.c
    version : 1.9
    date    : 11/30/20
*/
#ifndef LOCALTIME_C
#define LOCALTIME_C

/**
localtime  :  I  ->  T
Converts a time I into a list T representing local time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is a Boolean flagging daylight savings/summer time;
weekday is 1 = Monday ... 7 = Sunday.
*/
void do_localtime(void)
{
    int wday;
    struct tm t;
    time_t timval;
    Stack *root = 0;

    UNARY;
    timval = stack[-1];
    localtime_r(&timval, &t);
    if ((wday = t.tm_wday) == 0)
	wday = 7;
    vec_push(root, wday);
    vec_push(root, t.tm_yday);
    vec_push(root, t.tm_isdst);
    vec_push(root, t.tm_sec);
    vec_push(root, t.tm_min);
    vec_push(root, t.tm_hour);
    vec_push(root, t.tm_mday);
    vec_push(root, t.tm_mon + 1);
    vec_push(root, t.tm_year + 1900);
    stack[-1] = (intptr_t)root;
}
#endif
