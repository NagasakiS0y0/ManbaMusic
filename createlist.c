#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "song.h"
#include "createLibrary4.c"
//#include "interface.c"
//char folderPath[1024];


void createList(char listName[50]) 
{
    FILE *fp1 = fopen("Library/library.txt", "r");
    if (fp1 == NULL)
    {
        printf("未检测到音乐库，创建歌单失败!\n");
        fclose(fp1);return; 
    }
    while (1) 
    {
        if (strlen(listName) > 50) 
        {
            printf("歌单名称过长，请重新输入！\n");
            continue;
        }
        else 
        {
            FILE *fp2=fopen(listName,"w");
            printf("歌单创建成功！\n");
            break;
        }
    }
    FILE *fp2=fopen("listCatalog.txt","w");
    FILE *fp3=fopen(listName,"r");
    int num=1;
    WIN32_FIND_DATA Data;// 存储文件信息的结构体
    HANDLE hFind;// 查找句柄
    char Path[1024];
    char address[1024];
    snprintf(Path, sizeof(Path), "%s\\*.txt", a);// 将 \*.txt 附加到文件夹路径后面
    hFind = FindFirstFile(Path, &Data);
    strcpy(address, Path);
    fprintf(fp1,"%d %s %s",num++ ,listName ,address);
    FindClose(hFind);
    fclose(fp1);
    fclose(fp2);
}

void readList(char listName[50]) 
{
    FILE *fp1 = fopen(listName, "r");
    if (fp1 == NULL)
    {
        printf("未检测到歌单!\n");
        fclose(fp1);return; 
    }
    // 读取歌单文件
    fclose(fp1);
}

/*void createfolder()//创建存放歌单的文件夹
{
    char *folderPath[1024];
    printf("请输入要创建的文件夹路径: ");
    fgets(folderPath, sizeof(folderPath), stdin);
    if (CreateDirectory(folderPath, NULL) != 0) 
    {
        printf("目录已创建: %s\n", folderPath);
    } else {
        perror("无法创建目录");
        return 1;
    }
    return 0;
}*/
void scantxtFiles() 
{
    int num3=1;
    WIN32_FIND_DATA Data;// 存储文件信息的结构体
    HANDLE hFind;// 查找句柄
    char Path[1024];// 定义一个字符串数组，用于存储搜索路径
    snprintf(Path, sizeof(Path), "%s\\*.txt", "List");// 将 \*.txt 附加到文件夹路径后面
    //printf("正在搜索txt文件\n");
    hFind = FindFirstFile(Path, &Data);
    if (hFind == INVALID_HANDLE_VALUE)// 如果找不到文件，则返回
    {
        printf("在目录中没有找到歌单文件。\n");
        return;
    }
        FILE *fp_ca;
        fp_ca=fopen("listCatalog.txt","w");
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// 找到文件名的后缀位置
            if (dotPos != NULL) // 删除文件名中的后缀
            {
                *dotPos = '\0';// 将点号替换为空字符
            }
            printf("找到歌单文件: %s.txt\n", Data.cFileName);
            fprintf(fp_ca, "%d %s %s/%s.txt\n",num3++ ,Data.cFileName, "List",Data.cFileName);
            num=num3;
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// 关闭查找句柄
}

/*int main()
{
    int i;
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            1.创建歌单\n");
    printf("            2.读取歌单\n");
    printf("            0.返回\n");
    printf("*************************************\n");
    printf("请输入您的选择：[0-2]\n");
    scanf("%d", &i);
    while (1)
    {
        if (i == 1)
        {
            char listName[50];
            printf("请输入歌单名称：");
            scanf("%s.txt", listName);
            createList(listName);

            break;
        }
        else if (i == 2)
        {
            char listName[50];
            printf("请输入歌单名称：");
            scanf("%s.txt", listName);
            readList(listName);
            break;
        }
        else if (i == 0)
        {
            return 0;
        }
        else
        {
            printf("\n 输入错误，请重新输入！\n");
        }
    }
    return 0;
}*/
