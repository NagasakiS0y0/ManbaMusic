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
    printf("����������ѡ��[0-2]\n");
    FILE *fp;
    fp=fopen("Library/library.txt","r");
    if (fp == NULL)
    {
        printf("���ڴ������ֿ��ļ���\n");
        createLibrary();
        printf("������ɣ�\n");
    }
    printf("�����б�����:\n");
    
}


