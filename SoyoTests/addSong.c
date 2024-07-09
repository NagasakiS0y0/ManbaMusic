#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <song.h>
#define LEN sizeof(Song)    //歌单结构体长度



Song *addSongFromLib()
{
    void libPrint(Song *libHead);
    Song *createFromLib();

    int n,m;//功能选择菜单的判断变量
    int length=0;
    int found;
    char y[20];//歌曲名字
    Song *p;
    Song *h;//歌单头指针
    printf("----从曲库读取数据----\n");
    h=createFromLib();//创建歌单
    printf("读取结果如下\n");
    libPrint(h);//输出歌单

    while(1)//功能选择菜单
    {
        printf("*    1. 搜索序号添加\n");
        printf("*    2. 搜索歌名添加\n");
        printf("*    0. 返回上级\n");
        printf("请选择功能：[0-2] > ");
        scanf("%d",&n);
        switch (n)
        {
        case 0:
            free(h);
            return;
        case 1:
            {
                printf("请输入要搜索的歌曲序号\n");
                scanf("%d", &m);
                found = 0;
                for (p = h; p != NULL; p = p->next)
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
                if (!found) printf("未找到匹配的歌曲\n");
                break;
            }
        case 2:
            {
                printf("请输入要搜索的歌曲名\n");
                scanf("%s", y);
                found = 0;
                for (p = h; p != NULL; p = p->next)
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
                if (!found) printf("未找到匹配的歌曲\n");
                break;
            }
        default:
            printf("输入出错，请重试！\n");
            continue;
        }
    }
}

void libPrint(Song *libHead)//输出歌单
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

Song *createFromLib()//    读取文件
{
    Song *libHead=NULL,*p1,*libRear=NULL;//歌单头指针、局部指针、歌单尾指针
    FILE *fp1;
    fp1=fopen("Library/library.txt","r");
    if(fp1==NULL)
    {
        printf("Cannot open file!\n");
        return;
    }

    p1=(Song*)malloc(LEN);//创建新节点

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
        p1=(Song*)malloc(LEN);//创建新节点
    }
    libRear->next=NULL;//歌单尾指针指向NULL
    fclose(fp1);
    return(libHead);//返回歌单头指针
}
