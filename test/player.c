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
	int f1,f2,m;    //f1为文件是否打开，f2为播放是否暂停
    char n;
    f1=f2=0;
    m=1;    //播放模式默认为列表循环
    srand(time(NULL));

	while(1)
	{
		playermenu(s,m);
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
                mciSendString("close mp3",NULL,0,NULL);
                s=prev(s,m);
                break;
            }
            case '3':     //下一首
            {
                mciSendString("close mp3",NULL,0,NULL);
                s=next(s,m);
                break;
            }
            case '0':     //返回歌曲选择
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

        // 计算总时间（分钟和秒）
        MinTens_total = length / 60000;     
        MinOnes_total = (length / 1000) % 60 / 10;
        SecTens_total = ((length / 1000) % 60) / 10;
        SecOnes_total = ((length / 1000) % 60) % 10;

        // 计算当前时间（分钟和秒）
        MinTens_cur = position / 60000;
        MinOnes_cur = (position / 1000) % 60 / 10;
        SecTens_cur = ((position / 1000) % 60) / 10;
        SecOnes_cur = ((position / 1000) % 60) % 10;

        // 显示格式化的时间
        pintf("当前正在播放");
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
}*/

void playermenu(Song *s,int m)
{
		//system("cls");
        switch(m)
        {
            case 0:{printf("[单曲循环] ");break;}
            case 1:{printf("[列表循环] ");break;}
            case 2:{printf("[随机播放] ");break;}
        }
        printf("---当前正在播放%s---\n",s->name);
		printf("1.播放/暂停\n");
		printf("2.上一首\n");
		printf("3.下一首\n");
		printf("0.返回歌曲选择\n");
        printf("输入s单曲循环,输入l列表循环,输入r乱序播放\n");
		printf("请选择[0-3]or[s/l/r]>");
}

///////////////////////////////////////////////////////////////////////////////////



// 函数声明
void readSongsFromFile(Song **head);
void printSongList(Song *head);
void selectSongToPlay(Song *head);
void addSong(Song **head, Song *newSong);

int main() {
    Song *head = NULL; // 初始化链表头指针

    // 从文件中读取歌曲信息并构建链表
    readSongsFromFile(&head);

    // 用户选择歌曲进行播放
    selectSongToPlay(head);

    // 清理链表
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
        fprintf(stderr, "无法打开文件\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        Song *newSong = (Song *)malloc(sizeof(Song));
        if (newSong == NULL) {
            fprintf(stderr, "内存分配失败\n");
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
    printf("歌曲列表:\n");
    while (current->prev != head) 
    {
        printf("%03d | %s\n", current->num, current->name);
        current = current->prev;
    }
    printf("%03d | %s\n", current->num, current->name);
}

void selectSongToPlay(Song *head) {
    int choice;
    Song *current = head; // 将current初始化为head
    
    while (1) { // 使用无限循环，直到用户选择退出
        printSongList(head);
        printf("请输入要播放的歌曲编号（输入0退出）: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            return; // 用户选择退出
        }
        
        current = head; // 每次循环开始时重置current为head
        while (current->num != choice) {
            if (current->next == head) {
                printf("歌曲编号不存在，请重新输入。\n");
                break; // 如果到达链表尾部而未找到歌曲，则退出循环
            }
            current = current->next;
        }
        
        if (current->num == choice) {
            player(current); // 找到歌曲，播放
        }
    }
}

void addSong(Song **head, Song *newSong) {
    if (*head == NULL) {
        // 如果链表为空，新节点既是头节点也是尾节点
        *head = newSong;
        newSong->next = newSong;
        newSong->prev = newSong;
    } else {
        // 链表不为空，将新节点添加到链表末尾
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
        printf("链表为空。\n");
        return;
    }

    Song *current = head;
    do {
        printf("歌曲编号：%d, 歌曲名称：%s, 前驱节点编号：%d, 后继节点编号：%d\n",
               current->num, current->name,
               current->prev->num, current->next->num);
        current = current->next;
    } while (current != head);
}
