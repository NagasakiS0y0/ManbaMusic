#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include "song.h"

void checkSongList(Song *head);
void playermenu(Song *s,int m,int f2);
void playsong(Song *s);
void playcount(Song *s);
void printSongList(Song *s);
Song *prev(Song *s,int m);
Song *next(Song *s,int m);
//void *printProgress(void *arg);
int getLength123();
int getPosition();
Song *getRandom(Song *s);

void player (Song *s)
{
	int f1,f2,m;    //f1Ϊ�ļ��Ƿ�򿪣�f2Ϊ�����Ƿ���ͣ
    char n;
    f1=f2=0;
    m=1;    //����ģʽĬ��Ϊ�б�ѭ��
    srand(time(NULL));

	while(1)
	{
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
            case 's':{m=0;break;}
            case 'l':{m=1;break;}
            case 'r':{m=2;break;}
		}
	}
}

int getLength123()
{
    char length[11];
    mciSendString("status mp3 length", length, 10, NULL);
    return atoi(length);
}

int getPosition()
{
    char position[11];
    mciSendString("status mp3 position", position, 10, NULL);
    return atoi(position);
}

/*void *printProgress(void *args)
{
    while(1)
    {
        printf("\r");
        int length = getLength123();
        int position = getPosition();
        int MinTens_cur = 0, MinOnes_cur = 0, SecTens_cur = 0, SecOnes_cur = 0;
        int MinTens_total = 0, MinOnes_total = 0, SecTens_total = 0, SecOnes_total = 0;

        // ������ʱ�䣨���Ӻ��룩
        MinTens_total = length / 60000;     
        MinOnes_total = (length / 1000) % 60 / 10;
        SecTens_total = ((length / 1000) % 60) / 10;
        SecOnes_total = ((length / 1000) % 60) % 10;

        // ���㵱ǰʱ�䣨���Ӻ��룩
        MinTens_cur = position / 60000;
        MinOnes_cur = (position / 1000) % 60 / 10;
        SecTens_cur = ((position / 1000) % 60) / 10;
        SecOnes_cur = ((position / 1000) % 60) % 10;

        // ��ʾ��ʽ����ʱ��
        pintf("��ǰ���ڲ���");
        printf("[%02d:%02d/%02d:%02d]", MinTens_cur, SecTens_cur*10 + SecOnes_cur, MinTens_total, SecTens_total*10 + SecOnes_total);
        sleep(1);
    }
    return NULL;
}*/

void playsong(Song *s)
{
    mciSendString("close mp3",NULL,0,NULL);
    char command[256];
    char length[11];
    sprintf(command, "open \"%s\" alias mp3",s->address);
    mciSendString(command, NULL, 0, NULL);
    mciSendString("play mp3", NULL, 0, NULL);
    playcount(s);
}

Song *prev(Song *s,int m)
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

Song *next(Song *s,int m)
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

Song *getRandom(Song *s)
{
    int totalSongs=1;    //Ĭ�ϸ�����Ϊ1
    Song *temp;

    for(temp=s;temp->next!=s;temp=temp->next)
    {
        totalSongs ++;
    }

    int randomnum=rand()%totalSongs+1;

    temp=s;
    for(int i = 1; i < randomnum; i++)  //�ҵ��������
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

        if (sscanf(line, "%d %d %d %49s %255s", &num, &id, &count, name, address) == 5) {
            if (id == s->id) {
                count++; // ���Ӳ��Ŵ���
                // д����ʱ�ļ�
                fprintf(tempFp, "%d %d %d %s %s\n", num, id, count, name, address);
                found = 1;
            } else {
                // �������Ŀ�������ֱ�Ӹ��Ƶ���ʱ�ļ�
                fputs(line, tempFp);
            }
        }
    }

    fclose(fp);
    fclose(tempFp);

    if (!found) {
        printf("Song not found in the library.\n");
    } else {
        // �滻ԭ�ļ�
        remove("Library/library.txt");
        rename(tempFile, "Library/library.txt");
    }
}

void printSongList(Song *s) {
    Song *current = s;
    while (current->next != s) {
        printf("%03d | %s\n", current->num, current->name);
        current = current->next;
    }
    printf("%03d | %s\n\n", current->num, current->name);
}

void playermenu(Song *s,int m,int f2)
{
	system("cls");
    printSongList(s);
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
