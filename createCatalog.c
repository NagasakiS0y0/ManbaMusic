#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // For directory handling
#include <sys/stat.h> // For stat function
#include <time.h> // For time and rand functions
#include "song.h"
void addList(List **head, List *newList)
{
    if (*head == NULL) {
        // �������Ϊ�գ��½ڵ㼴��ͷ�ڵ�
        *head = newList;
        newList->next = NULL;  // ���������β��nextӦָ��NULL
    } else {
        // ����Ϊ�գ����½ڵ���ӵ�����ĩβ
        List *last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newList;
        newList->next = NULL;  // �½ڵ�����������һ��Ԫ��
    }
}void readListsFromFile(List **head) {
    FILE *fp;
    fp = fopen("listCatalog.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "�޷����ļ�\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        List *newList = (List *)malloc(sizeof(List));
        if (newList == NULL) {
            fprintf(stderr, "�ڴ����ʧ��\n");
            return;
        }
        sscanf(buffer, "%d%49s%255s",&newList->listNum, newList->listName, newList->listAddress);
        addList(head, newList);
    }
    fclose(fp);
}

void printListCatalog(List *head) {
    List *now = head;
    printf("�赥�б�:\n");
    while (now->next != NULL) {
        printf("%03d | %s\n", now->listNum, now->listName);
        now = now->next;
    }
    printf("%03d | %s\n", now->listNum, now->listName);
}
