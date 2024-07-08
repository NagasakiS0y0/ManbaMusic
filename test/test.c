#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include "song.h"
#include "player.c"

int main() {
    Song *s = (Song*)malloc(sizeof(Song));
    s->num=1;   //序号赋值
    s->id=1;
    s->count=1;
    strcpy(s->name,"adf");    //歌名赋值
    strcpy(s->address,"D:/Music/迷跡波/影色舞.wav");
    player(s);
    return 0;
}