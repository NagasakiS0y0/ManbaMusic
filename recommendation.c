#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"
#define LEN sizeof(struct song)
struct song *create()
{
    struct song *head=NULL,*p1,*rear=NULL;
    p1=(struct song *)malloc(LEN);
    FILE *fp=fopen("library.txt","r");
    if (fp==NULL)
    {
        puts("文件打开失败");
        free(p1);
        exit(0);
    }
    while (fscanf(fp,"%d%d%d%s%s",&p1->num,&p1->id,&p1->count,p1->name,p1->address)!=EOF)
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
        p1 = (struct song*)malloc(LEN);
    }
     rear->next=NULL;
    fclose(fp);
    return(head);
}


void recommendation(struct song *s)
{
    struct song *p,*q;
    struct song temp;
    for (p=s;p->next!=NULL;p=p->next)
    {   for (q=s; q->next!=NULL;q=q->next)
    {
                if (q->next->count>q->count)
                {
                temp.count = q->count;
                q->count = q->next->count;
                q->next->count = temp.count;
                temp.id = q->id;
                q->id = q->next->id;
                q->next->id = temp.id;
                strcpy(temp.name , q->name);
                strcpy(q->name, q->next->name);
                strcpy(q->next->name, temp.name);
                strcpy(temp.address , q->address);
                strcpy(q->address, q->next->address);
                strcpy(q->next->address, temp.address);
                }
        }
    }

}
void explore(struct song *s)
{
 struct song *p, *q;
    struct song temp;
    for (p = s; p->next != NULL; p = p->next)
    {
        for (q = s; q->next != NULL; q = q->next)
        {
            if (q->next->count<q->count)
            {
                // 交换 p 和 q 的 count 值
                temp.count = q->next->count;
                q->next->count = q->count;
                q->count = temp.count;

                // 交换 p 和 q 的 id 值
                temp.id = q->next->id;
                q->next->id = q->id;
                q->id = temp.id;

                // 交换 p 和 q 的 name 值
                strcpy(temp.name, q->next->name);
                strcpy(q->next->name, q->name);
                strcpy(q->name, temp.name);

                // 交换 p 和 q 的 address 值
                strcpy(temp.address, q->next->address);
                strcpy(q->next->address, q->address);
                strcpy(q->address, temp.address);
            }
        }
    }
}

void print(struct song *s)//打印歌曲单
{
    struct song *p;
    p = s;
    while (p != NULL)
    {
        printf("%d %d %s\n", p->id, p->count, p->name);
        p = p->next;
    } 
    printf("\n");
}

int main()
{
    struct song *s;
    s = (struct song *)malloc(LEN);
    s=create();
    print(s);
    recommendation(s);
    print(s);
    explore(s);
    print(s);
    return 0;
}
