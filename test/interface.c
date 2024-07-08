#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"
#include "player.c"

// 函数声明
void readSongsFromFile(Song **head);
void printSongList(Song *head);
void selectSongToPlay(Song *head);
void addSong(Song **head, Song *newSong);

int main() {
    Song *head = NULL; // 初始化链表头指针

    // 从文件中读取歌曲信息并构建链表
    readSongsFromFile(&head);

    // 用户选择歌曲进行播放
    selectSongToPlay(head);

    // 清理链表
    Song *current = head->next;
    while (current != head) {
        Song *next = current->next;
        free(current);
        current = next;
    }
    free(head);

    return 0;
}

void readSongsFromFile(Song **head) {
    FILE *fp;
    fp = fopen("library.txt", "r");
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

void selectSongToPlay(Song *head) {
    int choice;
    Song *current = head; // 将current初始化为head
    
    while (1) { // 使用无限循环，直到用户选择退出
        printSongList(head);
        printf("请输入要播放的歌曲编号（输入0退出）: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            return; // 用户选择退出
        }
        
        current = head; // 每次循环开始时重置current为head
        while (current->num != choice) {
            if (current->next == head) {
                printf("歌曲编号不存在，请重新输入。\n");
                break; // 如果到达链表尾部而未找到歌曲，则退出循环
            }
            current = current->next;
        }
        
        if (current->num == choice) {
            player(current); // 找到歌曲，播放
        }
    }
}

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