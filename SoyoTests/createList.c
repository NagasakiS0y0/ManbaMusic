#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "song.h"
#define LEN sizeof(struct song)    //歌单结构体长度

void searchmenu();    //搜索菜单
void print(struct song *head);  //输出歌单
void save(struct song *head);   //保存歌单
Song *search(struct song *head,int l);   //搜索歌曲
int getLength(struct song *head);   //获取歌单长度
struct song *createFromLib();  //读取曲库
struct song *createTempList(Song *lib);   //创建临时歌单


int main()
{
    Song *lib = createFromLib();
    print(lib);
    Song *list = createTempList(lib);
    print(list);
    save(list);
    getch();
    return 0;
}


/*
void readSongsFromFile(Song **head,List *l) {
    FILE *fp;
    char newName[50];
    char cache[216];
    strcpy(cache,"List/");
    printf("请输入新的歌单名称: ");
    scanf("%49s", newName);
    strcat(newName, ".txt"); // 添加 .txt 后缀
    strcat(cache,newName);
    FILE *fp2;
    fp2=fopen(cache,"w");
    if(fp2==NULL)   //打开文件失败
    {
        printf("Cannot open file!\n");
        exit(0);
    }
}*/


struct song *createFromLib()//    读取文件
{
    struct song *libHead=NULL,*p1,*libRear=NULL;//曲库头指针、局部指针、歌单尾指针

    FILE *fp1;
    fp1=fopen("Library/library.txt","r");

    if(fp1==NULL)
    {
        printf("Cannot open file!\n");
        exit(0);
    }

    p1=(struct song*)malloc(LEN);//创建新节点

    if(p1==NULL){
        printf("内存分配错误！\n");
        exit(1);
    }
    while(fscanf(fp1,"%d%d%d%s%s",&p1->num,&p1->id,&p1->count,p1->name,p1->address)!=EOF)//读取文件并判断读取是否结束
    {
        if(libHead==NULL){//歌单为空
            libHead=p1;//歌单头指针指向新节点
        }else{
            libRear->next=p1;//歌单尾指针指向新节点
        }
        libRear=p1;
        p1=(struct song*)malloc(LEN);//创建新节点
    }
    libRear->next=NULL;//歌单尾指针指向NULL
    fclose(fp1);
    int count=1;
    for(p1=libHead;p1!=NULL;p1=p1->next)     //遍历歌单，重新编号
        {
            p1->num=count;
            count++;
        }
    return(libHead);//返回歌单头指针
}

struct song *createTempList(Song *lib)//    读取文件
{
    struct song *head=NULL,*p1,*rear=NULL;//歌单头指针、局部指针、歌单尾指针
    int flag=1;
    
    while(flag)
    {
        Song *cache = search(lib, getLength(lib));
        if(cache==NULL)
        {
            // 用户选择了退出，设置标志为0以停止循环
            flag = 0;
        }
        else
        {
            /*int same=0;
            Song *p2;
            for (p2 = head; p2 != NULL; p2 = p2->next)
            {
                printf("%s %s\n",p2->name,p2->address);
                if (p2->id == cache->id)
                {
                    printf("这首歌曲的ID已经存在于歌单中，请重新选择。\n");
                    same=1;
                    break; // 跳出内层循环，重新选择歌曲
                }
            }
            free(p2);
            if(same==1)
            {
                continue;
            }*/
            p1=(struct song*)malloc(LEN);//创建新节点
            p1->num=cache->num;
            p1->id=cache->id;
            p1->count=cache->count;
            strcpy(p1->name,cache->name);
            strcpy(p1->address,cache->address);
            if(head==NULL){//歌单为空
                head=p1;//歌单头指针指向新节点
                head->next=NULL;
            }else{
                rear->next=p1;//歌单尾指针指向新节点
            }
            rear=p1;
            p1=(struct song*)malloc(LEN);//创建新节点
        }
        if (rear != NULL) {
        rear->next = NULL; // 歌单尾指针指向NULL
        }
    }
    int count=1;
    for(p1=head;p1!=NULL;p1=p1->next)     //遍历歌单，重新编号
        {
            p1->num=count;
            count++;
        }
    return(head);//返回歌单头指针
}

void print(struct song *head)   //输出歌单
{
    struct song *p;
    p=head;
    while(p!=NULL)//遍历歌单
    {
        printf("%d  %s\n",p->num,p->name);
        p=p->next;
    }
    printf("\n");
}

void save(struct song *head)    //保存歌单
{
    struct song *p;
    p=head;
    char newName[50];
    char cache[216];
    strcpy(cache,"List/");
    printf("请输入新的歌单名称: ");
    scanf("%49s", newName);
    strcat(newName, ".txt"); // 添加 .txt 后缀
    strcat(cache,newName);
    FILE *fp2;
    fp2=fopen(cache,"w");
    if(fp2==NULL)   //打开文件失败
    {
        printf("Cannot open file!\n");
        exit(0);
    }
    while(p!=NULL)  //遍历歌单并写入文件
    {
        fprintf(fp2,"%d %d %s %s\n",p->num,p->id,p->name,p->address);
        p=p->next;
    }
    fclose(fp2);    //关闭文件
}

Song *search(struct song *head, int l) // 查找歌曲
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
                printf("返回主菜单\n");
                return NULL;
                break;
            }
            case 1:
            {
                printf("请输入要搜索的歌曲序号\n");
                scanf("%d", &m);
                if (m < 1 || m > l) // 判断输入是否合法
                {
                    printf("输入错误，请重新输入\n");
                    continue;
                }
                found = 0;
                for (p = head; p != NULL; p = p->next)
                {
                    if (p->num == m) // 判断是否找到歌曲序号
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
                    printf("未找到匹配的歌曲\n");
                    continue;
                }
                break;
            }
            case 2:
            {
                printf("请输入要搜索的歌曲名\n");
                scanf("%s", y);
                found = 0;
                for (p = head; p != NULL; p = p->next)
                {
                    if (strcmp(p->name, y) == 0) // 判断是否找到歌曲名
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
                    printf("未找到匹配的歌曲\n");
                    continue;
                }
                break;
            }
            default:
            {
                printf("输入错误，请重新输入\n");
                continue;
            }
        }
        break;
    }
}

int getLength(struct song *head)//获取歌单长度
{
    int len=0;
    struct song *l;
    l=head;
    while(l!=NULL)      //遍历歌单
    {
        len++;
        l=l->next;
    }
    return len;
}

void searchmenu()//搜索菜单
{
    printf("*******************************\n");
    printf("*    添加歌曲菜单              *\n");
    printf("*    1. 按歌曲序号添加         *\n");
    printf("*    2. 按歌名添加            *\n");
    printf("*    0. 返回主菜单             *\n");
    printf("*******************************\n");
    printf("请选择搜索方式：[0-2] > ");
}
