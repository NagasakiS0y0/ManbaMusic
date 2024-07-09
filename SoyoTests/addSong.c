#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <song.h>
#define LEN sizeof(Song)    //�赥�ṹ�峤��



Song *addSongFromLib()
{
    void libPrint(Song *libHead);
    Song *createFromLib();

    int n,m;//����ѡ��˵����жϱ���
    int length=0;
    int found;
    char y[20];//��������
    Song *p;
    Song *h;//�赥ͷָ��
    printf("----�������ȡ����----\n");
    h=createFromLib();//�����赥
    printf("��ȡ�������\n");
    libPrint(h);//����赥

    while(1)//����ѡ��˵�
    {
        printf("*    1. ����������\n");
        printf("*    2. �����������\n");
        printf("*    0. �����ϼ�\n");
        printf("��ѡ���ܣ�[0-2] > ");
        scanf("%d",&n);
        switch (n)
        {
        case 0:
            free(h);
            return;
        case 1:
            {
                printf("������Ҫ�����ĸ������\n");
                scanf("%d", &m);
                found = 0;
                for (p = h; p != NULL; p = p->next)
                {
                    if (p->num == m) // �ж��Ƿ��ҵ��������
                    {
                        if (!found)
                        {
                            printf("Song found!\n");
                            found = 1;
                        }
                        printf("%d  %s\n", p->num, p->name);
                        return p;
                    }
                }
                if (!found) printf("δ�ҵ�ƥ��ĸ���\n");
                break;
            }
        case 2:
            {
                printf("������Ҫ�����ĸ�����\n");
                scanf("%s", y);
                found = 0;
                for (p = h; p != NULL; p = p->next)
                {
                    if (strcmp(p->name, y) == 0) // �ж��Ƿ��ҵ�������
                    {
                        if (!found)
                        {
                            printf("Song found!\n");
                            found = 1;
                        }
                        printf("%d  %s\n", p->num, p->name);
                        return p;
                    }
                }
                if (!found) printf("δ�ҵ�ƥ��ĸ���\n");
                break;
            }
        default:
            printf("������������ԣ�\n");
            continue;
        }
    }
}

void libPrint(Song *libHead)//����赥
{
    Song *p;
    p=libHead;
    while(p!=NULL)
    {
        printf("%d  %s\n",p->num,p->name);
        p=p->next;
    }
    printf("\n");
}

Song *createFromLib()//    ��ȡ�ļ�
{
    Song *libHead=NULL,*p1,*libRear=NULL;//�赥ͷָ�롢�ֲ�ָ�롢�赥βָ��
    FILE *fp1;
    fp1=fopen("Library/library.txt","r");
    if(fp1==NULL)
    {
        printf("Cannot open file!\n");
        return;
    }

    p1=(Song*)malloc(LEN);//�����½ڵ�

    if(p1==NULL){
        printf("�ڴ�������\n");
        exit(1);
    }
    while(fscanf(fp1,"%d%d%d%s%s",&p1->num,&p1->id,&p1->count,p1->name,p1->address)!=EOF)//��ȡ�ļ����ж϶�ȡ�Ƿ����
    {
        if(libHead==NULL){//�赥Ϊ��
            libHead=p1;//�赥ͷָ��ָ���½ڵ�
        }else{
            libRear->next=p1;//�赥βָ��ָ���½ڵ�
        }
        libRear=p1;
        p1=(Song*)malloc(LEN);//�����½ڵ�
    }
    libRear->next=NULL;//�赥βָ��ָ��NULL
    fclose(fp1);
    return(libHead);//���ظ赥ͷָ��
}
