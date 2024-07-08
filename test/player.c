#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include "song.h"

void checkSongList(Song *head);
void playermenu(Song *s,int m);
void playsong(Song *s);
void playcount(Song *s);
Song *prev(Song *s,int m);
Song *next(Song *s,int m);
//void *printProgress(void *arg);
int getLength();
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
		playermenu(s,m);
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
                mciSendString("close mp3",NULL,0,NULL);
                s=prev(s,m);
                break;
            }
            case '3':     //��һ��
            {
                mciSendString("close mp3",NULL,0,NULL);
                s=next(s,m);
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

int getLength()
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
        int length = getLength();
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

/*void playcount(Song *s)
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
}*/

void playermenu(Song *s,int m)
{
		//system("cls");
        switch(m)
        {
            case 0:{printf("[����ѭ��] ");break;}
            case 1:{printf("[�б�ѭ��] ");break;}
            case 2:{printf("[�������] ");break;}
        }
        printf("---��ǰ���ڲ���%s---\n",s->name);
		printf("1.����/��ͣ\n");
		printf("2.��һ��\n");
		printf("3.��һ��\n");
		printf("0.���ظ���ѡ��\n");
        printf("����s����ѭ��,����l�б�ѭ��,����r���򲥷�\n");
		printf("��ѡ��[0-3]or[s/l/r]>");
}

///////////////////////////////////////////////////////////////////////////////////



// ��������
void readSongsFromFile(Song **head);
void printSongList(Song *head);
void selectSongToPlay(Song *head);
void addSong(Song **head, Song *newSong);

int main() {
    Song *head = NULL; // ��ʼ������ͷָ��

    // ���ļ��ж�ȡ������Ϣ����������
    readSongsFromFile(&head);

    // �û�ѡ��������в���
    selectSongToPlay(head);

    // ��������
    Song *current = head->next;
    while (current != head) {
        Song *next = current->next;
        free(current);
        current = next;
    }
    free(head);

    return 0;
}

void readSongsFromFile(Song **head) {
    FILE *fp;
    fp = fopen("library.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "�޷����ļ�\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        Song *newSong = (Song *)malloc(sizeof(Song));
        if (newSong == NULL) {
            fprintf(stderr, "�ڴ����ʧ��\n");
            return;
        }
        sscanf(buffer, "%d %d %d %49s %255s",&newSong->num, &newSong->id, &newSong->count, newSong->name, newSong->address);
        addSong(head, newSong);
    }
    fclose(fp);
}

void printSongList(Song *head) 
{
    Song *current = head;
    printf("�����б�:\n");
    while (current->prev != head) 
    {
        printf("%03d | %s\n", current->num, current->name);
        current = current->prev;
    }
    printf("%03d | %s\n", current->num, current->name);
}

void selectSongToPlay(Song *head) {
    int choice;
    Song *current = head; // ��current��ʼ��Ϊhead
    
    while (1) { // ʹ������ѭ����ֱ���û�ѡ���˳�
        printSongList(head);
        printf("������Ҫ���ŵĸ�����ţ�����0�˳���: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            return; // �û�ѡ���˳�
        }
        
        current = head; // ÿ��ѭ����ʼʱ����currentΪhead
        while (current->num != choice) {
            if (current->next == head) {
                printf("������Ų����ڣ����������롣\n");
                break; // �����������β����δ�ҵ����������˳�ѭ��
            }
            current = current->next;
        }
        
        if (current->num == choice) {
            player(current); // �ҵ�����������
        }
    }
}

void addSong(Song **head, Song *newSong) {
    if (*head == NULL) {
        // �������Ϊ�գ��½ڵ����ͷ�ڵ�Ҳ��β�ڵ�
        *head = newSong;
        newSong->next = newSong;
        newSong->prev = newSong;
    } else {
        // ����Ϊ�գ����½ڵ���ӵ�����ĩβ
        Song *last = (*head)->prev;
        last->next = newSong;
        newSong->prev = last;
        newSong->next = *head;
        (*head)->prev = newSong;
    }
}

void checkSongList(Song *head) 
{
    if (head == NULL) {
        printf("����Ϊ�ա�\n");
        return;
    }

    Song *current = head;
    do {
        printf("������ţ�%d, �������ƣ�%s, ǰ���ڵ��ţ�%d, ��̽ڵ��ţ�%d\n",
               current->num, current->name,
               current->prev->num, current->next->num);
        current = current->next;
    } while (current != head);
}
