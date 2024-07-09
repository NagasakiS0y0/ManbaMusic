#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h> 
#include "createLibrary.c"
#include "createCatalog.c"
#include "player.c"
//#include "interface.c"
#include "explore_re2.c"
#include "song.h"

void menu_re(Song *s)
{
    int i;
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("                             \n");
    printf("             1.�Ķ�ģʽ       \n");
    printf("             2.̽��ģʽ       \n");
    printf("               0.�˳�        \n");
    printf("                             \n");
    printf("*************************************\n");
    printf("����������ѡ��:   ");
    scanf("%d",&i);
    switch (i)
    {
    case 1:
        recommendation(s);
        player (s);
        break;
    case 2:
       
        break;
    default:
        break;
    }
    free(s);
}

int main()
{
    int i=0;
    List *catalog=NULL;
    Song *s=NULL;
    List *l=NULL;
    FILE *fp_lib;
    fp_lib=fopen("Library/library.txt","r");
    if (fp_lib == NULL)
    {
        printf("���ڴ������ֿ��ļ���\n");
        createLibrary();
        printf("������ɣ�\n");
    }
    fclose(fp_lib);
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("                             \n");
    printf("           1.�赥����ģʽ      \n");
    printf("           2.�����Ƽ�ģʽ      \n");
    printf("               0.�˳�      \n");
    printf("                             \n");
    printf("*************************************\n");
    printf("����������ѡ��:   ");
    scanf("%d",&i);
    switch (i)
    {
    case 2:
        birthSongsFromFile(&s);
        menu_re(s);
        break;
    
    default:
        break;
    }
    return 0;
    

    //��ʾ�赥�б�
    /*FILE *fp_log;
    fp_log=fopen("listCatalog.txt","r");
    if (fp_log==NULL)
    {
        printf("���ڴ����赥��\n");
        s=createFromLib();
        FILE *fp_1;
        fp_1=fopen("List/lib.txt","w");
        while (s!=NULL)
        {
            fprintf(fp_1, "%d %d %s %s\n", &s->num, &s->id, s->name, s->address);
            s=s->next;
        }
         fclose(fp_1);
         fclose(fp_log);
         fp_log=fopen("listCatalog.txt","w");

    }
    
    readListsFromFile(&catalog);
    printf("�赥�б�����:\n");
    printListCatalog(catalog);
    getchar();
    free(catalog);
    return 0;*/

}


