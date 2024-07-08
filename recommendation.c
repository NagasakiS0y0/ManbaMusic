#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"
#define LEN sizeof(struct song)
struct song *create()
{
    struct song *head=NULL,*p1,*rear=NULL;
    p1=(struct song *)malloc(LEN);
    FILE *fp=fopen("song.txt","r");
    if (fp==NULL)
    {
        puts("文件打开失败");
        free(p1);
        exit(0);
    }
    while (fscanf(fp,"%d:%d:%s:%s",&p1->id,&p1->count,p1->name,p1->address)!=EOF)
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
     rear->next=head;
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
                if (p->count<q->count)
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

void print(struct song *s)//打印歌曲单
{
    struct song *p;
    p = s;
    if (s== NULL)
    {
        printf("歌曲单为空。\n");
        return;
    }
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
    recommendation(s);
    print(s);
    return 0;
}
