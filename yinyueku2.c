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
    int id;
    int count;
	char name[50];
	char singer[50];
	char address[1024];
	struct song *next;
} Song;

#endif
void menu1()
{
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            1.添加歌曲\n");
    printf("            2.删除歌曲\n");
    printf("            3.修改歌曲\n");
    printf("            4.查看歌曲单\n");
    printf("            0.返回主菜单\n");
    printf("*************************************\n");
    printf("请输入您的选择：[0-4]\n");
}

struct song * create()
{
    struct song *head=NULL,*p1,*rear=NULL;
    p1=(struct song *)malloc(LEN);
    FILE *fp1;
    fp1=fopen("song.txt","r");
    if(fp1==NULL)
    {
        puts("无法打开文件。");
        exit(0);
    }
    while (fscanf(fp1,"%d%s%s",&p1->num,p1->name,p1->singer)!=EOF)
    {
        if (head==NULL)
        {
            head=p1;
            rear=p1;
        }
        else
        {
            rear->next=p1;
            rear=p1;
        }
        rear=p1;
        p1=(struct song*)malloc(LEN);
    }
    rear->next=head;
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
        case 1:printf("请输入要查找的编号");
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

        case 2:printf("请输入要查找的歌名");
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

        case 3:printf("请输入要查找的歌手");
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
        default:printf("\n 输入错误，请重新输入！\n");
        };
}*/
void print(struct song *head)
{
    struct song *p;
    p=head;
    if(head!=NULL)
    {
        while(1)
        {
            printf("%d %s %s  \n",p->num,p->name,p->singer);
            p=p->next;
            if (p==head)
            {
                break;
            }
        }
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
        puts("无法打开文件。");
        exit(0);
    }
    if (head!=NULL)
    {
        while(1)
        {
            fprintf(fp2,"%d %s %s\n",p->num,p->name,p->singer);
            p=p->next;
            if (p==head)
            {
                break;
            }
        }
    }
    fclose(fp2);
}

struct song *modify_Node(struct song *head, int x)
{
    struct song *p, *q;
    int found = 0;
    p = head;
    q = NULL;
    if (head!=NULL) 
    {
        while(1)
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
            if (p == head) 
            {
                break;
            }
        }
    }
    if (found == 1) 
    {
        printf("请输入修改后的歌名: ");
        scanf("%s", p->name);
        printf("请输入修改后的歌手: ");
        scanf("%s", p->singer);
        return head;
    } 
    else 
    {
        printf("找不到数据!");
        return head;
    }
}

struct song *Del_Node(struct song *head,int x)
{
    struct song *p,*q;
    int found=0;
    p=head;
    q=NULL;
    if(head!=NULL)
    {
        while(1)
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
            if (p==head)
            {
                break;
            }
        }
    }
    if(found==1)
    {
        if(p==head)
        {
            head=p->next;
            q=p;
            while(q->next!=head)
            {
                q=q->next;
            }
            q->next=head;
        }
        else
        {
            q->next=p->next;
        }
        free(p);
    }
    else
    {
        printf("找不到数据!");
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
    s->next=NULL;
    if (head==NULL)
    {
        head=s;
    }
    else
    {
        while (1) 
        {
            if (p==head||p->num>s->num) 
            {
                break;
            }
            q=p;
            p=p->next;
        }
        if (p==head) 
        {
            s->next=head;
            head=s;
        } else 
        {
            s->next=p;
            q->next=s;
        }
    }
    return head;
}

void search(char *way) 
{
    WIN32_FIND_DATA Data;// 存储文件信息的结构体
    HANDLE hFind;// 查找句柄

    char path[MAX_PATH];// 定义一个字符串数组，用于存储搜索路径
    snprintf(path, sizeof(path), "%s\\*.mp3", way);// 将 \*.mp3 附加到文件夹路径后面

    hFind = FindFirstFile(path, &Data);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("在目录中没有找到MP3文件。\n");
        return;
    }
        FILE *fp1;
        fp1=fopen("list.txt","w");
        FILE *fp2;
        fp2=fopen("song.txt","w");
        int num = 1;
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// 找到文件名的后缀位置
            if (dotPos != NULL) // 删除文件名中的后缀
            {
                *dotPos = '\0';
            }
            printf("找到MP3文件: %s.mp3\n", Data.cFileName);
            fprintf(fp1, "%d %s\n", num++, Data.cFileName);
            fprintf(fp2, "%d %s\n", num++, Data.cFileName); // 写入序号和文件名到 song.txt
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// 关闭查找句柄
        fclose(fp1);
        fclose(fp2);
}

void paixu(struct song *head) 
{
    struct song *p, *q;
    int x;
    char y[50], z[50];
    p = head;
    if (p != NULL) 
    {
        while(1)
        {
            q = p->next;
            while (q!=head) 
            {
                if (p->num>q->num) 
                {
                    x=p->num;
                    p->num=q->num;
                    q->num=x;
                    strcpy(y, p->name);
                    strcpy(p->name, q->name);
                    strcpy(q->name, y);
                    strcpy(z, p->singer);
                    strcpy(p->singer, q->singer);
                    strcpy(q->singer, z);
            }   
            q=q->next;
        }
        p=p->next;
        if (p==head) 
        {
            break; 
        }
        }
        p = head;
        int i = 1;
        if(p != NULL) 
        {
            while(1)
            {
                p->num=i++;
                p=p->next;
                if (p==head) 
                {
                    break;
                }
            }
        }
    }
}

void read(struct song *head)
{
    FILE *fp = fopen("list.txt", "r");
    if (fp == NULL)
    {
        puts("无法打开 list.txt 文件。");
        return;
    }
    struct song *p, *q;
    p=NULL;
    head = NULL;
    char address[1024];

    while (1)
    {
        p = (struct song *)malloc(LEN);
        if (fscanf(fp, "%d %s %s", &p->num, p->name, p->singer) == EOF)
        {
            free(p);
            break;
        }
        if (head == NULL)
        {
            head = p;
            q = p;
        }
        else
        {
            q->next = p;
            q = p;
        }
    }

    if (q != NULL)
    {
        q->next = head; // 链表成环
    }

    fclose(fp);
}

int main()
{
    int i,j,k;
    char x[20],y[20];
    struct song *h;
    h=NULL;
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            是否为首次开启？\n");
    printf("            1.首次开启\n");
    printf("            2.非首次开启\n");
    printf("            0.返回主菜单\n");
    printf("*************************************\n");
    printf("请输入您的选择：[0-2]\n");
    scanf("%d",&i);
    while (1)
    {
        if(i==1)
        {
            system("cls");
            printf("正在创建音乐库文件。\n");
            char *way = "D:\\code\\C language\\7\\project\\c\\output";// 替换为实际路径
            search(way);// 调用 search 函数找出.mp3文件
            printf("创建完成！");
            h=create();
            paixu(h);
            printf("创建的歌曲单如下:\n");
            print(h);
            break;
        }
        else if(i==2)
        {
            system("cls");
            printf("正在从歌曲单文件读取数据\n");
            h=create();
            paixu(h);
            printf("读取成功!\n");
            printf("歌曲列表如下:\n");
            print(h);
            break;
        }
        else
        {
            printf("\n 输入错误，请重新输入！\n");
        }
    }
    while (1)
    {
        menu1();
        scanf("%d",&j);
        switch (j)
        {
            case 1:printf("请输入需要添加的歌曲（歌名 歌手）:\n");
                scanf("%s%s",&x,&y);
                h=insert_Node(h,x,y);
                paixu(h);
                system("cls");
                save(h);
                system("cls");
                break;
            case 2:printf("请输入需要删除的歌曲（序号）:\n");
                scanf("%d",&k);
                h=Del_Node(h,k);
                paixu(h);
                system("cls");
                save(h);
                break;
            case 3:printf("请输入需要修改的歌曲（序号）:\n");
                scanf("%d",&k);
                h=modify_Node(h,k);
                paixu(h);
                system("cls");
                save(h);
                system("cls");
                break;
            case 4:system("cls");
                printf("歌曲单如下:\n");
                print(h);
                break;
            case 0:return 1;
            default:printf("\n 输入错误，请重新输入！\n");
        };
    }
    return 0;
}
