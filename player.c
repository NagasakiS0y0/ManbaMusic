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
	int f1,f2,m;    //f1Ϊ�ļ��Ƿ�򿪣�f2Ϊ�����Ƿ���ͣ
    char n;

    f1=f2=0;
    m=0;    //����ģʽĬ��Ϊ����ѭ��
    srand(time(NULL));

	while(1)
	{
		playermenu(s);
		scanf(" %c",&n);
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
                prev(s,m);
                break;
            }
            case '3':     //��һ��
            {
                next(s,m);
                break;
            }
            case '4':     //���ظ���ѡ��
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

        // �������е�����
        if (sscanf(line, "%d%d%d%49s%49s%1023s", &num,&id,&count,name,singer,address) == 6) {
            // ����ҵ���ƥ���ID
            if (id == s->id) {
                count++; // ���Ӳ��Ŵ���

                // ���ļ�ָ���ƻص��еĿ�ʼ
                fseek(fp, -strlen(line), SEEK_CUR);

                // ��д��һ��
                fprintf(fp, "%d:%d:%s:%s:%s\n", id, count, name, singer, address);

                found = 1;
                break; // �ҵ����޸ĺ��˳�ѭ��
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
        printf("---��ǰ���ڲ���%s---\n",s->name);
		printf("1.����/��ͣ\n");
		printf("2.��һ��\n");
		printf("3.��һ��\n");
		printf("4.���ظ���ѡ��\n");
        printf("����s����ѭ��,����l�б�ѭ��,����r���򲥷�\n");
		printf("��ѡ��[1-4]or[s/l/r]>");
}