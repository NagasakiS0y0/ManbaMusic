#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.c"
#include "song.h"

// ��������
Song *createPlaylist(const char *filename);
void displayPlaylist(Song *head);
void freePlaylist(Song *head);
void chooseSong(Song *head);

int main() {
    Song *head = NULL;
    head=createPlaylist("library.txt"); // �����赥
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

Song *createPlaylist(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("�޷����ļ�");
        exit(EXIT_FAILURE);
    }
    Song *head=NULL;
    Song *newSong;
    int data;
        while (fscanf(file, "%d|%d|%d|%49s|%255s", &newSong->num, &newSong->id, &newSong->count, newSong->name, newSong->address)!=EOF) {
            // �����ȡ���ֶ�������5���򵽴��ļ�ĩβ���ȡʧ��
            if (head == NULL) { // ����ǵ�һ���ڵ�
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
    printf("�赥�����ɹ���\n");
    fclose(file);
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