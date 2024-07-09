#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h> 
#include "createLibrary.c"
#include "createCatalog.c"
#include "interface.c"
#include "song.h"

int main()
{
    List *catalog=NULL;
    Song *s=NULL;
    List *l=NULL;
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("                             \n");
    printf("         音乐文件名请别带空格 \n");
    printf("         man what can i say \n");
    printf("                             \n");
    printf("*************************************\n");
    FILE *fp_lib;
    fp_lib=fopen("Library/library.txt","r");
    if (fp_lib == NULL)
    {
        printf("正在创建音乐库文件。\n");
        createLibrary();
        printf("创建完成！\n");
    }
    FILE *fp_log;
    fp_log=fopen("listCatalog.txt","r");
    if (fp_log==NULL)
    {
        printf("正在创建歌单。\n");
        s=createFromLib();

    }
    
    readListsFromFile(&catalog);
    printf("歌单列表如下:\n");
    printListCatalog(catalog);
    getchar();
    free(catalog);
    return 0;

}


