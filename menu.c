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
            player (s);
            break;
        case 2:
            explore(s);
            player (s);
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
    



