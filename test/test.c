#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include "song.h"
#include "player.c"

int main() {
    Song *s = (Song*)malloc(sizeof(Song));
    s->num=1;   //��Ÿ�ֵ
    s->id=1;
    s->count=1;
    strcpy(s->name,"adf");    //������ֵ
    strcpy(s->address,"D:/Music/���E��/Ӱɫ��.wav");
    player(s);
    return 0;
}