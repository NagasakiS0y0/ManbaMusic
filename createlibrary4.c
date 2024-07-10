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
    WIN32_FIND_DATA Data;// �洢�ļ���Ϣ�Ľṹ��
    HANDLE hFind;// ���Ҿ��
    int id1=generateRandomID();
    int count=0;
    int num1=1;
    char Path[1024];// ����һ���ַ������飬���ڴ洢����·��
    snprintf(Path, sizeof(Path), "%s\\*.wav", directoryPath);// �� \*.mp3 ���ӵ��ļ���·������
    printf("��������wav�ļ�\n");
    hFind = FindFirstFile(Path, &Data);
    if (hFind == INVALID_HANDLE_VALUE)// ����Ҳ����ļ����򷵻�
    {
        return;
    }
        FILE *fp1;
        FILE *fp2;
        fp1=fopen("Library/library.txt","w");
        fp2=fopen("List/library.txt","w");
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// �ҵ��ļ����ĺ�׺λ��
            if (dotPos != NULL) // ɾ���ļ����еĺ�׺
            {
                *dotPos = '\0';// ������滻Ϊ���ַ�
            }
            printf("�ҵ�wav�ļ�: %s.wav\n", Data.cFileName);
            
            fprintf(fp1, "%d %d %d %s %s/%s.wav\n",num1 , id1, count, Data.cFileName, directoryPath,Data.cFileName);
            fprintf(fp2, "%d %d %s %s/%s.wav\n",num1++ , id1++, Data.cFileName, directoryPath,Data.cFileName);
            num=num1;
            id=id1;
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// �رղ��Ҿ��
        fclose(fp1);
        fclose(fp2);
}

void scanAndSaveMP3Files(const char *directoryPath) 
{
    WIN32_FIND_DATA Data;// �洢�ļ���Ϣ�Ľṹ��
    HANDLE hFind;// ���Ҿ��
    int count=0;
    int num2=num;
    int id2=id;
    char Path[1024];// ����һ���ַ������飬���ڴ洢����·��
    snprintf(Path, sizeof(Path), "%s\\*.mp3", directoryPath);// �� \*.mp3 ���ӵ��ļ���·������
    printf("��������mp3�ļ�\n");
    hFind = FindFirstFile(Path, &Data);

    if (hFind == INVALID_HANDLE_VALUE)// ����Ҳ����ļ����򷵻�
    {
        return;
    }
        FILE *fp1;
        FILE *fp2;
        fp1=fopen("Library/library.txt","a");
        fp2=fopen("List/library.txt","a");
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// �ҵ��ļ����ĺ�׺λ��
            if (dotPos != NULL) // ɾ���ļ����еĺ�׺
            {
                *dotPos = '\0';// ������滻Ϊ���ַ�
            }
            printf("�ҵ�MP3�ļ�: %s.mp3\n", Data.cFileName);
            fprintf(fp1, "%d %d %d %s %s/%s.mp3\n",num2 , id2, count, Data.cFileName, directoryPath,Data.cFileName);
            fprintf(fp2, "%d %d %s %s/%s.mp3\n",num2++ , id2++, Data.cFileName, directoryPath,Data.cFileName);
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// �رղ��Ҿ��
        fclose(fp1);
        fclose(fp2);
}

void tihuan() 
{
    FILE *fp1;
    FILE *fp2;
    char ch;

    // ���ļ����ڶ�ȡ
    fp1 = fopen("Library/library.txt", "r");
    if (fp1 == NULL) {
        printf("�޷����ļ� %s\n", "library.txt");
        return;
    }

    // ������ʱ�ļ�����д��
    fp2 = fopen("Library/temp.txt", "w");
    if (fp2 == NULL) 
    {
        printf("�޷�������ʱ�ļ�\n");
        fclose(fp1);
        return;
    }

    // ��ȡԭ�ļ����ݣ��������滻��Ȼ��д����ʱ�ļ�
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
    printf("������Ҫɨ����ļ���·��: ");
    fgets(directoryPath, sizeof(directoryPath), stdin);// ��ȡ����
    strcpy(a, directoryPath);
    directoryPath[strcspn(directoryPath, "\n")] = 0;// �Ƴ����з�
    FILE *fp = fopen("Library/library.txt", "w");
    if (fp != NULL)
    {
        fclose(fp);
    }
    scanAndSaveWavFiles(directoryPath);// ɨ�貢����.wav�ļ�
    scanAndSaveMP3Files(directoryPath);// ɨ�貢����.mp3�ļ�
    printf("ɨ����ɣ���Ϣ�ѱ��浽library.txt��\n");
}

