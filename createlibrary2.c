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
    if ((dir = opendir(directoryPath)) != NULL)// ��Ŀ¼
     {
        int num = 1; // �������
        while ((ent = readdir(dir)) != NULL) // ��ȡĿ¼�е��ļ�
        {
            if (strstr(ent->d_name, ".wav") != NULL) // �ж��Ƿ�Ϊ.wav�ļ�
            {
                char filePath[256];
                snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, ent->d_name);
                struct stat st;// ��ȡ�ļ���Ϣ
                if (stat(filePath, &st) == 0 && S_ISREG(st.st_mode)) // �ж��Ƿ�Ϊ�����ļ�
                {
                    Song song;
                    song.num = num++;
                    song.id = 1;
                    song.count = 0;
                    strncpy(song.name, ent->d_name, sizeof(song.name) - 1);
                    strncpy(song.address, filePath, sizeof(song.address) - 1);
                    song.address[sizeof(song.address) - 1] = '\0';// ȷ���ַ�����null��β

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
        closedir(dir);// �ر�Ŀ¼
    } else
    {
        perror("Could not open directory");// ��ӡ������Ϣ
        return;
    }
}*/

void scanAndSaveWavFiles(const char *directoryPath) 
{
    struct song *h;
    h = NULL;
    WIN32_FIND_DATA Data;// �洢�ļ���Ϣ�Ľṹ��
    HANDLE hFind;// ���Ҿ��
    int num=1;
    int id=1000;
    int count=0;
    char Path[1024];// ����һ���ַ������飬���ڴ洢����·��
    snprintf(Path, sizeof(Path), "%s\\*.wav", directoryPath);// �� \*.mp3 ���ӵ��ļ���·������
    printf("��������wav�ļ�\n");
    hFind = FindFirstFile(Path, &Data);

    if (hFind == INVALID_HANDLE_VALUE)// ����Ҳ����ļ����򷵻�
    {
        printf("��Ŀ¼��û���ҵ�wav�ļ���\n");
        return;
    }
        FILE *fp1;
        fp1=fopen("library.txt","w");
        char address[1024];
        strcpy(address, Path);
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// �ҵ��ļ����ĺ�׺λ��
            if (dotPos != NULL) // ɾ���ļ����еĺ�׺
            {
                *dotPos = '\0';// ������滻Ϊ���ַ�
            }
            printf("�ҵ�wav�ļ�: %s.wav\n", Data.cFileName);
            fprintf(fp1, "%d %d %d %s %s\n",num++ , id++, count, Data.cFileName, address);
            
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// �رղ��Ҿ��
        fclose(fp1);
}

void scanAndSaveMP3Files(const char *directoryPath) 
{
    struct song *h;
    h = NULL;
    WIN32_FIND_DATA Data;// �洢�ļ���Ϣ�Ľṹ��
    HANDLE hFind;// ���Ҿ��
    int num=1;
    int id=1000;
    int count=0;
    char Path[1024];// ����һ���ַ������飬���ڴ洢����·��
    snprintf(Path, sizeof(Path), "%s\\*.mp3", directoryPath);// �� \*.mp3 ���ӵ��ļ���·������
    printf("��������mp3�ļ�\n");
    hFind = FindFirstFile(Path, &Data);

    if (hFind == INVALID_HANDLE_VALUE)// ����Ҳ����ļ����򷵻�
    {
        printf("��Ŀ¼��û���ҵ�MP3�ļ���\n");
        return;
    }
        FILE *fp1;
        fp1=fopen("library.txt","w");
        char address[1024];
        strcpy(address, Path);
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// �ҵ��ļ����ĺ�׺λ��
            if (dotPos != NULL) // ɾ���ļ����еĺ�׺
            {
                *dotPos = '\0';// ������滻Ϊ���ַ�
            }
            printf("�ҵ�MP3�ļ�: %s.mp3\n", Data.cFileName);
            fprintf(fp1, "%d %d %d %s %s\n",num++ , id++, count, Data.cFileName, address);
            
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// �رղ��Ҿ��
        fclose(fp1);
}


void createLibrary() 
{

    char directoryPath[256];
    printf("������Ҫɨ����ļ���·��: ");
    fgets(directoryPath, sizeof(directoryPath), stdin);
    directoryPath[strcspn(directoryPath, "\n")] = 0; // Remove newline character
    // Clear the library.txt file before writing new data
    FILE *fp = fopen("Library/library.txt", "w");
    if (fp != NULL)
    {
        fclose(fp);
    }
    scanAndSaveWavFiles(directoryPath);// ɨ�貢����.wav�ļ�
    scanAndSaveMP3Files(directoryPath);// ɨ�貢����.mp3�ļ�
    printf("ɨ����ɣ���Ϣ�ѱ��浽library.txt��\n");

}

int main() 
{
    createLibrary();
    return 0;
}