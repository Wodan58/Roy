/*
    module  : jsound.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSOUND_C
#define JSOUND_C

/**
jsound  :  sound  ->
Play a sound.
*/
void do_jsound(void)
{
    char *sound;

    COMPILE;
    sound = (char *)do_pop();
    j_sound(sound);
}
#endif
