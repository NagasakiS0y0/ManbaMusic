#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "song.h"

void searchmenu();    //�����˵�
void print(struct song *head);  //����赥
void print2(struct song *head);
void save(struct song *head);   //����赥
Song *search(struct song *head,int l);   //��������
int getLength(struct song *head);   //��ȡ�赥����
struct song *createFromLib_list();  //��ȡ����
struct song *createTempList(Song *lib);   //������ʱ�赥


void createList_zk()
{
    Song *lib = createFromLib_list();
    print(lib);
    Song *list = createTempList(lib);
    print2(list);
    save(list);
}

struct song *createFromLib_list()//    ��ȡ�ļ�
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

struct song *createTempList(Song *lib)
{
    struct song *head = NULL, *p1, *rear = NULL;
    int flag = 1;
    
    while(flag){
        Song *cache = search(lib, getLength(lib));
        if(cache == NULL){
            flag = 0;
        } else {
            int same = 0;
            Song *p2;
            for (p2 = head; p2 != NULL; p2 = p2->next){
                if (p2->id == cache->id){
                    MessageBox(NULL, "�����Ѵ���", "����", MB_OK);
                    same = 1;
                    break;
                }
            }
            if(same == 1){
                continue;
            }
            p1 = (struct song*)malloc(sizeof(struct song));
            p1->num = cache->num;
            p1->id = cache->id;
            p1->count = cache->count;
            strcpy(p1->name, cache->name);
            strcpy(p1->address, cache->address);
            p1->next = NULL;
            p1->prev = rear; // ����ǰ��ָ��
            if(head == NULL){ // ����Ϊ��
                head = p1;
                rear = p1;
            } else {
                rear->next = p1; // ����ǰһ���ڵ�ĺ��ָ��
                rear = p1;
            }
        }
    }

    // ����ѭ������
    if (rear != NULL) {
        rear->next = head; // β�ڵ�ָ��ͷ�ڵ�
        head->prev = rear; // ͷ�ڵ��ǰ��ָ��ָ��β�ڵ�
    }

    int count = 1;
    struct song *p = head;
    do { // ʹ��do-whileѭ��ȷ������ִ��һ��
        p->num=count;
        count++;
        p = p->next; // �ƶ�����һ���ڵ�
    } while (p != head); // ��p�ٴλص�ͷ�ڵ�ʱ������ѭ��
    return head;
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

void print2(struct song *head)   // ����赥
{
    struct song *p;
    if (head == NULL) { // ��������Ƿ�Ϊ��
        printf("����Ϊ�ա�\n");
        return;
    }

    p = head;
    do { // ʹ��do-whileѭ��ȷ������ִ��һ��
        printf("%d  %s\n", p->num, p->name);
        p = p->next; // �ƶ�����һ���ڵ�
    } while (p != head); // ��p�ٴλص�ͷ�ڵ�ʱ������ѭ��

    printf("\n");
}

void save(struct song *head)    //����赥
{
    struct song *p;
    p=head;
    char newName[50];
    char cache[216];
    strcpy(cache,"List/");
    printf("�������µĸ赥����: ");
    scanf("%49s", newName);
    strcat(newName, ".txt"); // ��� .txt ��׺
    strcat(cache,newName);
    FILE *fp2;
    fp2=fopen(cache,"w");
    if(fp2==NULL)   //���ļ�ʧ��
    {
        printf("Cannot open file!\n");
        exit(0);
    }
      //�����赥��д���ļ�
    do{
        fprintf(fp2,"%d %d %s %s\n",p->num,p->id,p->name,p->address);
        p=p->next;
    }while(p!=head);
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
        system("cls");
        print(head);
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
    printf("*    ��Ӹ����˵�              *\n");
    printf("*    1. ������������         *\n");
    printf("*    2. ���������            *\n");
    printf("*    0. �������˵�             *\n");
    printf("*******************************\n");
    printf("��ѡ��������ʽ��[0-2] > ");
}
