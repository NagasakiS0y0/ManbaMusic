#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h> 
#include "createLibrary.c"
#include "createCatalog.c"
#include "player.c"
//#include "interface.c"
#include "explore_re2.c"
#include "song.h"

void menu_re(Song *s)
{
    int i;
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
       
        break;
    default:
        break;
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
        printf("创建完成！\n");
    }
    fclose(fp_lib);
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
    case 2:
        birthSongsFromFile(&s);
        menu_re(s);
        break;
    
    default:
        break;
    }
    return 0;
    

    //显示歌单列表
    /*FILE *fp_log;
    fp_log=fopen("listCatalog.txt","r");
    if (fp_log==NULL)
    {
        printf("正在创建歌单。\n");
        s=createFromLib();
        FILE *fp_1;
        fp_1=fopen("List/lib.txt","w");
        while (s!=NULL)
        {
            fprintf(fp_1, "%d %d %s %s\n", &s->num, &s->id, s->name, s->address);
            s=s->next;
        }
         fclose(fp_1);
         fclose(fp_log);
         fp_log=fopen("listCatalog.txt","w");

    }
    
    readListsFromFile(&catalog);
    printf("歌单列表如下:\n");
    printListCatalog(catalog);
    getchar();
    free(catalog);
    return 0;*/

}


