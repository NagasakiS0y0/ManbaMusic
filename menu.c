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
        // �������Ϊ�գ��½ڵ����ͷ�ڵ�Ҳ��β�ڵ�
        *head = newSong;
        newSong->next = newSong;
        newSong->prev = newSong;
    } else {
        // ����Ϊ�գ����½ڵ���ӵ�����ĩβ
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
        sscanf(buffer, "%d %d %d %49s %255s",&newSong->num, &newSong->id, &newSong->count, newSong->name, newSong->address);

        addSong(head, newSong);
    }
    fclose(fp);
}

void printSongList(Song *head) {
    Song *current = head;
    printf("�����б�:\n");
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
        printf("���ڴ������ֿ��ļ���\n");
        createLibrary();
        printf("������ɣ�\n");
    }
    readSongsFromFile(&h);
    printf("�赥�б�����:\n");
    printSongList(h);
    getchar();
    free(h);
    return 0;

}


