#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define LEN sizeof(struct song)
#ifndef SONG_H
#define SONG_H

typedef struct song
{
    struct song *prev;
	int num;
	char name[50];
	char singer[50]; 
	struct song *next;
} Song;

#endif