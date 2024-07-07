#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include "song.h"
#include "player.c"

int main() {
    Song *s = (Song*)malloc(sizeof(Song));
    s->num=1;   //ÐòºÅ¸³Öµ
    s->id=1;
    s->count=1;
    strcpy(s->name,"adf");    //¸èÃû¸³Öµ
    strcpy(s->singer,"adSG");
    strcpy(s->address,"D:/Code/resource/angel_s_song.mp3");
    player(s);
    return 0;
}