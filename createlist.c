#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "song.h"
#include "createLibrary4.c"
void readList(char listName[50]) // ��ȡ�赥�ļ�
{
    FILE *fp1 = fopen(listName, "r");
    if (fp1 == NULL)
    {
        printf("δ��⵽�赥!\n");
        fclose(fp1);return; 
    }
    fclose(fp1);
}

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
        fclose(fp_ca);
}

