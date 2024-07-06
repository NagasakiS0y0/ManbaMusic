#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "song.h"

void playermenu();
void player(Song *s)
{
	int n,f1,f2;    //f1Ϊ�ļ��Ƿ�򿪣�f2Ϊ�����Ƿ���ͣ
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
                if(f1==0)   //���ļ�
                {
                    sprintf(command,"open \"%s\" type mpegaudeo alias mp3",s->address);
                    mciSendString(command,NULL,0,NULL);
                    mciSendString("play mp3",NULL,0,NULL);
                    f1=1;   //�ļ��Ѵ�
                    f2=1;   //״̬Ϊ����
                }
                else
                {
                    if(f2==1)   
                    {
                        mciSendString("pause mp3",NULL,0,NULL);
                        f2=1;   //�޸�״̬Ϊ��ͣ
                    }
                    else
                    {
                        mciSendString("resume mp3",NULL,0,NULL);
                        f2=0;   //�޸�״̬Ϊ����
                    }
                }
                break;
            }
            case 2:     //��һ��
            {
                s=s->prev;
                sprintf(command,"open \"%s\" type mpegaudeo alias mp3",s->address);     
                mciSendString(command,NULL,0,NULL);     //���ļ�
                mciSendString("play mp3",NULL,0,NULL);      //����
                break;
            }
            case 3:     //��һ��
            {
                s=s->next;
                sprintf(command,"open \"%s\" type mpegaudeo alias mp3",s->address);
                mciSendString(command,NULL,0,NULL);     //���ļ�
                mciSendString("play mp3",NULL,0,NULL);      //����
                break;
            }
		}
	}
}

void playermenu()
{
		system("cls");
		printf("1.����/��ͣ\n");
		printf("2.��һ��\n");
		printf("3.��һ��\n");
		printf("4.���ظ���ѡ��\n");
		printf("��ѡ��[1-4]>");
}