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
        printf("δ��⵽���ֿ⣬�����赥ʧ��!\n");
        fclose(fp1);return; 
    }
    while (1) 
    {
        if (strlen(listName) > 50) 
        {
            printf("�赥���ƹ��������������룡\n");
            continue;
        }
        else 
        {
            FILE *fp2=fopen(listName,"w");
            printf("�赥�����ɹ���\n");
            break;
        }
    }
    FILE *fp2=fopen("listCatalog.txt","w");
    FILE *fp3=fopen(listName,"r");
    int num=1;
    WIN32_FIND_DATA Data;// �洢�ļ���Ϣ�Ľṹ��
    HANDLE hFind;// ���Ҿ��
    char Path[1024];
    char address[1024];
    snprintf(Path, sizeof(Path), "%s\\*.txt", a);// �� \*.txt ���ӵ��ļ���·������
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
        printf("δ��⵽�赥!\n");
        fclose(fp1);return; 
    }
    // ��ȡ�赥�ļ�
    fclose(fp1);
}

/*void createfolder()//������Ÿ赥���ļ���
{
    char *folderPath[1024];
    printf("������Ҫ�������ļ���·��: ");
    fgets(folderPath, sizeof(folderPath), stdin);
    if (CreateDirectory(folderPath, NULL) != 0) 
    {
        printf("Ŀ¼�Ѵ���: %s\n", folderPath);
    } else {
        perror("�޷�����Ŀ¼");
        return 1;
    }
    return 0;
}*/
void scantxtFiles() 
{
    int num3=1;
    WIN32_FIND_DATA Data;// �洢�ļ���Ϣ�Ľṹ��
    HANDLE hFind;// ���Ҿ��
    char Path[1024];// ����һ���ַ������飬���ڴ洢����·��
    snprintf(Path, sizeof(Path), "%s\\*.txt", "List");// �� \*.txt ���ӵ��ļ���·������
    //printf("��������txt�ļ�\n");
    hFind = FindFirstFile(Path, &Data);
    if (hFind == INVALID_HANDLE_VALUE)// ����Ҳ����ļ����򷵻�
    {
        printf("��Ŀ¼��û���ҵ��赥�ļ���\n");
        return;
    }
        FILE *fp_ca;
        fp_ca=fopen("listCatalog.txt","w");
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// �ҵ��ļ����ĺ�׺λ��
            if (dotPos != NULL) // ɾ���ļ����еĺ�׺
            {
                *dotPos = '\0';// ������滻Ϊ���ַ�
            }
            printf("�ҵ��赥�ļ�: %s.txt\n", Data.cFileName);
            fprintf(fp_ca, "%d %s %s/%s.txt\n",num3++ ,Data.cFileName, "List",Data.cFileName);
            num=num3;
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// �رղ��Ҿ��
}

/*int main()
{
    int i;
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            1.�����赥\n");
    printf("            2.��ȡ�赥\n");
    printf("            0.����\n");
    printf("*************************************\n");
    printf("����������ѡ��[0-2]\n");
    scanf("%d", &i);
    while (1)
    {
        if (i == 1)
        {
            char listName[50];
            printf("������赥���ƣ�");
            scanf("%s.txt", listName);
            createList(listName);

            break;
        }
        else if (i == 2)
        {
            char listName[50];
            printf("������赥���ƣ�");
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
            printf("\n ����������������룡\n");
        }
    }
    return 0;
}*/
