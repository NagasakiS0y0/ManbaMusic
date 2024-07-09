#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h> 
#include "createLibrary.c"
//#include "interface.c"
#include "song.h"
void addSong(Song **head, Song *newSong)
{
    if (*head == NULL) {
        // 如果链表为空，新节点既是头节点也是尾节点
        *head = newSong;
        newSong->next = newSong;
        newSong->prev = newSong;
    } else {
        // 链表不为空，将新节点添加到链表末尾
        Song *last = (*head)->prev;
        last->next = newSong;
        newSong->prev = last;
        newSong->next = *head;
        (*head)->prev = newSong;
    }
}
void readSongsFromFile(Song **head) {
    FILE *fp;
    fp = fopen("Library/library.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "无法打开文件\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        Song *newSong = (Song *)malloc(sizeof(Song));
        if (newSong == NULL) {
            fprintf(stderr, "内存分配失败\n");
            return;
        }
        sscanf(buffer, "%d %d %d %49s %255s",&newSong->num, &newSong->id, &newSong->count, newSong->name, newSong->address);

        addSong(head, newSong);
    }
    fclose(fp);
}

void printSongList(Song *head) {
    Song *current = head;
    printf("歌曲列表:\n");
    while (current->next != head) {
        printf("%03d | %s\n", current->num, current->name);
        current = current->next;
    }
    printf("%03d | %s\n", current->num, current->name);
}

int main()
{
    Song *h=NULL;
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
    readSongsFromFile(&h);
    printf("歌单列表如下:\n");
    printSongList(h);
    getchar();
    free(h);
    return 0;

}


