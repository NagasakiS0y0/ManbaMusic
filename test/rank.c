#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song {
    int num;      // 歌曲编号
    int id;       // 歌曲id
    int count;    // 播放次数
    char name[50]; // 歌曲名
    char address[256]; // 歌曲绝对位置
    struct song *prev; // 指向上一个节点
    struct song *next; // 指向下一个节点
} Song;

// 比较函数，用于qsort
int compareSongs(const void *a, const void *b) {
    Song *songA = (Song *)a;
    Song *songB = (Song *)b;
    return (songB->count - songA->count); // 降序排序
}

int main() {
    FILE *fp;
    fp = fopen("library.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "无法打开文件\n");
        return 1;
    }

    // 动态分配内存，初始大小为1
    Song *songs = malloc(sizeof(Song));
    if (songs == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return 1;
    }

    size_t numSongs = 0; // 当前已读取的歌曲数量
    size_t capacity = 1; // 当前分配的内存容量

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (numSongs >= capacity) {
            // 增加内存容量
            capacity *= 2;
            songs = realloc(songs, capacity * sizeof(Song));
            if (songs == NULL) {
                fprintf(stderr, "内存重新分配失败\n");
                return 1;
            }
        }

        // 解析一行数据
        sscanf(buffer, "%*d|%d|%d|%49s|%255s", &songs[numSongs].id, &songs[numSongs].count, songs[numSongs].name, songs[numSongs].address);
        numSongs++;
    }

    // 关闭文件
    fclose(fp);

    // 对歌曲按播放次数进行降序排序
    qsort(songs, numSongs, sizeof(Song), compareSongs);

    // 输出排序后的歌曲列表
    for (int i = 0; i < numSongs; i++) {
        printf("%d | %d | %d | %s | %s\n", i + 1, songs[i].id, songs[i].count, songs[i].name, songs[i].address);
    }

    // 释放内存
    free(songs);

    return 0;
}