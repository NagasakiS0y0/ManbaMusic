#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include "song.h"


// ����ΨһID
int generateRandomID() {
    srand((unsigned int)time(NULL));
    return rand() % 10000; // ����0-9999֮�������
}

// ��Ӹ���������ĩβ
void addSongToLibrary(Song *song, Song **head) {
    Song *current = *head;
    if (*head == NULL) {
        *head = song;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = song;
        song->prev = current;
    }
}

// ��ȡĿ¼�е�.wav��.mp3�ļ�
// �� readDirectorySongs ��������ȷ�ؽ���б��ת��
void readDirectorySongs(const char *directoryPath, Song **head) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directoryPath)) != NULL) {
        int num = 1;
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".wav") || strstr(ent->d_name, ".mp3")) {
                char filePath[256];
                snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, ent->d_name);
                struct stat st;
                if (stat(filePath, &st) == 0 && S_ISREG(st.st_mode)) {
                    Song *song = (Song *)malloc(sizeof(Song));
                    song->num = num++;
                    song->id = generateRandomID();
                    song->count = 0;
                    strncpy(song->name, ent->d_name, sizeof(song->name) - 1);
                    // �ȸ���·���� song->address��Ȼ���ٽ���б��ת��
                    strncpy(song->address, filePath, sizeof(song->address) - 1);
                    song->address[sizeof(song->address) - 1] = '\0';

                    // б��ת��
                    char *slash = strchr(song->address, '\\');
                    while (slash) {
                        *slash = '/';
                        slash = strchr(slash + 1, '\\');
                    }

                    song->prev = NULL;
                    song->next = NULL;
                    addSongToLibrary(song, head);
                }
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
}

// �� readUserInputSong ��������ȷ�ؽ���б��ת��
void readUserInputSong(const char *filePath, Song **head) {
    struct stat st;
    if (stat(filePath, &st) == 0 && S_ISREG(st.st_mode)) {
        Song *song = (Song *)malloc(sizeof(Song));
        song->num = (*head == NULL ? 1 : (*head)->num + 1);
        song->id = generateRandomID();
        song->count = 0;
        char *filename = strrchr(filePath, '/');
        if (filename) {
            filename = filename + 1;
            strncpy(song->name, filename, sizeof(song->name) - 1);
        } else {
            strncpy(song->name, filePath, sizeof(song->name) - 1);
        }
        // �ȸ���·���� song->address��Ȼ���ٽ���б��ת��
        strncpy(song->address, filePath, sizeof(song->address) - 1);
        song->address[sizeof(song->address) - 1] = '\0';

        // б��ת��
        char *slash = strchr(song->address, '\\');
        while (slash) {
            *slash = '/';
            slash = strchr(slash + 1, '\\');
        }

        song->prev = NULL;
        song->next = NULL;
        addSongToLibrary(song, head);
    } else {
        printf("File does not exist or is not a regular file.\n");
    }
}

// ���������ļ�
void saveLibraryToFile(Song *head) {
    FILE *fp = fopen("Library/library.txt", "w");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    Song *current = head;
    while (current != NULL) {
        fprintf(fp, "%d %d %d %s %s\n", current->num, current->id, current->count, current->name, current->address);
        current = current->next;
    }
    fclose(fp);
}

// ������
int main() {
    Song *head = NULL;
    int choice;
    char path[256];

    do {
        printf("Menu:\n");
        printf("1. Read songs from directory\n");
        printf("2. Read song from user input path\n");
        printf("3. Save library to file\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter directory path: ");
                scanf("%s", path);
                readDirectorySongs(path, &head);
                break;
            case 2:
                printf("Enter file path: ");
                scanf("%s", path);
                readUserInputSong(path, &head);
                break;
            case 3:
                saveLibraryToFile(head);
                printf("Library saved to file.\n");
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}