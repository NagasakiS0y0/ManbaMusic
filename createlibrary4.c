#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h> // For time and rand functions
#include "song.h"
void scanAndSaveWavFiles(const char *directoryPath);
void scanAndSaveMP3Files(const char *directoryPath);
void createLibrary();
char a[1024];
int num,id;

int generateRandomID() {
    // Seed the random number generator
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    return rand() % 9000 + 1000; // Generates a 4-digit number between 1000 and 9999
}

void scanAndSaveWavFiles(const char *directoryPath) 
{
    WIN32_FIND_DATA Data;// 存储文件信息的结构体
    HANDLE hFind;// 查找句柄
    int id1=generateRandomID();
    int count=0;
    int num1=1;
    char Path[1024];// 定义一个字符串数组，用于存储搜索路径
    snprintf(Path, sizeof(Path), "%s\\*.wav", directoryPath);// 将 \*.mp3 附加到文件夹路径后面
    printf("正在搜索wav文件\n");
    hFind = FindFirstFile(Path, &Data);
    if (hFind == INVALID_HANDLE_VALUE)// 如果找不到文件，则返回
    {
        return;
    }
        FILE *fp1;
        FILE *fp2;
        fp1=fopen("Library/library.txt","w");
        fp2=fopen("List/library.txt","w");
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// 找到文件名的后缀位置
            if (dotPos != NULL) // 删除文件名中的后缀
            {
                *dotPos = '\0';// 将点号替换为空字符
            }
            printf("找到wav文件: %s.wav\n", Data.cFileName);
            
            fprintf(fp1, "%d %d %d %s %s/%s.wav\n",num1 , id1, count, Data.cFileName, directoryPath,Data.cFileName);
            fprintf(fp2, "%d %d %s %s/%s.wav\n",num1++ , id1++, Data.cFileName, directoryPath,Data.cFileName);
            num=num1;
            id=id1;
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// 关闭查找句柄
        fclose(fp1);
        fclose(fp2);
}

void scanAndSaveMP3Files(const char *directoryPath) 
{
    WIN32_FIND_DATA Data;// 存储文件信息的结构体
    HANDLE hFind;// 查找句柄
    int count=0;
    int num2=num;
    int id2=id;
    char Path[1024];// 定义一个字符串数组，用于存储搜索路径
    snprintf(Path, sizeof(Path), "%s\\*.mp3", directoryPath);// 将 \*.mp3 附加到文件夹路径后面
    printf("正在搜索mp3文件\n");
    hFind = FindFirstFile(Path, &Data);

    if (hFind == INVALID_HANDLE_VALUE)// 如果找不到文件，则返回
    {
        return;
    }
        FILE *fp1;
        FILE *fp2;
        fp1=fopen("Library/library.txt","a");
        fp2=fopen("List/library.txt","a");
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// 找到文件名的后缀位置
            if (dotPos != NULL) // 删除文件名中的后缀
            {
                *dotPos = '\0';// 将点号替换为空字符
            }
            printf("找到MP3文件: %s.mp3\n", Data.cFileName);
            fprintf(fp1, "%d %d %d %s %s/%s.mp3\n",num2 , id2, count, Data.cFileName, directoryPath,Data.cFileName);
            fprintf(fp2, "%d %d %s %s/%s.mp3\n",num2++ , id2++, Data.cFileName, directoryPath,Data.cFileName);
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// 关闭查找句柄
        fclose(fp1);
        fclose(fp2);
}

void tihuan() 
{
    FILE *fp1;
    FILE *fp2;
    char ch;

    // 打开文件用于读取
    fp1 = fopen("Library/library.txt", "r");
    if (fp1 == NULL) {
        printf("无法打开文件 %s\n", "library.txt");
        return;
    }

    // 创建临时文件用于写入
    fp2 = fopen("Library/temp.txt", "w");
    if (fp2 == NULL) 
    {
        printf("无法创建临时文件\n");
        fclose(fp1);
        return;
    }

    // 读取原文件内容，并进行替换，然后写入临时文件
    while ((ch = fgetc(fp1)) != EOF) {
        if (ch == '\\') {
            fputc('/', fp2);
        } else {
            fputc(ch, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("Library/library.txt");
    rename("Library/temp.txt", "Library/library.txt");
}

void createLibrary() 
{

    char directoryPath[256];
    printf("请输入要扫描的文件夹路径: ");
    fgets(directoryPath, sizeof(directoryPath), stdin);// 读取输入
    strcpy(a, directoryPath);
    directoryPath[strcspn(directoryPath, "\n")] = 0;// 移除换行符
    FILE *fp = fopen("Library/library.txt", "w");
    if (fp != NULL)
    {
        fclose(fp);
    }
    scanAndSaveWavFiles(directoryPath);// 扫描并保存.wav文件
    scanAndSaveMP3Files(directoryPath);// 扫描并保存.mp3文件
    printf("扫描完成，信息已保存到library.txt。\n");
}

