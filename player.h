#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include "song.h"

void playermenu();
void playsong(Song *s);
void playcount(Song *s);
void prev(Song *s, int m);
void next(Song *s, int m);
// void *printProgress(void *arg);
int getLength();
int getPosition();
Song *getRandom(Song *s);

void player(Song *s);

#endif /* PLAYER_H */