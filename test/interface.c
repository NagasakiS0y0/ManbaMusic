#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"
#include "player.c"

// ��������
void readSongsFromFile(Song **head);
void printSongList(Song *head);
void selectSongToPlay(Song *head);
void addSong(Song **head, Song *newSong);

int main() {
    Song *head = NULL; // ��ʼ������ͷָ��

    // ���ļ��ж�ȡ������Ϣ����������
    readSongsFromFile(&head);

    // �û�ѡ��������в���
    selectSongToPlay(head);

    // ��������
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

void selectSongToPlay(Song *head) {
    int choice;
    Song *current = head; // ��current��ʼ��Ϊhead
    
    while (1) { // ʹ������ѭ����ֱ���û�ѡ���˳�
        printSongList(head);
        printf("������Ҫ���ŵĸ�����ţ�����0�˳���: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            return; // �û�ѡ���˳�
        }
        
        current = head; // ÿ��ѭ����ʼʱ����currentΪhead
        while (current->num != choice) {
            if (current->next == head) {
                printf("������Ų����ڣ����������롣\n");
                break; // �����������β����δ�ҵ����������˳�ѭ��
            }
            current = current->next;
        }
        
        if (current->num == choice) {
            player(current); // �ҵ�����������
        }
    }
}

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