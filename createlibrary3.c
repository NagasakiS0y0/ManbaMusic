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
    int id1=generateRandomID();
    int count=0;
    int num1=1;
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
            fprintf(fp1, "%d %d %d %s %s\n",num1++ , id1++, count, Data.cFileName, address);
            num=num1;
            id=id1;
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
    int count=0;
    int num2=num;
    int id2=id;
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
        fp1=fopen("library.txt","a");
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
            fprintf(fp1, "%d %d %d %s %s\n",num2++ , id2++, count, Data.cFileName, address);
            
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// �رղ��Ҿ��
        fclose(fp1);
}

void tihuan() 
{
    FILE *fp1;
    FILE *fp2;
    char ch;

    // ���ļ����ڶ�ȡ
    fp1 = fopen("library.txt", "r");
    if (fp1 == NULL) {
        printf("�޷����ļ� %s\n", "library.txt");
        return;
    }

    // ������ʱ�ļ�����д��
    fp2 = fopen("temp.txt", "w");
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
    remove("library.txt");
    rename("temp.txt", "library.txt");
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

int main() 
{
    createLibrary();
    tihuan();
    return 0;
}