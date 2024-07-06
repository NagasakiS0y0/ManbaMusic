#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define LEN sizeof(struct song)
#ifndef SONG_H
#define SONG_H

typedef struct song
{
    struct song *prev;
	int num;
    int count;
	char name[50];
	char singer[50];
	char address[1024];
	struct song *next;
} Song;

#endif
void menu1()
{
    int i;
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            1.��Ӹ���\n");
    printf("            2.ɾ������\n");
    printf("            3.�޸ĸ���\n");
    printf("            4.�鿴������\n");
    printf("            0.�������˵�\n");
    printf("*************************************\n");
    printf("����������ѡ��[0-4]\n");
}

struct song * create()
{
    struct song *head=NULL,*p1,*rear=NULL;
    p1=(struct song *)malloc(LEN);
    FILE *fp1;
    fp1=fopen("song.txt","r");
    if(fp1==NULL)
    {
        puts("�޷����ļ���");
        exit(0);
    }
    while (fscanf(fp1,"%d%s%s",&p1->num,p1->name,p1->singer)!=EOF)
    {
        if (head==NULL)
        {
            head=p1;
        }
        else
        {
            rear->next=p1;
        }
        rear=p1;
        p1=(struct song*)malloc(LEN);
    }
    rear->next=NULL;
    fclose(fp1);
    return(head);
}

/*void search(struct song *head)
{
    struct song *p;
    p=head;
    int j=0,i=0;
    char x[20],y[20];
        
    scanf("%d",&j);
    switch (j)
    {
        case 1:printf("������Ҫ���ҵı��");
                scanf("%d",&i);
                while(p!=NULL)
                {
                    if(p->num==i)
                    {
                        printf("%d %s %s\n",p->num,p->name,p->singer);
                    }
                    p=p->next;
                }
                   break;

        case 2:printf("������Ҫ���ҵĸ���");
                scanf("%s",&x);
                while(p!=NULL)
                {
                    if(strcmp(p->name,x)==0)
                    {
                        printf("%d %s %s\n",p->num,p->name,p->singer);
                    }
                    p=p->next;
                }
                break;

        case 3:printf("������Ҫ���ҵĸ���");
                scanf("%s",&y);
                while(p!=NULL)
                {
                    if(strcmp(p->singer,y)==0)
                    {
                        printf("%d %s %s\n",p->num,p->name,p->singer);
                    }
                    p=p->next;
                }
                break;
        case 0:return 1;
        default:printf("\n ����������������룡\n");
        };
}*/
void print(struct song *head)
{
    struct song *p;
    p=head;
    while(p!=NULL)
    {
        printf("%d %s %s  \n",p->num,p->name,p->singer);
        p=p->next;
    }
    printf("\n");
}

void save(struct song *head)
{
    struct song *p;
    p=head;
    FILE *fp2;
    fp2=fopen("song.txt","w");
    if(fp2==NULL)
    {
        puts("�޷����ļ���");
        exit(0);
    }
    while (p!=NULL)
    {
        fprintf(fp2,"%d %s %s\n",p->num,p->name,p->singer);
        p=p->next;
    }
    fclose(fp2);
}

struct song *modify_Node(struct song *head, int x)
{
    struct song *p, *q;
    int found = 0;
    p = head;
    q = NULL;
    while (p != NULL) 
    {
        if (p->num == x) 
        {
            found = 1;
            break;
        } 
        else 
        {
            q = p;
            p = p->next;
        }
    }
    if (found == 1) 
    {
        printf("�������޸ĺ�ĸ���: ");
        scanf("%s", p->name);
        printf("�������޸ĺ�ĸ���: ");
        scanf("%s", p->singer);
        return head;
    } 
    else 
    {
        printf("�Ҳ�������!");
        return head;
    }
}

struct song *Del_Node(struct song *head,int x)
{
    struct song *p,*q;
    int found=0;
    p=head;
    q=NULL;
    while(p!=NULL)
    {
        if(p->num==x)
        {
            found=1;
            break;
        }
        else
        {
            q=p;
            p=p->next;
        }
    }
    if(found==1)
    {
        if(p==head)
        {
            head=p->next;
        }
        else
        {
            q->next=p->next;
            free(p);
        }
    }
    else
    {
        printf("�Ҳ�������!");
    }
    return head;
}

struct song *insert_Node (struct song *head ,char y[20],char z[20])
{
    struct song *p,*q,*s;
    p=head;q=NULL;
    s=(struct song*)malloc(LEN);
    strcpy(s->name,y);
    strcpy(s->singer,z);
    if (head==NULL)
    {
        head=s;
        s->next=NULL;
    }
    else
    {
        while ((p!=NULL)&&(p->num<s->num))
        {
            q=p;
            p=p->next;
        }
        if(p==head)
        {
            s->next=p;
            head=s;
        }
        else
        {
            s->next=p;
            q->next=s;
        } 
    }
    return(head);
}

void search(char *way) 
{
    WIN32_FIND_DATA Data;// �洢�ļ���Ϣ�Ľṹ��
    HANDLE hFind;// ���Ҿ��

    char path[MAX_PATH];// ����һ���ַ������飬���ڴ洢����·��
    snprintf(path, sizeof(path), "%s\\*.mp3", way);// �� \*.mp3 ���ӵ��ļ���·������

    hFind = FindFirstFile(path, &Data);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("��Ŀ¼��û���ҵ�MP3�ļ���\n");
        return;
    } 
    else 
    {
        FILE *fp = fopen("song.txt", "w");
        int num = 1;
        do {
            char *dotPos = strrchr(Data.cFileName, '.');// �ҵ��ļ����ĺ�׺λ��
            if (dotPos != NULL) // ɾ���ļ����еĺ�׺
            {
                *dotPos = '\0';
            }
            printf("�ҵ�MP3�ļ�: %s.mp3\n", Data.cFileName);
            fprintf(fp, "%d %s\n", num++, Data.cFileName); // д����ź��ļ����� song.txt
        } 
        while (FindNextFile(hFind, &Data) != 0);
        FindClose(hFind);// �رղ��Ҿ��
        fclose(fp);
    }
}

void paixu(struct song *head) 
{
    struct song *p, *q;
    int x;
    char y[50], z[50];
    p = head;
    while (p != NULL) 
    {
        q = p->next;
        while (q != NULL) 
        {
            if (p->num > q->num) 
            {
                x = p->num;
                p->num = q->num;
                q->num = x;
                strcpy(y, p->name);
                strcpy(p->name, q->name);
                strcpy(q->name, y);
                strcpy(z, p->singer);
                strcpy(p->singer, q->singer);
                strcpy(q->singer, z);
            }
            q = q->next;
        }
        p = p->next;
    }
    p = head;
    int i = 1;
    while (p != NULL) 
    {
        p->num=i++;
        p=p->next;
    }
}

int main()
{
    int i,j;
    char x[20],y[20];
    struct song *h;
    printf("���ļ���ȡ����\n");
    char *way = "D:\\code\\C language\\7\\project\\c\\output";// �滻Ϊʵ��·��
    search(way);// ���� search �����ҳ�.mp3�ļ�
    h=create();
    printf("�����ĸ���������:\n");
    print(h);
    while (1)
    {
        menu1();
        scanf("%d",&i);
        switch (i)
        {
            case 1:printf("��������Ҫ��ӵĸ��������� ���֣�:\n");
                scanf("%s%s",&x,&y);
                h=insert_Node(h,x,y);
                paixu(h);
                system("cls");
                save(h);
                system("cls");
                break;
            case 2:printf("��������Ҫɾ���ĸ�������ţ�:\n");
                scanf("%d",&j);
                h=Del_Node(h,j);
                paixu(h);
                system("cls");
                save(h);
                break;
            case 3:printf("��������Ҫ�޸ĵĸ�������ţ�:\n");
                scanf("%d",&j);
                h=modify_Node(h,j);
                paixu(h);
                system("cls");
                save(h);
                system("cls");
                break;
            case 4:system("cls");
                printf("����������:\n");
                print(h);
                break;
            case 0:return 1;
            default:printf("\n ����������������룡\n");
        };
    }
    return 0;
}
