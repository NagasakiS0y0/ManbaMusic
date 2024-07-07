#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "song.h"

void playermenu(Song *s);
void playsong(Song *s);
void playcount(Song *s);
void player (Song *s)
{
	int n,f1,f2;    //f1Ϊ�ļ��Ƿ�򿪣�f2Ϊ�����Ƿ���ͣ
    f1=f2=0;
	while(1)
	{
		playermenu(s);
		scanf("%d",&n);
		switch(n)
		{
            case 1:
            {
                if(f1==0)   //���ļ�
                {
                    playsong(s);
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
                playsong(s);
                break;
            }
            case 3:     //��һ��
            {
                s=s->next;
                playsong(s);
                break;
            }
            case 4:     //���ظ���ѡ��
            {
                mciSendString("close mp3",NULL,0,NULL);
                return;
            }
		}
	}
}

void playsong(Song *s)
{
    char command[255];
    sprintf(command, "open \"%s\" type mpegaudio alias mp3dev", s->address);
    printf("%s\n", command);
    mciSendString(command, NULL, 0, NULL);
    mciSendString("play mp3dev", NULL, 0, NULL);
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
		printf("1.����/��ͣ\n");
		printf("2.��һ��\n");
		printf("3.��һ��\n");
		printf("4.���ظ���ѡ��\n");
		printf("��ѡ��[1-4]>");
}