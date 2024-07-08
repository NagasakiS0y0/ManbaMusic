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
        rear=p1;
        p1=(struct song *)malloc(LEN);
    }
    rear->next=head;
    fclose(fp);
    return(head);
}

void recommendation(struct song *s)
{
    Song *p,*q;
    int num,id;
    char name[50], address[1024];
    p=s;
    if (p!=NULL)
    {
        while (1)
        {
            q=p->next;
            while (q!=s)
            {
                if (p->count<q->count)
                {
                    num=p->num;
                    p->num=q->num;
                    q->num=num;
                    id=p->id;
                    p->id=q->id;
                    q->id=id;
                    strcpy(name, p->name);
                    strcpy(p->name, q->name);
                    strcpy(q->name, name);
                    strcpy(address, p->address);
                    strcpy(p->address, q->address);
                    strcpy(q->address, address);
                }
                q=q->next;
            }
            p=p->next;
             if (p==s) 
            {
                break; 
            }
        }
        
    }
    
}
