#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.c"
#include "song.h"

// 函数声明
Song *createPlaylist(const char *filename);
void displayPlaylist(Song *head);
void freePlaylist(Song *head);
void chooseSong(Song *head);

int main() {
    Song *head = NULL;
    head=createPlaylist("library.txt"); // 创建歌单
    displayPlaylist(head); // 显示歌单

    // 用户交互
    int choice;
    do {
        printf("请输入歌曲编号进行操作，或输入0退出程序: ");
        scanf("%d", &choice);
        if (choice != 0) {
            chooseSong(head); // 用户选择歌曲
        }
    } while (choice != 0);

    freePlaylist(head); // 清理歌单
    return 0;
}

Song *createPlaylist(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("无法打开文件");
        exit(EXIT_FAILURE);
    }
    Song *head=NULL;
    Song *newSong;
    int data;
        while (fscanf(file, "%d|%d|%d|%49s|%255s", &newSong->num, &newSong->id, &newSong->count, newSong->name, newSong->address)!=EOF) {
            // 如果读取的字段数不是5，则到达文件末尾或读取失败
            if (head == NULL) { // 如果是第一个节点
                head = newSong;
                head->next = head;
                head->prev = head;
        } else {
                head->prev->next = newSong;
                newSong->prev = head->prev;
                newSong->next = head;
                head->prev = newSong;
        }
        free(newSong);
        break;
    }
    printf("歌单创建成功。\n");
    fclose(file);
    return head;
}

void displayPlaylist(Song *head) {
    if (head == NULL) {
        printf("歌单为空。\n");
        return;
    }

    Song *current = head;
    do {
        printf("编号: %d, ID: %d, 播放次数: %d, 名称: %s, 地址: %s\n",
               current->num, current->id, current->count, current->name, current->address);
        current = current->next;
    } while (current != head);
}

void freePlaylist(Song *head) {
    Song *current = head;
    Song *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void chooseSong(Song *head) {
    int choice;
    printf("请输入您想播放的歌曲编号: ");
    scanf("%d", &choice);

    Song *current = head;
    int index = 0;

    // 循环遍历链表直到找到正确的歌曲或结束
    do {
        index++;
        if (index == choice) {
            // 调用 player 函数并传递歌曲节点
            player(current);
            return;
        }
        current = current->next;
    } while (current != head);

    // 如果没有找到对应的歌曲
    printf("找不到编号为 %d 的歌曲。\n", choice);
}