#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "song.h"
#define LEN sizeof(struct song)    //�赥�ṹ�峤��

void mainmenu();    //���˵�
void searchmenu();    //�����˵�
void print(struct song *head);  //����赥
void save(struct song *head);   //����赥
Song *search(struct song *head,int l);   //��������
int getLength(struct song *head);   //��ȡ�赥����
struct song *createFromLib();  //�����赥
struct song *createList(Song *lib);

int main()
{
    Song *lib = createFromLib();
    print(lib);
    Song *list = createList(lib);
    print(list);
    getch();
    return 0;
}

struct song *createFromLib()//    ��ȡ�ļ�
{
    struct song *libHead=NULL,*p1,*libRear=NULL;//����ͷָ�롢�ֲ�ָ�롢�赥βָ��

    FILE *fp1;
    fp1=fopen("Library/library.txt","r");

    if(fp1==NULL)
    {
        printf("Cannot open file!\n");
        exit(0);
    }

    p1=(struct song*)malloc(LEN);//�����½ڵ�

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
        p1=(struct song*)malloc(LEN);//�����½ڵ�
    }
    libRear->next=NULL;//�赥βָ��ָ��NULL
    fclose(fp1);
    int count=1;
    for(p1=libHead;p1!=NULL;p1=p1->next)     //�����赥�����±��
        {
            p1->num=count;
            count++;
        }
    return(libHead);//���ظ赥ͷָ��
}

struct song *createList(Song *lib)//    ��ȡ�ļ�
{
    struct song *head=NULL,*p1,*rear=NULL;//�赥ͷָ�롢�ֲ�ָ�롢�赥βָ��
    
    p1=(struct song*)malloc(LEN);//�����½ڵ�
    if(p1==NULL){
        printf("�ڴ�������\n");
        exit(1);
    }

    Song *cache;
    cache=(struct song*)malloc(LEN);

    while(search(lib,getLength(lib))!=NULL)
    {
        cache=search(lib,getLength(lib));
        p1->num=cache->num;
        p1->id=cache->id;
        p1->count=cache->count;
        strcpy(p1->name,cache->name);
        strcpy(p1->address,cache->address);
        if(head==NULL){//�赥Ϊ��
            head=p1;//�赥ͷָ��ָ���½ڵ�
        }else{
            rear->next=p1;//�赥βָ��ָ���½ڵ�
        }
        rear=p1;
        p1=(struct song*)malloc(LEN);//�����½ڵ�
    }
    rear->next=NULL;//�赥βָ��ָ��NULL
    int count=1;
    for(p1=head;p1!=NULL;p1=p1->next)     //�����赥�����±��
        {
            p1->num=count;
            count++;
        }
    return(head);//���ظ赥ͷָ��
}

void print(struct song *head)   //����赥
{
    struct song *p;
    p=head;
    while(p!=NULL)//�����赥
    {
        printf("%d  %s\n",p->num,p->name);
        p=p->next;
    }
    printf("\n");
}

void save(struct song *head)    //����赥
{
    struct song *p;
    p=head;
    FILE *fp2;
    fp2=fopen("song.txt","w");

    if(fp2==NULL)   //���ļ�ʧ��
    {
        printf("Cannot open file!\n");
        exit(0);
    }
    while(p!=NULL)  //�����赥��д���ļ�
    {
        fprintf(fp2,"%d  %s  %s\n",p->num,p->name);
        p=p->next;
    }
    fclose(fp2);    //�ر��ļ�
}


Song *search(struct song *head, int l) // ���Ҹ���
{
    int flag, m;
    char y[20];
    struct song *p;
    int found;

    while (1)
    {
        searchmenu();
        scanf("%d", &flag);
        switch (flag)
        {
            case 0:
            {
                printf("�������˵�\n");
                return NULL;
                break;
            }
            case 1:
            {
                printf("������Ҫ�����ĸ������\n");
                scanf("%d", &m);
                if (m < 1 || m > l) // �ж������Ƿ�Ϸ�
                {
                    printf("�����������������\n");
                    continue;
                }
                found = 0;
                for (p = head; p != NULL; p = p->next)
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
                if (!found) 
                {
                    printf("δ�ҵ�ƥ��ĸ���\n");
                    continue;
                }
                break;
            }
            case 2:
            {
                printf("������Ҫ�����ĸ�����\n");
                scanf("%s", y);
                found = 0;
                for (p = head; p != NULL; p = p->next)
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
                if (!found)
                {
                    printf("δ�ҵ�ƥ��ĸ���\n");
                    continue;
                }
                break;
            }
            default:
            {
                printf("�����������������\n");
                continue;
            }
        }
        break;
    }
}

int getLength(struct song *head)//��ȡ�赥����
{
    int len=0;
    struct song *l;
    l=head;
    while(l!=NULL)      //�����赥
    {
        len++;
        l=l->next;
    }
    return len;
}

void searchmenu()//�����˵�
{
    printf("*******************************\n");
    printf("*    ���������˵�              *\n");
    printf("*    1. �������������         *\n");
    printf("*    2. ����������            *\n");
    printf("*    3. ����������            *\n");
    printf("*    0. �������˵�             *\n");
    printf("*******************************\n");
    printf("��ѡ��������ʽ��[0-3] > ");
}


