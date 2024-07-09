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
		playermenu(s,m,f2);
        printf("请选择[0-3]or[s/l/r] >");
		n=getch();
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
                f1=1;
                f2=1;
                break;
            }
            case '3':     //下一首
            {
                mciSendString("close mp3",NULL,0,NULL);
                s=next(s,m);
                f1=1;
                f2=1;
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

void playcount(Song *s)
{
    FILE *fp;
    char line[256];
    int found = 0;

    fp = fopen("Library/library.txt", "r+");
    if (fp == NULL) {
        printf("Error opening library.txt\n");
        return;
    }

    while (fgets(line,sizeof(line),fp)){
        int num;
        int id;
        int count;
        char name[50];
        char address[256];

        // 解析行中的数据
        if (sscanf(line, "%d %d %d %49s %255s", &num,&id,&count,name,address)!=EOF) {
            // 如果找到了匹配的ID
            if (id == s->id) {
                count++; // 增加播放次数
                if (count%10){
                    fseek(fp, -strlen(line)-1, SEEK_CUR);   // 将文件指针移回到行的开始(位数未增加)
                }else{
                    fseek(fp, -strlen(line)-2, SEEK_CUR);   // 将文件指针移回到行的开始(位数增加)
                }
                fprintf(fp, "%d %d %d %s %s\n",num, id, count, name, address);  // 重写这一行
                found = 1;
                break; // 找到并修改后退出循环
            }
        }
    }
    fclose(fp);
    if (!found) {
        printf("Song not found in the library.\n");
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
        case 0:{printf("[单曲循环] ");break;}
        case 1:{printf("[列表循环] ");break;}
        case 2:{printf("[随机播放] ");break;}
    }
    printf("当前曲目");
    if(f2==0)
    {
        printf(" [|>] %s\n",s->name);
    }
    else
    { 
        printf(" [||] %s\n",s->name);
    }
	printf("%-20s%-20s\n", "1.播放/暂停", "2.上一首");
    printf("%-20s%-20s\n", "3.下一首", "0.返回歌曲选择");
    printf("输入[s]单曲循环,输入[l]列表循环,输入[r]乱序播放\n");
    printf("***********************************************************\n");
}
