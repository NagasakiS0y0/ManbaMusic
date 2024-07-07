#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "song.h"
void playermenu()
{
		system("cls");
		printf("1.播放/暂停\n");
		printf("2.上一首\n");
		printf("3.下一首\n");
		printf("4.返回歌曲选择\n");
		printf("请选择[1-4]>");
}
    
struct Song *player()
{
	int n,f1,f2;
    int k=0;
    struct song *s;    
    f1=f2=0;
    char command[1024];
	playermenu();
		scanf("%d",&n);
		switch(n)
		{
            case 1:
            {
                if(f1==0)   //打开文件
                {
                    sprintf(command,"open \"%s\" type mpegaudeo alias mp3",s->address);
                    mciSendString(command,NULL,0,NULL);
                    mciSendString("play mp3",NULL,0,NULL);
                    k=1;
                    f1=1;   //文件已打开
                    f2=1;   //状态为播放
                }
                else
                {
                    if(f2==1)   
                    {
                        mciSendString("pause mp3",NULL,0,NULL);
                        f2=1;   //修改状态为暂停
                    }
                    else
                    {
                        mciSendString("resume mp3",NULL,0,NULL);
                        f2=0;   //修改状态为播放
                    }
                }
                break;
            }
            case 2:     //上一首
            {
                s=s->prev;
                sprintf(command,"open \"%s\" type mpegaudeo alias mp3",s->address);     
                mciSendString(command,NULL,0,NULL);     //打开文件
                mciSendString("play mp3",NULL,0,NULL);
                k=1;      //播放
                break;
            }
            case 3:     //下一首
            {
                s=s->next;
                sprintf(command,"open \"%s\" type mpegaudeo alias mp3",s->address);
                mciSendString(command,NULL,0,NULL);     //打开文件
                mciSendString("play mp3",NULL,0,NULL);
                k=1;      //播放
                break;
            }
	}
    if (k=1)
    {
        return s;
    }
    else return NULL;
}
void count()
{
    struct song *p1;
    struct song *h;
    char command[1024];
    int n;
    FILE *fp3;
    if ((fp3=fopen("song.txt","r"))==NULL)
    {
        printf("can't find file!\n");
        exit(0);
    }
    h=player();
        while (fscanf(fp3,"%d%s%s%d%s",&p1->num,p1->name,p1->singer,&p1->count,&p1->address)!=EOF)
    {
        if (strcmp(h->address,p1->address))
        {
            p1->count++;
        }
        
    }
    

}