#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"
void addTheSong(Song **head, Song *newSong)
{
    if (*head == NULL) {
        // �������Ϊ�գ��½ڵ����ͷ�ڵ�Ҳ��β�ڵ�
        *head = newSong;
        newSong->next=newSong;
        newSong->prev=newSong;
    } else {
        // ����Ϊ�գ����½ڵ���ӵ�����ĩβ
        Song *last=(*head)->prev;
        last->next=newSong;
        newSong->prev=last;
        newSong->next=*head;
        (*head)->prev=newSong;
    }
}

void birthSongsFromFile(Song **head) {
    FILE *fp;
    fp = fopen("Library/library.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "�޷����ļ�\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        Song *newSong = (Song *)malloc(sizeof(Song));
        if (newSong == NULL) {
            fprintf(stderr, "�ڴ����ʧ��\n");
            return;
        }
        sscanf(buffer, "%d%d%d%49s%255s",&newSong->num, &newSong->id, &newSong->count, newSong->name, newSong->address);

        addTheSong(head,newSong);
    }
    fclose(fp);

}

void recommendation(struct song *s)
{
    struct song *p,*q;
    struct song temp;
    for (p=s;p->next!=s;p=p->next)
    {   for (q=s;q->next!=s;q=q->next)
    {
                if (q->next->count>q->count)
                {
                temp.count=q->count;
                q->count=q->next->count;
                q->next->count=temp.count;
                temp.id=q->id;
                q->id=q->next->id;
                q->next->id=temp.id;
                strcpy(temp.name,q->name);
                strcpy(q->name,q->next->name);
                strcpy(q->next->name,temp.name);
                strcpy(temp.address,q->address);
                strcpy(q->address,q->next->address);
                strcpy(q->next->address,temp.address);
                }
        }
    }

}
void explore(struct song *s)
{
 struct song *p, *q;
    struct song temp;
    for (p=s;p->next!=s;p=p->next)
    {
        for (q=s;q->next!=s;q=q->next)
        {
            if (q->next->count<q->count)
            {
            
                temp.count=q->next->count;
                q->next->count=q->count;
                q->count=temp.count;

                temp.id = q->next->id;
                q->next->id = q->id;
                q->id = temp.id;

                strcpy(temp.name, q->next->name);
                strcpy(q->next->name, q->name);
                strcpy(q->name, temp.name);

                strcpy(temp.address, q->next->address);
                strcpy(q->next->address, q->address);
                strcpy(q->address, temp.address);
            }
        }
    }
}

void printList(struct song *s)//��ӡ������
{
    struct song *p=s;
    while (p->next!=s)
    {
        printf("%d %d %s\n", p->id, p->count, p->name);
        p = p->next;
    } 
     printf("%d %d %s\n", p->id, p->count, p->name);
     printf("\n");
}