#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.c"
#include "song.h"

// ��������
Song *createPlaylist(const char *filename,Song *head);
void displayPlaylist(Song *head);
void freePlaylist(Song *head);
void chooseSong(Song *head);

int main() {
    Song *head = NULL;
    head=createPlaylist("library.txt",head); // �����赥
    displayPlaylist(head); // ��ʾ�赥

    // �û�����
    int choice;
    do {
        printf("�����������Ž��в�����������0�˳�����: ");
        scanf("%d", &choice);
        if (choice != 0) {
            chooseSong(head); // �û�ѡ�����
        }
    } while (choice != 0);

    freePlaylist(head); // ����赥
    return 0;
}

Song *createPlaylist(const char *filename, Song *head) 
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("�޷����ļ�");
        return NULL; // ����NULL��ʾʧ��
    }

    Song *rear = head;
    Song *newSong;
    newSong = (Song*)malloc(sizeof(Song));

    while (fscanf(fp, "%d|%d|%d|%49s|%255s", &newSong->num, &newSong->id, &newSong->count, newSong->name, newSong->address) == 5) 
    {
        if (newSong == NULL) {
            perror("�ڴ����ʧ��");
            fclose(fp);
            return NULL; // ����NULL��ʾʧ��
        }

        if (head == NULL) {
            head = newSong;
            newSong->next = newSong;
            newSong->prev = newSong;
            rear = newSong;
        } else {
            rear = newSong;
            head->prev = rear;
            newSong->prev = rear;
            rear->next = newSong;
            newSong->next->prev = newSong;
            rear = newSong;
        }
        newSong = (Song*)malloc(sizeof(Song));
    }

    printf("�赥�����ɹ���\n");
    fclose(fp);
    return head;
}

void displayPlaylist(Song *head) {
    if (head == NULL) {
        printf("�赥Ϊ�ա�\n");
        return;
    }

    Song *current = head;
    do {
        printf("���: %d, ID: %d, ���Ŵ���: %d, ����: %s, ��ַ: %s\n",
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
    printf("���������벥�ŵĸ������: ");
    scanf("%d", &choice);

    Song *current = head;
    int index = 0;

    // ѭ����������ֱ���ҵ���ȷ�ĸ��������
    do {
        index++;
        if (index == choice) {
            // ���� player ���������ݸ����ڵ�
            player(current);
            return;
        }
        current = current->next;
    } while (current != head);

    // ���û���ҵ���Ӧ�ĸ���
    printf("�Ҳ������Ϊ %d �ĸ�����\n", choice);
}