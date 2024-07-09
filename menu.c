#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h> 
#include "createLibrary.c"
//#include "interface.c"
#include "song.h"#include "song.h"

void addList(List **head, List *newList)
{
    if (*head == NULL) {
        // 如果链表为空，新节点即是头节点
        *head = newList;
        newList->next = NULL;  // 单向链表的尾部next应指向NULL
    } else {
        // 链表不为空，将新节点添加到链表末尾
        List *last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newList;
        newList->next = NULL;  // 新节点是链表的最后一个元素
    }
}void readListsFromFile(List **head) {
    FILE *fp;
    fp = fopen("listCatalog.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "无法打开文件\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        List *newList = (List *)malloc(sizeof(List));
        if (newList == NULL) {
            fprintf(stderr, "内存分配失败\n");
            return;
        }
        sscanf(buffer, "%d%49s%255s",&newList->listNum, newList->listName, newList->listAddress);
       addList(head, newList);
    }
    fclose(fp);
}

void printList(List *head) {
    List *current = head;
    printf("歌单列表:\n");
    while (current->next != NULL) {
        printf("%03d | %s\n", current->listNum, current->listName);
        current = current->next;
    }
    printf("%03d | %s\n", current->listNum, current->listName);
}

int main()
{
    List *h=NULL;
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("                             \n");
    printf("           man what can i say\n");
    printf("                             \n");
    printf("                             \n");
    printf("*************************************\n");
    FILE *fp;
    fp=fopen("Library/library.txt","r");
    if (fp == NULL)
    {
        printf("正在创建音乐库文件。\n");
        createLibrary();
        printf("创建完成！\n");
    }
    readListsFromFile(&h);
    printf("歌单列表如下:\n");
    printList(h);
    getchar();
    free(h);
    return 0;

}


