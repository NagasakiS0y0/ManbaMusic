#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h> 
#include "createLibrary.c"
//#include "interface.c"
#include "song.h"

int main()
{
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("                             \n");
    printf("           man what can i say\n");
    printf("                             \n");
    printf("                             \n");
    printf("*************************************\n");
    printf("请输入您的选择：[0-2]\n");
    FILE *fp;
    fp=fopen("Library/library.txt","r");
    if (fp == NULL)
    {
        printf("正在创建音乐库文件。\n");
        createLibrary();
        printf("创建完成！\n");
    }
    printf("歌曲列表如下:\n");
    
}


