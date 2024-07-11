#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include "song.h"

void checkSongList(Song *head);     //�������б�
void playermenu(Song *s,int m,int f2);      //���Ž���
void playsong(Song *s);     //���Ÿ���
void playcount(Song *s);    //���Ŵ���+1
void printSongList(Song *s);    //��ӡ�����б�
Song *prev(Song *s,int m);    //��һ��
Song *next(Song *s,int m);    //��һ��
Song *getRandom(Song *s);    //�������

void player (Song *s)     //���Ÿ������ܣ�����ָ�������ָ�룬�ɵ���
{
	int f1,f2,m;    //f1Ϊ�ļ��Ƿ�򿪣�f2Ϊ�����Ƿ���ͣ
    char n;
    f1=f2=0;
    m=1;    //����ģʽĬ��Ϊ�б�ѭ��
    srand(time(NULL));

	while(1)
	{
        system("cls");
        printSongList(s);
		playermenu(s,m,f2);
        printf("��ѡ��[0-3]or[s/l/r] >");
		n=getch();
		switch(n)
		{
            case '1':
            {
                if(f1==0)   //���ļ�
                {
                    playsong(s);
                    f1=1;   //�ļ��Ѵ�
                    f2=1;   //״̬Ϊ����
                    break;
                }
                else
                {
                    if(f2==1)
                    {
                        mciSendString("pause mp3",NULL,0,NULL);
                        f2=0;   //�޸�״̬Ϊ��ͣ
                        break;
                    }
                    else
                    {
                        mciSendString("resume mp3",NULL,0,NULL);
                        f2=1;   //�޸�״̬Ϊ����
                        break;
                    }
                }
            }
            case '2':     //��һ��
            {
                mciSendString("close mp3",NULL,0,NULL);
                s=prev(s,m);
                f1=1;
                f2=1;
                break;
            }
            case '3':     //��һ��
            {
                mciSendString("close mp3",NULL,0,NULL);
                s=next(s,m);
                f1=1;
                f2=1;
                break;
            }
            case '0':     //���ظ���ѡ��
            {
                mciSendString("close mp3",NULL,0,NULL);
                return;
            }
            case 's':{m=0;break;}   //����ѭ��
            case 'l':{m=1;break;}   //�б�ѭ��
            case 'r':{m=2;break;}   //�������
		}
	}
}


void playsong(Song *s)      //���Ÿ���
{
    mciSendString("close mp3",NULL,0,NULL);     //��ȷ�Ϲر��ļ�
    char command[256];
    char length[11];
    sprintf(command, "open \"%s\" alias mp3",s->address);   
    mciSendString(command, NULL, 0, NULL);      //���ļ�
    mciSendString("play mp3", NULL, 0, NULL);       //�����ļ�
    playcount(s);
}

Song *prev(Song *s,int m)   //��һ��
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

Song *next(Song *s,int m)   //��һ��
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

Song *getRandom(Song *s)    //�������
{
    int totalSongs=1;    //Ĭ�ϸ�����Ϊ1
    Song *temp;

    for(temp=s;temp->next!=s;temp=temp->next)
    {
        totalSongs ++;
    }   //�����������

    int randomnum=rand()%totalSongs+1;

    temp=s;
    for(int i = 1; i < randomnum; i++)  //�ҵ��������
    {
        temp = temp->next;
    }
    return temp;
}

void playcount(Song *s)     //���Ŵ���+1
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

    // ������ʱ�ļ�����д����º������
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
                count++; // ���Ӳ��Ŵ���
                // д����ʱ�ļ�
                fprintf(tempFp, "%d %d %d %s %s\n", num, id, count, name, address);
                found = 1;
            } else 
            {
                // �������Ŀ�������ֱ�Ӹ��Ƶ���ʱ�ļ�
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
        // �滻ԭ�ļ�
        remove("Library/library.txt");
        rename(tempFile, "Library/library.txt");
    }
}

void printSongList(Song *s)     //��ӡ�����б�
{
    Song *current = s;
    while (current->next != s) {
        printf("%03d |%s\n", current->num, current->name);
        current = current->next;
    }
    printf("%03d |%s\n\n", current->num,current->name);
}

void playermenu(Song *s,int m,int f2)       //���Ž���
{
	printf("\n***********************************************************\n");
    switch(m)
    {
        case 0:{printf("[����ѭ��] ");break;}
        case 1:{printf("[�б�ѭ��] ");break;}
        case 2:{printf("[�������] ");break;}
    }
    printf("��ǰ��Ŀ");
    if(f2==0)
    {
        printf(" [|>] %s\n",s->name);
    }
    else
    { 
        printf(" [||] %s\n",s->name);
    }
	printf("%-20s%-20s\n", "1.����/��ͣ", "2.��һ��");
    printf("%-20s%-20s\n", "3.��һ��", "0.���ظ���ѡ��");
    printf("����[s]����ѭ��,����[l]�б�ѭ��,����[r]���򲥷�\n");
    printf("***********************************************************\n");
}
