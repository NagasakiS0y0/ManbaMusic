#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    printf("            3.搜索歌曲\n");
    printf("            4.查看歌曲单\n");
    printf("            0.返回前置菜单\n");
    printf("*************************************\n");
    printf("请输入您的选择：[0-4]\n");
}

struct song * create()//创建歌曲单
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
    while (fscanf(fp1,"%d%s%s",&p1->id,p1->name,p1->address)!=EOF)
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

void print(struct song *head)//打印歌曲单
{
    struct song *p;
    p = head;
    if (head == NULL)
    {
        printf("歌曲单为空。\n");
        return;
    }
    do
    {
        printf("%d %d %s\n", p->num, p->id, p->name);
        p = p->next;
    } 
    while (p != head);
    printf("\n");
}

void save(struct song *head)//保存歌曲单
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
            fprintf(fp2,"%d %d %s\n",p->num,p->id,p->name);
            p=p->next;
            if (p==head)
            {
                break;
            }
        }
    }
    fclose(fp2);
}

/**
 * 搜索歌曲函数
 * 该函数提供了一个交互式搜索界面，允许用户按照歌曲ID或文件名搜索歌曲。
 * 如果找到匹配的歌曲，将打印歌曲的编号、ID和名称。
 */
void search(struct song *head)
{
    struct song *p; // 定义一个指针用于遍历歌曲列表
    p = head; // 将指针指向列表头部
    int j = 0, i = 0; // 定义变量用于存储用户的选择和搜索的ID
    char x[50]; // 定义一个字符数组用于存储用户输入的文件名

    // 打印欢迎信息和搜索选项
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            请输入查找方式。\n");
    printf("            1.按id查找\n");
    printf("            2.按文件名查找\n");
    printf("            0.返回前置菜单\n");
    printf("*************************************\n");

    // 获取用户的选择
    printf("请输入您的选择：[0-2]\n");
    scanf("%d", &j);

    // 根据用户的选择进行不同的搜索
    switch (j)
    {
        case 1:
            // 按ID搜索
            printf("请输入要查找的id:");
            scanf("%d", &i);
            while (p != NULL)
            {
                if (p->id == i)
                {
                    // 找到匹配的歌曲，打印信息
                    printf("%d %d %s\n", p->num, p->id, p->name);
                    break;
                }
                else
                {
                    // 没有找到匹配的歌曲，打印提示信息并退出循环
                    printf("没有找到该歌曲。\n");
                    break;
                }
                p = p->next; // 移动到下一首歌曲
            }
            break;

        case 2:
            // 按文件名搜索
            printf("请输入要查找的文件名");
            scanf("%s", &x);
            while (p != NULL)
            {
                if (strcmp(p->name, x) == 0)
                {
                    // 找到匹配的歌曲，打印信息
                    printf("%d %d %s\n", p->num, p->id, p->name);
                    break;
                }
                else
                {
                    // 没有找到匹配的歌曲，打印提示信息并退出循环
                    printf("没有找到该歌曲。\n");
                    break;
                }
                p = p->next; // 移动到下一首歌曲
            }
            break;

        case 0:
            // 用户选择返回前置菜单，直接退出函数
            break;

        default:
            // 用户输入了无效的选择，打印提示信息
            printf("\n 输入错误，请重新输入！\n");
    }
}


/**
 * 删除链表中指定编号的节点
 * @param head 链表的头指针
 * @param x 要删除的节点的编号
 * @return 返回处理后的链表头指针
 */
struct song *Del_Node(struct song *head, int x)
{
    struct song *p, *q;
    int found = 0; // 用于标记是否找到要删除的节点
    p = head;
    q = NULL;

    if (head != NULL)
    {
        while (1)
        {
            if (p->num == x)
            {
                found = 1; // 找到要删除的节点
                break;
            }
            else
            {
                q = p; // 记录前一个节点
                p = p->next; // 移动到下一个节点
            }
            if (p == head)
            {
                break; // 遍历回到头节点，说明链表中没有要删除的节点
            }
        }
    }

    if (found == 1)
    {
        if (p == head)
        {
            head = p->next; // 如果要删除的节点是头节点，更新头指针
            q = p;
            while (q->next != p)
            {
                q = q->next; // 找到尾节点，用于断开链表
            }
            q->next = head; // 断开链表
        }
        else
        {
            q->next = p->next; // 如果要删除的节点不是头节点，直接断开链接
        }
        free(p); // 释放被删除节点的内存
    }
    else
    {
        printf("找不到数据!\n"); // 如果未找到要删除的节点，给出提示
    }

    return head; // 返回处理后的链表头指针
}

/*
 * 在歌曲列表中插入一个新节点
 * 此函数首先检查歌曲名称和ID是否已在文件"list.txt"中存在，
 * 如果存在，则不插入新节点并返回原列表头部指针；
 * 如果不存在，则分配内存给新节点，复制歌曲名称和ID，
 * 并根据列表是否为空来更新节点的链接，最后返回更新后的列表头部指针。
 */
struct song *insert_Node(struct song *head, int x, char y[50])
{
    struct song *p, *q, *s;
    p = head;
    q = NULL;
    s = (struct song *)malloc(LEN);
    strcpy(s->name, y);
    s->id = x;

    /* 打开文件以检查歌曲是否已存在 */
    FILE *fp = fopen("list.txt", "r");
    int id;
    char name[50];
    int found;
    found = 0;

    /* 遍历文件中的每一行，检查是否存在相同的歌曲名称和ID */
    while (fscanf(fp, "%d %s", &id, name) != EOF)
    {
        if (strcmp(name, y) == 0 && id == x)
        {
            found = 1;
            break;
        }
    }
    fclose(fp);

    /* 如果歌曲已存在，则提示错误并返回原列表头部指针 */
    if (found == 0)
    {
        printf("数据错误：歌曲不在音乐库中。\n");
        return head;
    }

    /* 如果列表为空，则将新节点设置为唯一节点 */
    if (head == NULL)
    {
        s->next = s;
        head = s;
    }
    else
    {
        /* 找到列表的最后一个节点，并将新节点插入到其后面 */
        while (p->next != head)
        {
            q = p;
            p = p->next;
        }
        q->next = s;
        s->next = head;
    }
    return head;
}


void search_way(char *way) 
{
    WIN32_FIND_DATA Data;// 存储文件信息的结构体
    HANDLE hFind;// 查找句柄

    char path[1024];// 定义一个字符串数组，用于存储搜索路径
    snprintf(path, sizeof(path), "%s\\*.mp3", way);// 将 \*.mp3 附加到文件夹路径后面
    printf("正在搜索路径: %s\n", path);
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
        char address[1024];
        strcpy(address, path);
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// 找到文件名的后缀位置
            if (dotPos != NULL) // 删除文件名中的后缀
            {
                *dotPos = '\0';
            }
            printf("找到MP3文件: %s.mp3\n", Data.cFileName);
            fprintf(fp1, "%s %s\n", Data.cFileName, address);
            fprintf(fp2, "%s %s\n", Data.cFileName, address); // 写入序号和文件名到 song.txt
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// 关闭查找句柄
        fclose(fp1);
        fclose(fp2);
}

/*
 * 对歌曲列表进行排序
 * 该函数通过冒泡排序算法对歌曲列表进行排序，首先按照歌曲编号（num）升序排序，
 * 然后重新为歌曲列表中的每一项分配从1开始的顺序编号。
 */
void paixu(struct song *head) 
{
    struct song *p, *q;
    int num,id;
    char name[50], address[1024];

    /* 初始化指针p为列表头部 */
    p = head;
    /* 当列表不为空时进行排序 */
    if (p != NULL) 
    {
        /* 使用冒泡排序对列表进行排序 */
        while(1)
        {
            /* 初始化指针q为p的下一个节点，用于在列表中比较 */
            q = p->next;
            /* 遍历列表直到回到头部 */
            while (q!=head) 
            {
                /* 如果当前节点的歌曲编号大于下一个节点的编号，则交换它们的信息 */
                if (p->num>q->num) 
                {
                    /* 交换歌曲编号 */
                    num=p->num;
                    p->num=q->num;
                    q->num=num;
                    /* 交换歌曲ID */
                    id=p->id;
                    p->id=q->id;
                    q->id=id;
                    /* 交换歌曲名称 */
                    strcpy(name, p->name);
                    strcpy(p->name, q->name);
                    strcpy(q->name, name);
                    /* 交换歌曲地址 */
                    strcpy(address, p->address);
                    strcpy(p->address, q->address);
                    strcpy(q->address, address);
                }   
                /* 移动指针q到下一个节点 */
                q=q->next;
            }
            /* 移动指针p到下一个节点 */
            p=p->next;
            /* 如果p回到头部，则排序完成，跳出循环 */
            if (p==head) 
            {
                break; 
            }
        }

        /* 重新为歌曲列表中的每一项分配从1开始的顺序编号 */
        p = head;
        int i = 1;
        if(p != NULL) 
        {
            while(1)
            {
                /* 给节点分配顺序编号 */
                p->num=i++;
                /* 移动指针p到下一个节点 */
                p=p->next;
                /* 如果p回到头部，则编号完成，跳出循环 */
                if (p==head) 
                {
                    break;
                }
            }
        }
    }
}

void give_id(struct song *head) //可能有问题
{
    struct song *p = head;
    int id;
    int repeat;
    repeat=0;
    struct song *q;
    
    FILE *fp1 = fopen("list.txt", "w");
    FILE *fp2 = fopen("song.txt", "w");
    if (fp1 == NULL) 
    {
        puts("无法打开 list.txt 文件。");
        return;
    }
    
    srand(time(0));

    while (p != NULL) 
    {
        do 
        {
            id = rand() % 9000 + 1000;
            q = head;

            while (q != NULL) 
            {
                if (q->id == id) 
                {
                    repeat = 1;
                    break;
                }
                q = q->next;
                if (q == head) 
                {
                    break;
                }
            }
        } while (repeat==1);

        p->id = id;
        p = p->next;
        if (p== head) 
        {
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
}

/*void copy(struct song *head) //也好像有点问题
{
    if (head == NULL) 
    {
        printf("链表为空。\n");
        return;
    }

    struct song *p = head;
    FILE *fp1 = fopen("list.txt", "r");
    FILE *fp2 = fopen("song.txt", "w");

    
    do {
        fprintf(fp2, "%s %s\n", p->name, p->address);
        p = p->next;
    } while (p != head);
        fclose(fp1);
        fclose(fp2);
}*/

int main()
{
    int i, j, k;
    char x[50], y[1024];
    struct song *h;
    h = NULL;
    give_id(h);
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            是否存在音乐库？\n");
    printf("            1.不存在音乐库\n");
    printf("            2.已存在音乐库\n");
    printf("            0.返回前置菜单\n");
    printf("*************************************\n");
    printf("请输入您的选择：[0-2]\n");
    scanf("%d", &i);
    while (1)
    {
        if (i == 1)
        {
            system("cls");
            printf("正在创建音乐库文件。\n");
            char *way = "D:\\code\\C language\\7\\project\\git\\output"; // 替换为实际路径
            search_way(way); // 调用 search 函数找出.mp3文件
            printf("创建完成！\n");
            //give_id(h);
            //copy(h);
            h = create();
            printf("创建的歌曲单如下:\n");
            paixu(h);
            print(h);
            break;
        }
        else if (i == 2)
        {
            system("cls");
            printf("正在从歌曲单文件读取数据\n");
            //copy(h);
            h = create();
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
    // 主循环等待用户选择操作
    while (1)
    {
        menu1();
        scanf("%d", &j);
        switch (j)
        {
            case 1:
                printf("请输入需要添加的歌曲（文件名 歌手）:\n");
                scanf("%s %s", &x, &y);
                h = insert_Node(h, x, y);
                paixu(h);
                save(h);
                printf("添加成功！\n");
                print(h);
                break;
            case 2:
                printf("请输入需要删除的歌曲（序号）:\n");
                scanf("%d", &k);
                h = Del_Node(h, k);
                paixu(h);
                system("cls");
                save(h);
                printf("删除成功！\n");
                break;
            case 3:
                printf("请输入需要搜索的歌曲:\n");
                search(h);
                break;
            case 4:
                system("cls");
                printf("歌曲单如下:\n");
                print(h);
                break;
            case 0:
                return 1; // 返回前置菜单
            default:
                printf("\n 输入错误，请重新输入！\n");
        };
    }
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    printf("            3.搜索歌曲\n");
    printf("            4.查看歌曲单\n");
    printf("            0.返回前置菜单\n");
    printf("*************************************\n");
    printf("请输入您的选择：[0-4]\n");
}

struct song * create()//创建歌曲单
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
    while (fscanf(fp1,"%d%s%s",&p1->id,p1->name,p1->address)!=EOF)
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

void print(struct song *head)//打印歌曲单
{
    struct song *p;
    p = head;
    if (head == NULL)
    {
        printf("歌曲单为空。\n");
        return;
    }
    do
    {
        printf("%d %d %s\n", p->num, p->id, p->name);
        p = p->next;
    } 
    while (p != head);
    printf("\n");
}

void save(struct song *head)//保存歌曲单
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
            fprintf(fp2,"%d %d %s\n",p->num,p->id,p->name);
            p=p->next;
            if (p==head)
            {
                break;
            }
        }
    }
    fclose(fp2);
}

/**
 * 搜索歌曲函数
 * 该函数提供了一个交互式搜索界面，允许用户按照歌曲ID或文件名搜索歌曲。
 * 如果找到匹配的歌曲，将打印歌曲的编号、ID和名称。
 */
void search(struct song *head)
{
    struct song *p; // 定义一个指针用于遍历歌曲列表
    p = head; // 将指针指向列表头部
    int j = 0, i = 0; // 定义变量用于存储用户的选择和搜索的ID
    char x[50]; // 定义一个字符数组用于存储用户输入的文件名

    // 打印欢迎信息和搜索选项
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            请输入查找方式。\n");
    printf("            1.按id查找\n");
    printf("            2.按文件名查找\n");
    printf("            0.返回前置菜单\n");
    printf("*************************************\n");

    // 获取用户的选择
    printf("请输入您的选择：[0-2]\n");
    scanf("%d", &j);

    // 根据用户的选择进行不同的搜索
    switch (j)
    {
        case 1:
            // 按ID搜索
            printf("请输入要查找的id:");
            scanf("%d", &i);
            while (p != NULL)
            {
                if (p->id == i)
                {
                    // 找到匹配的歌曲，打印信息
                    printf("%d %d %s\n", p->num, p->id, p->name);
                    break;
                }
                else
                {
                    // 没有找到匹配的歌曲，打印提示信息并退出循环
                    printf("没有找到该歌曲。\n");
                    break;
                }
                p = p->next; // 移动到下一首歌曲
            }
            break;

        case 2:
            // 按文件名搜索
            printf("请输入要查找的文件名");
            scanf("%s", &x);
            while (p != NULL)
            {
                if (strcmp(p->name, x) == 0)
                {
                    // 找到匹配的歌曲，打印信息
                    printf("%d %d %s\n", p->num, p->id, p->name);
                    break;
                }
                else
                {
                    // 没有找到匹配的歌曲，打印提示信息并退出循环
                    printf("没有找到该歌曲。\n");
                    break;
                }
                p = p->next; // 移动到下一首歌曲
            }
            break;

        case 0:
            // 用户选择返回前置菜单，直接退出函数
            break;

        default:
            // 用户输入了无效的选择，打印提示信息
            printf("\n 输入错误，请重新输入！\n");
    }
}


/**
 * 删除链表中指定编号的节点
 * @param head 链表的头指针
 * @param x 要删除的节点的编号
 * @return 返回处理后的链表头指针
 */
struct song *Del_Node(struct song *head, int x)
{
    struct song *p, *q;
    int found = 0; // 用于标记是否找到要删除的节点
    p = head;
    q = NULL;

    if (head != NULL)
    {
        while (1)
        {
            if (p->num == x)
            {
                found = 1; // 找到要删除的节点
                break;
            }
            else
            {
                q = p; // 记录前一个节点
                p = p->next; // 移动到下一个节点
            }
            if (p == head)
            {
                break; // 遍历回到头节点，说明链表中没有要删除的节点
            }
        }
    }

    if (found == 1)
    {
        if (p == head)
        {
            head = p->next; // 如果要删除的节点是头节点，更新头指针
            q = p;
            while (q->next != p)
            {
                q = q->next; // 找到尾节点，用于断开链表
            }
            q->next = head; // 断开链表
        }
        else
        {
            q->next = p->next; // 如果要删除的节点不是头节点，直接断开链接
        }
        free(p); // 释放被删除节点的内存
    }
    else
    {
        printf("找不到数据!\n"); // 如果未找到要删除的节点，给出提示
    }

    return head; // 返回处理后的链表头指针
}

/*
 * 在歌曲列表中插入一个新节点
 * 此函数首先检查歌曲名称和ID是否已在文件"list.txt"中存在，
 * 如果存在，则不插入新节点并返回原列表头部指针；
 * 如果不存在，则分配内存给新节点，复制歌曲名称和ID，
 * 并根据列表是否为空来更新节点的链接，最后返回更新后的列表头部指针。
 */
struct song *insert_Node(struct song *head, int x, char y[50])
{
    struct song *p, *q, *s;
    p = head;
    q = NULL;
    s = (struct song *)malloc(LEN);
    strcpy(s->name, y);
    s->id = x;

    /* 打开文件以检查歌曲是否已存在 */
    FILE *fp = fopen("list.txt", "r");
    int id;
    char name[50];
    int found;
    found = 0;

    /* 遍历文件中的每一行，检查是否存在相同的歌曲名称和ID */
    while (fscanf(fp, "%d %s", &id, name) != EOF)
    {
        if (strcmp(name, y) == 0 && id == x)
        {
            found = 1;
            break;
        }
    }
    fclose(fp);

    /* 如果歌曲已存在，则提示错误并返回原列表头部指针 */
    if (found == 0)
    {
        printf("数据错误：歌曲不在音乐库中。\n");
        return head;
    }

    /* 如果列表为空，则将新节点设置为唯一节点 */
    if (head == NULL)
    {
        s->next = s;
        head = s;
    }
    else
    {
        /* 找到列表的最后一个节点，并将新节点插入到其后面 */
        while (p->next != head)
        {
            q = p;
            p = p->next;
        }
        q->next = s;
        s->next = head;
    }
    return head;
}


void search_way(char *way) 
{
    WIN32_FIND_DATA Data;// 存储文件信息的结构体
    HANDLE hFind;// 查找句柄

    char path[1024];// 定义一个字符串数组，用于存储搜索路径
    snprintf(path, sizeof(path), "%s\\*.mp3", way);// 将 \*.mp3 附加到文件夹路径后面
    printf("正在搜索路径: %s\n", path);
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
        char address[1024];
        strcpy(address, path);
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// 找到文件名的后缀位置
            if (dotPos != NULL) // 删除文件名中的后缀
            {
                *dotPos = '\0';
            }
            printf("找到MP3文件: %s.mp3\n", Data.cFileName);
            fprintf(fp1, "%s %s\n", Data.cFileName, address);
            fprintf(fp2, "%s %s\n", Data.cFileName, address); // 写入序号和文件名到 song.txt
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// 关闭查找句柄
        fclose(fp1);
        fclose(fp2);
}

/*
 * 对歌曲列表进行排序
 * 该函数通过冒泡排序算法对歌曲列表进行排序，首先按照歌曲编号（num）升序排序，
 * 然后重新为歌曲列表中的每一项分配从1开始的顺序编号。
 */
void paixu(struct song *head) 
{
    struct song *p, *q;
    int num,id;
    char name[50], address[1024];

    /* 初始化指针p为列表头部 */
    p = head;
    /* 当列表不为空时进行排序 */
    if (p != NULL) 
    {
        /* 使用冒泡排序对列表进行排序 */
        while(1)
        {
            /* 初始化指针q为p的下一个节点，用于在列表中比较 */
            q = p->next;
            /* 遍历列表直到回到头部 */
            while (q!=head) 
            {
                /* 如果当前节点的歌曲编号大于下一个节点的编号，则交换它们的信息 */
                if (p->num>q->num) 
                {
                    /* 交换歌曲编号 */
                    num=p->num;
                    p->num=q->num;
                    q->num=num;
                    /* 交换歌曲ID */
                    id=p->id;
                    p->id=q->id;
                    q->id=id;
                    /* 交换歌曲名称 */
                    strcpy(name, p->name);
                    strcpy(p->name, q->name);
                    strcpy(q->name, name);
                    /* 交换歌曲地址 */
                    strcpy(address, p->address);
                    strcpy(p->address, q->address);
                    strcpy(q->address, address);
                }   
                /* 移动指针q到下一个节点 */
                q=q->next;
            }
            /* 移动指针p到下一个节点 */
            p=p->next;
            /* 如果p回到头部，则排序完成，跳出循环 */
            if (p==head) 
            {
                break; 
            }
        }

        /* 重新为歌曲列表中的每一项分配从1开始的顺序编号 */
        p = head;
        int i = 1;
        if(p != NULL) 
        {
            while(1)
            {
                /* 给节点分配顺序编号 */
                p->num=i++;
                /* 移动指针p到下一个节点 */
                p=p->next;
                /* 如果p回到头部，则编号完成，跳出循环 */
                if (p==head) 
                {
                    break;
                }
            }
        }
    }
}

void give_id(struct song *head) //可能有问题
{
    struct song *p = head;
    int id;
    int repeat;
    repeat=0;
    struct song *q;
    
    FILE *fp1 = fopen("list.txt", "w");
    FILE *fp2 = fopen("song.txt", "w");
    if (fp1 == NULL) 
    {
        puts("无法打开 list.txt 文件。");
        return;
    }
    
    srand(time(0));

    while (p != NULL) 
    {
        do 
        {
            id = rand() % 9000 + 1000;
            q = head;

            while (q != NULL) 
            {
                if (q->id == id) 
                {
                    repeat = 1;
                    break;
                }
                q = q->next;
                if (q == head) 
                {
                    break;
                }
            }
        } while (repeat==1);

        p->id = id;
        p = p->next;
        if (p== head) 
        {
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
}

/*void copy(struct song *head) //也好像有点问题
{
    if (head == NULL) 
    {
        printf("链表为空。\n");
        return;
    }

    struct song *p = head;
    FILE *fp1 = fopen("list.txt", "r");
    FILE *fp2 = fopen("song.txt", "w");

    
    do {
        fprintf(fp2, "%s %s\n", p->name, p->address);
        p = p->next;
    } while (p != head);
        fclose(fp1);
        fclose(fp2);
}*/

int main()
{
    int i, j, k;
    char x[50], y[1024];
    struct song *h;
    h = NULL;
    give_id(h);
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            是否存在音乐库？\n");
    printf("            1.不存在音乐库\n");
    printf("            2.已存在音乐库\n");
    printf("            0.返回前置菜单\n");
    printf("*************************************\n");
    printf("请输入您的选择：[0-2]\n");
    scanf("%d", &i);
    while (1)
    {
        if (i == 1)
        {
            system("cls");
            printf("正在创建音乐库文件。\n");
            char *way = "D:\\code\\C language\\7\\project\\git\\output"; // 替换为实际路径
            search_way(way); // 调用 search 函数找出.mp3文件
            printf("创建完成！\n");
            //give_id(h);
            //copy(h);
            h = create();
            printf("创建的歌曲单如下:\n");
            paixu(h);
            print(h);
            break;
        }
        else if (i == 2)
        {
            system("cls");
            printf("正在从歌曲单文件读取数据\n");
            //copy(h);
            h = create();
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
    // 主循环等待用户选择操作
    while (1)
    {
        menu1();
        scanf("%d", &j);
        switch (j)
        {
            case 1:
                printf("请输入需要添加的歌曲（文件名 歌手）:\n");
                scanf("%s %s", &x, &y);
                h = insert_Node(h, x, y);
                paixu(h);
                save(h);
                printf("添加成功！\n");
                print(h);
                break;
            case 2:
                printf("请输入需要删除的歌曲（序号）:\n");
                scanf("%d", &k);
                h = Del_Node(h, k);
                paixu(h);
                system("cls");
                save(h);
                printf("删除成功！\n");
                break;
            case 3:
                printf("请输入需要搜索的歌曲:\n");
                search(h);
                break;
            case 4:
                system("cls");
                printf("歌曲单如下:\n");
                print(h);
                break;
            case 0:
                return 1; // 返回前置菜单
            default:
                printf("\n 输入错误，请重新输入！\n");
        };
    }
    return 0;
}

