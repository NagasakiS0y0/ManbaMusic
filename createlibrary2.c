#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h> // For time and rand functions
#include "song.h"
int generateRandomID();
void scanAndSaveWavFiles(const char *directoryPath);
void scanAndSaveMP3Files(const char *directoryPath);
void createLibrary();

/*int generateRandomID() {
    // Seed the random number generator
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    return rand() % 9000 + 1000; // Generates a 4-digit number between 1000 and 9999
}
*/

/*void generateRandomID(struct song *head) 
{
    int id, repeat;
    struct song *q;
    srand(time(0));
    while(1)
    {
        repeat = 0;
        id = rand() % 9000 + 1000;
        q = head;
        if (q != NULL)
            {
                do
                {
                    if (q->id == id)
                    {
                        repeat = 1;
                        break;
                    }
                    q = q->next;
                } while (q != head);
            }
    }
    return id; // Generates a 4-digit number between 1000 and 9999
}*/

/*void scanAndSaveWavFiles(const char *directoryPath) 
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directoryPath)) != NULL)// 打开目录
     {
        int num = 1; // 歌曲编号
        while ((ent = readdir(dir)) != NULL) // 读取目录中的文件
        {
            if (strstr(ent->d_name, ".wav") != NULL) // 判断是否为.wav文件
            {
                char filePath[256];
                snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, ent->d_name);
                struct stat st;// 获取文件信息
                if (stat(filePath, &st) == 0 && S_ISREG(st.st_mode)) // 判断是否为常规文件
                {
                    Song song;
                    song.num = num++;
                    song.id = 1;
                    song.count = 0;
                    strncpy(song.name, ent->d_name, sizeof(song.name) - 1);
                    strncpy(song.address, filePath, sizeof(song.address) - 1);
                    song.address[sizeof(song.address) - 1] = '\0';// 确保字符串以null结尾

                    // Write to library.txt
                    FILE *fp = fopen("Library/library.txt", "a");
                    if (fp != NULL) 
                    {
                        fprintf(fp, "%d %d %d %s %s\n", song.num, song.id, song.count, song.name, song.address);
                        fclose(fp);
                    }
                }
            }
        }
        closedir(dir);// 关闭目录
    } else
    {
        perror("Could not open directory");// 打印错误信息
        return;
    }
}*/

void scanAndSaveWavFiles(const char *directoryPath) 
{
    struct song *h;
    h = NULL;
    WIN32_FIND_DATA Data;// 存储文件信息的结构体
    HANDLE hFind;// 查找句柄
    int num=1;
    int id=1000;
    int count=0;
    char Path[1024];// 定义一个字符串数组，用于存储搜索路径
    snprintf(Path, sizeof(Path), "%s\\*.wav", directoryPath);// 将 \*.mp3 附加到文件夹路径后面
    printf("正在搜索wav文件\n");
    hFind = FindFirstFile(Path, &Data);

    if (hFind == INVALID_HANDLE_VALUE)// 如果找不到文件，则返回
    {
        printf("在目录中没有找到wav文件。\n");
        return;
    }
        FILE *fp1;
        fp1=fopen("library.txt","w");
        char address[1024];
        strcpy(address, Path);
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// 找到文件名的后缀位置
            if (dotPos != NULL) // 删除文件名中的后缀
            {
                *dotPos = '\0';// 将点号替换为空字符
            }
            printf("找到wav文件: %s.wav\n", Data.cFileName);
            fprintf(fp1, "%d %d %d %s %s\n",num++ , id++, count, Data.cFileName, address);
            
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// 关闭查找句柄
        fclose(fp1);
}

void scanAndSaveMP3Files(const char *directoryPath) 
{
    struct song *h;
    h = NULL;
    WIN32_FIND_DATA Data;// 存储文件信息的结构体
    HANDLE hFind;// 查找句柄
    int num=1;
    int id=1000;
    int count=0;
    char Path[1024];// 定义一个字符串数组，用于存储搜索路径
    snprintf(Path, sizeof(Path), "%s\\*.mp3", directoryPath);// 将 \*.mp3 附加到文件夹路径后面
    printf("正在搜索mp3文件\n");
    hFind = FindFirstFile(Path, &Data);

    if (hFind == INVALID_HANDLE_VALUE)// 如果找不到文件，则返回
    {
        printf("在目录中没有找到MP3文件。\n");
        return;
    }
        FILE *fp1;
        fp1=fopen("library.txt","w");
        char address[1024];
        strcpy(address, Path);
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// 找到文件名的后缀位置
            if (dotPos != NULL) // 删除文件名中的后缀
            {
                *dotPos = '\0';// 将点号替换为空字符
            }
            printf("找到MP3文件: %s.mp3\n", Data.cFileName);
            fprintf(fp1, "%d %d %d %s %s\n",num++ , id++, count, Data.cFileName, address);
            
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// 关闭查找句柄
        fclose(fp1);
}


void createLibrary() 
{

    char directoryPath[256];
    printf("请输入要扫描的文件夹路径: ");
    fgets(directoryPath, sizeof(directoryPath), stdin);
    directoryPath[strcspn(directoryPath, "\n")] = 0; // Remove newline character
    // Clear the library.txt file before writing new data
    FILE *fp = fopen("Library/library.txt", "w");
    if (fp != NULL)
    {
        fclose(fp);
    }
    scanAndSaveWavFiles(directoryPath);// 扫描并保存.wav文件
    scanAndSaveMP3Files(directoryPath);// 扫描并保存.mp3文件
    printf("扫描完成，信息已保存到library.txt。\n");

}

int main() 
{
    createLibrary();
    return 0;
}