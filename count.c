#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "song.h"
void playermenu()
{
		system("cls");
		printf("1.����/��ͣ\n");
		printf("2.��һ��\n");
		printf("3.��һ��\n");
		printf("4.���ظ���ѡ��\n");
		printf("��ѡ��[1-4]>");
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
                if(f1==0)   //���ļ�
                {
                    sprintf(command,"open \"%s\" type mpegaudeo alias mp3",s->address);
                    mciSendString(command,NULL,0,NULL);
                    mciSendString("play mp3",NULL,0,NULL);
                    k=1;
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
                mciSendString("play mp3",NULL,0,NULL);
                k=1;      //����
                break;
            }
            case 3:     //��һ��
            {
                s=s->next;
                sprintf(command,"open \"%s\" type mpegaudeo alias mp3",s->address);
                mciSendString(command,NULL,0,NULL);     //���ļ�
                mciSendString("play mp3",NULL,0,NULL);
                k=1;      //����
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