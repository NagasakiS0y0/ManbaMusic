#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h> 
#include "createList_zk.c"
#include "createlist.c"
#include "createCatalog.c"
#include "interface.c"
#include "explore_re2.c"
#include "song.h"

void printSongListforExplore(Song *s) {
    Song *current = s;
    while (current->next != s) {
        printf("%03d|%d| %s\n", current->num,current->count, current->name);
        current = current->next;
    }
    printf("%03d|%d|%s\n\n", current->num,current->count, current->name);
}
void playerforExplore (Song *s)
{
	int f1,f2,m;    //f1为文件是否打开，f2为播放是否暂停
    char n;
    f1=f2=0;
    m=1;    //播放模式默认为列表循环
    srand(time(NULL));

	while(1)
	{
        system("cls");
        printSongListforExplore(s);
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
void menu_manba()
{
    printf("正在读取音乐库文件。\n");
    mciSendString("open \"resource/ManbaOut.mp3\" alias mp3", NULL, 0, NULL);
    mciSendString("play mp3", NULL, 0, NULL);
    char manba[30]={"Man what can I say! Manba out!"};
    char *s=manba;
    
    while(*s!='\0')
    {
        Sleep(150);
        printf("%c",*s);
        s++;
    }
    printf("\n读取成功！\n");Sleep(1000);
    printf("欢迎使用Manba Music！");Sleep(3000);
    mciSendString("close mp3", NULL, 0, NULL);
}

void menu_pl(catalog)
{
    char i;
    while(1)
    {
        FILE *fp4;
        fp4=fopen("listCatalog.txt","r");
        free(catalog);
        List *catalog=NULL;
        scantxtFiles(); 
        readListsFromFile(&catalog);
        system("cls");
        printListCatalog(catalog);
        printf("\n           Manba Music\n");
        printf("*************************************\n");
        printf("             输入数字选择歌单       \n");
        printf("             输入c创建新的歌单      \n");
        printf("             输入0返回        \n");
        printf("*************************************\n");
        printf("请输入您的选择:   ");
        i=getch();
        switch (i)
        {
        case 'c':
            createList_zk();
            menu_pl(catalog);
            break;
        case '0':
            fclose(fp4);
            return;
        default:
            for(List *find=catalog;find!=NULL;find=find->next)
            {
                if(i-'0'==find->listNum)
                {
                    listMain(find);
                    break;
                }
            }
            break;
        }
    }
}

void menu_re(Song *s)
{
    int i;
    while(1)
    {
        FILE *fp5;
        fp5=fopen("Library/library.txt","r");
        free(s);
        Song *s=NULL;
        birthSongsFromFile(&s);
        fclose(fp5);
        system("cls");
        printf("            Manba Music\n");
        printf("*************************************\n");
        printf("                             \n");
        printf("             1.心动模式       \n");
        printf("             2.探索模式       \n");
        printf("               0.退出        \n");
        printf("                             \n");
        printf("*************************************\n");
        printf("请输入您的选择:   ");
        scanf("%d",&i);
        switch (i)
        {
        case 1:
            recommendation(s);
            playerforExplore (s);
            break;
        case 2:
            explore(s);
            playerforExplore (s);
            break;
        case 0:
            return;
            break;
        default:
            break;
        }
    }
    free(s);
}

int main()
{
    menu_manba();
    int i=0;
    List *catalog=NULL;
    Song *s=NULL;
    List *l=NULL;
    FILE *fp_lib;
    fp_lib=fopen("Library/library.txt","r");
    if (fp_lib == NULL)
    {
        printf("正在创建音乐库文件。\n");
        createLibrary();
        tihuan();
        printf("创建完成！\n");
    }
    fclose(fp_lib);
    
    while (1)
    {
        
        system("cls");
        printf("            Manba Music\n");
        printf("*************************************\n");
        printf("                             \n");
        printf("           1.歌单播放模式      \n");
        printf("           2.歌曲推荐模式      \n");
        printf("               0.退出      \n");
        printf("                             \n");
        printf("*************************************\n");
        printf("请输入您的选择:   ");
        scanf("%d",&i);
        switch (i)
        {
            case 1:
                menu_pl(catalog);
                break;
            case 2:
                birthSongsFromFile(&s);
                menu_re(s);
                break;
            case 0:
                exit(0);
        }
    }
    return 0;
}
    



