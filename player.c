#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include "song.h"

void playermenu(Song *s);
void playsong(Song *s);
void playcount(Song *s);
void prev(Song *s,int m);
void next(Song *s,int m);
Song *getRandom(Song *s);
void player (Song *s)
{
	int f1,f2,m;    //f1为文件是否打开，f2为播放是否暂停
    char n;

    f1=f2=0;
    m=0;    //播放模式默认为单曲循环
    srand(time(NULL));

	while(1)
	{
		playermenu(s);
		scanf(" %c",&n);
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
                prev(s,m);
                break;
            }
            case '3':     //下一首
            {
                next(s,m);
                break;
            }
            case '4':     //返回歌曲选择
            {
                mciSendString("close mp3",NULL,0,NULL);
                return;
            }
            case 's':{m=0;break;}
            case 'l':{m=1;break;}
            case 'r':{m=2;break;}
		}
	}
}

void playsong(Song *s)
{
    char command[256];
    sprintf(command, "open \"%s\" alias mp3", s->address);
    mciSendString(command, NULL, 0, NULL);
    mciSendString("play mp3", NULL, 0, NULL);
}

void prev(Song *s,int m)
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
            s=getRandom(s);
            playsong(s);
            break;
        }
    }
} 

void next(Song *s,int m)
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
            s=getRandom(s);
            playsong(s);
            break;
        }
    }
}

Song *getRandom(Song *s)
{
    int totalSongs=1;    //默认歌曲数为1
    Song *temp;

    for(temp=s;temp->next!=s;temp=temp->next)
    {
        totalSongs ++;
    }

    int randomnum=rand()%totalSongs+1;

    temp=s;
    for(int i = 1; i < randomnum; i++)  //找到随机歌曲
    {
        temp = temp->next;
    }
    return temp;
}



void playcount(Song *s)
{
    FILE *fp;
    char line[256];
    int found = 0;

    fp = fopen("library.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line,sizeof(line),fp)){
        int num;
        int id;
        int count;
        char name[50];
        char singer[50];
        char address[1024];

        // 解析行中的数据
        if (sscanf(line, "%d%d%d%49s%49s%1023s", &num,&id,&count,name,singer,address) == 6) {
            // 如果找到了匹配的ID
            if (id == s->id) {
                count++; // 增加播放次数

                // 将文件指针移回到行的开始
                fseek(fp, -strlen(line), SEEK_CUR);

                // 重写这一行
                fprintf(fp, "%d:%d:%s:%s:%s\n", id, count, name, singer, address);

                found = 1;
                break; // 找到并修改后退出循环
            }
        }
    }
    fclose(fp);
    if (!found) {
        printf("Song not found in the library.\n");
    }
}

void playermenu(Song *s)
{
		system("cls");
        printf("---当前正在播放%s---\n",s->name);
		printf("1.播放/暂停\n");
		printf("2.上一首\n");
		printf("3.下一首\n");
		printf("4.返回歌曲选择\n");
        printf("输入s单曲循环,输入l列表循环,输入r乱序播放\n");
		printf("请选择[1-4]or[s/l/r]>");
}