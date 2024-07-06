#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "song.h"

void playermenu();
void player(Song *s)
{
	int n,f1,f2;    //f1为文件是否打开，f2为播放是否暂停
    f1=f2=0;
    char command[1024];
	while(1)
	{
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
                mciSendString("play mp3",NULL,0,NULL);      //播放
                break;
            }
            case 3:     //下一首
            {
                s=s->next;
                sprintf(command,"open \"%s\" type mpegaudeo alias mp3",s->address);
                mciSendString(command,NULL,0,NULL);     //打开文件
                mciSendString("play mp3",NULL,0,NULL);      //播放
                break;
            }
		}
	}
}

void playermenu()
{
		system("cls");
		printf("1.播放/暂停\n");
		printf("2.上一首\n");
		printf("3.下一首\n");
		printf("4.返回歌曲选择\n");
		printf("请选择[1-4]>");
}