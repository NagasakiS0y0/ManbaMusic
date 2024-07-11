#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include "song.h"

void checkSongList(Song *head);     //检查歌曲列表
void playermenu(Song *s,int m,int f2);      //播放界面
void playsong(Song *s);     //播放歌曲
void playcount(Song *s);    //播放次数+1
void printSongList(Song *s);    //打印歌曲列表
Song *prev(Song *s,int m);    //上一首
Song *next(Song *s,int m);    //下一首
Song *getRandom(Song *s);    //随机播放

void player (Song *s)     //播放歌曲功能，接受指向歌曲的指针，可调用
{
	int f1,f2,m;    //f1为文件是否打开，f2为播放是否暂停
    char n;
    f1=f2=0;
    m=1;    //播放模式默认为列表循环
    srand(time(NULL));

	while(1)
	{
        system("cls");
        printSongList(s);
		playermenu(s,m,f2);
        printf("请选择[0-3]or[s/l/r] >");
		n=getch();
		switch(n)
		{
            case '1':
            {
                if(f1==0)   //打开文件
                {
                    playsong(s);
                    f1=1;   //文件已打开
                    f2=1;   //状态为播放
                    break;
                }
                else
                {
                    if(f2==1)
                    {
                        mciSendString("pause mp3",NULL,0,NULL);
                        f2=0;   //修改状态为暂停
                        break;
                    }
                    else
                    {
                        mciSendString("resume mp3",NULL,0,NULL);
                        f2=1;   //修改状态为播放
                        break;
                    }
                }
            }
            case '2':     //上一首
            {
                mciSendString("close mp3",NULL,0,NULL);
                s=prev(s,m);
                f1=1;
                f2=1;
                break;
            }
            case '3':     //下一首
            {
                mciSendString("close mp3",NULL,0,NULL);
                s=next(s,m);
                f1=1;
                f2=1;
                break;
            }
            case '0':     //返回歌曲选择
            {
                mciSendString("close mp3",NULL,0,NULL);
                return;
            }
            case 's':{m=0;break;}   //单曲循环
            case 'l':{m=1;break;}   //列表循环
            case 'r':{m=2;break;}   //随机播放
		}
	}
}


void playsong(Song *s)      //播放歌曲
{
    mciSendString("close mp3",NULL,0,NULL);     //先确认关闭文件
    char command[256];
    char length[11];
    sprintf(command, "open \"%s\" alias mp3",s->address);   
    mciSendString(command, NULL, 0, NULL);      //打开文件
    mciSendString("play mp3", NULL, 0, NULL);       //播放文件
    playcount(s);
}

Song *prev(Song *s,int m)   //上一首
{
    switch (m)
    {
        case 0:     
        {
            playsong(s);
            break;
        }
        case 1:
        {
            s=s->prev;
            playsong(s);
            break;
        }
        case 2:
        {
            s = getRandom(s);
            playsong(s);
            break;
        }
    }
    return s;
}

Song *next(Song *s,int m)   //下一首
{
    switch (m)
    {
        case 0:
        {
            playsong(s);
            break;
        }
        case 1:
        {
            s=s->next;
            playsong(s);
            break;
        }
        case 2:
        {
            s = getRandom(s);
            playsong(s);
            break;
        }
    }
    return s;
}

Song *getRandom(Song *s)    //随机播放
{
    int totalSongs=1;    //默认歌曲数为1
    Song *temp;

    for(temp=s;temp->next!=s;temp=temp->next)
    {
        totalSongs ++;
    }   //计算歌曲总数

    int randomnum=rand()%totalSongs+1;

    temp=s;
    for(int i = 1; i < randomnum; i++)  //找到随机歌曲
    {
        temp = temp->next;
    }
    return temp;
}

void playcount(Song *s)     //播放次数+1
{
    FILE *fp;
    char line[256];
    int found = 0;
    char *tempFile = "temp.txt";

    fp = fopen("Library/library.txt", "r");
    if (fp == NULL) {
        printf("Error opening library.txt\n");
        return;
    }

    // 创建临时文件用于写入更新后的数据
    FILE *tempFp = fopen(tempFile, "w");
    if (tempFp == NULL) {
        printf("Error creating temp file\n");
        fclose(fp);
        return;
    }

    while (fgets(line, sizeof(line), fp))
    {
        int num;
        int id;
        int count;
        char name[50];
        char address[256];

        if (sscanf(line, "%d %d %d %49s %255s", &num, &id, &count, name, address) !=EOF) 
        {
            if (id == s->id) 
            {
                count++; // 增加播放次数
                // 写入临时文件
                fprintf(tempFp, "%d %d %d %s %s\n", num, id, count, name, address);
                found = 1;
            } else 
            {
                // 如果不是目标歌曲，直接复制到临时文件
                fputs(line, tempFp);
            }
        }
    }

    fclose(fp);
    fclose(tempFp);

    if (!found) 
    {
        printf("Song not found in the library.\n");
    } else 
    {
        // 替换原文件
        remove("Library/library.txt");
        rename(tempFile, "Library/library.txt");
    }
}

void printSongList(Song *s)     //打印歌曲列表
{
    Song *current = s;
    while (current->next != s) {
        printf("%03d |%s\n", current->num, current->name);
        current = current->next;
    }
    printf("%03d |%s\n\n", current->num,current->name);
}

void playermenu(Song *s,int m,int f2)       //播放界面
{
	printf("\n***********************************************************\n");
    switch(m)
    {
        case 0:{printf("[单曲循环] ");break;}
        case 1:{printf("[列表循环] ");break;}
        case 2:{printf("[随机播放] ");break;}
    }
    printf("当前曲目");
    if(f2==0)
    {
        printf(" [|>] %s\n",s->name);
    }
    else
    { 
        printf(" [||] %s\n",s->name);
    }
	printf("%-20s%-20s\n", "1.播放/暂停", "2.上一首");
    printf("%-20s%-20s\n", "3.下一首", "0.返回歌曲选择");
    printf("输入[s]单曲循环,输入[l]列表循环,输入[r]乱序播放\n");
    printf("***********************************************************\n");
}
