#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song {
    int num;      // �������
    int id;       // ����id
    int count;    // ���Ŵ���
    char name[50]; // ������
    char address[256]; // ��������λ��
    struct song *prev; // ָ����һ���ڵ�
    struct song *next; // ָ����һ���ڵ�
} Song;

// �ȽϺ���������qsort
int compareSongs(const void *a, const void *b) {
    Song *songA = (Song *)a;
    Song *songB = (Song *)b;
    return (songB->count - songA->count); // ��������
}

int main() {
    FILE *fp;
    fp = fopen("library.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "�޷����ļ�\n");
        return 1;
    }

    // ��̬�����ڴ棬��ʼ��СΪ1
    Song *songs = malloc(sizeof(Song));
    if (songs == NULL) {
        fprintf(stderr, "�ڴ����ʧ��\n");
        return 1;
    }

    size_t numSongs = 0; // ��ǰ�Ѷ�ȡ�ĸ�������
    size_t capacity = 1; // ��ǰ������ڴ�����

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (numSongs >= capacity) {
            // �����ڴ�����
            capacity *= 2;
            songs = realloc(songs, capacity * sizeof(Song));
            if (songs == NULL) {
                fprintf(stderr, "�ڴ����·���ʧ��\n");
                return 1;
            }
        }

        // ����һ������
        sscanf(buffer, "%*d|%d|%d|%49s|%255s", &songs[numSongs].id, &songs[numSongs].count, songs[numSongs].name, songs[numSongs].address);
        numSongs++;
    }

    // �ر��ļ�
    fclose(fp);

    // �Ը��������Ŵ������н�������
    qsort(songs, numSongs, sizeof(Song), compareSongs);

    // ��������ĸ����б�
    for (int i = 0; i < numSongs; i++) {
        printf("%d | %d | %d | %s | %s\n", i + 1, songs[i].id, songs[i].count, songs[i].name, songs[i].address);
    }

    // �ͷ��ڴ�
    free(songs);

    return 0;
}