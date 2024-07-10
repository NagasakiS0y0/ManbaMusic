#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "song.h"
#include "player.c"

Song *addSongFromLib();     //�������ȡ������Ϣ
void printSongList(Song *head);     //����赥
void renumberSongs(Song **head);    //���±��
void selectSongToPlay(Song *head);      //ѡ�����
void addSong(Song **head, List *l);     //��Ӹ���
void deleteSong(Song **head,List *l);       //ɾ������
void addNode(Song **head, Song *newSong);       //��ӽڵ�
void renamePlaylist(Song *head,List **l);       //�������赥
void readSongsFromFile(Song **head,List *l);    //���ļ���ȡ������Ϣ
void savePlaylistToFile(Song *head,List *l);    //����赥���ļ�

void listMain(List *l)      //�赥�ڲ�����������ָ��赥��ָ�룬�ɵ���
{
    Song *head = NULL;
    Song *current;
    readSongsFromFile(&head,l);   // ���ļ��ж�ȡ������Ϣ����������

    char choice;
    while(1) 
    {
        system("cls");
        printf("[��ǰ�赥]> [%s]\n\n",l->listName);
        printSongList(head);
        printf("*********************************\n");
        printf("   1. ��������    2. ���Ӹ���\n");
        printf("   3. ɾ������    4. �������赥\n");
        printf("   0. �˳�\n");
        printf("*********************************\n");
        printf("��ѡ���ܣ�[0-4] > ");
        
        choice=getch();
        switch (choice) {
            case '1':
                selectSongToPlay(head);
                break;
            case '2':
                addSong(&head,l);
                break;
            case '3':
                deleteSong(&head,l);
                break;
            case '4':
                renamePlaylist(head,&l);
                break;
            case '0':
                current = head->next;
                while (current != head) 
                {
                    Song *next = current->next;
                    free(current);
                    current = next;
                }
                free(head);
                return;
            default:
                printf("��Ч��ѡ�����������롣\n");
                break;
        }
    }

    // ��������
    

    return;
}

void readSongsFromFile(Song **head,List *l) {
    FILE *fp;
    fp = fopen(l->listAddress, "r");
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
        sscanf(buffer, "%d %d %49s %255s",&newSong->num, &newSong->id, newSong->name, newSong->address);
        addNode(head, newSong);
    }
    fclose(fp);
}

void selectSongToPlay(Song *head) {
    int choice;
    Song *current = head;
    
    while (1) {
        system("cls");
        printSongList(head);
        printf("������Ҫ���ŵĸ�����ţ�����0���أ�> ");
        scanf("%d",&choice);
        current = head;
        while (current->num != choice) {
            if (current->next == head) {
                MessageBox(NULL, "������Ų����ڣ����������룡","����", MB_OK);
                break; //δ�ҵ��������˳�
            }
            current = current->next;
        }
        
        if (current->num == choice) {
            player(current);
        }
    }
}

void addNode(Song **head, Song *newSong)    //��ӽڵ�
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

void renamePlaylist(Song *head,List **l)    //�������赥
{
    char newName[50];
    char cache[256];
    char folder[10];
    strcpy(folder,"List/");
    printf("�������µĸ赥����: ");
    scanf("%49s", newName);
    strcpy(cache, newName);
    strcat(newName, ".txt"); // ��� .txt ��׺
    strcat(folder, newName);
    if (rename((*l)->listAddress, folder) != 0) {
        MessageBox(NULL, "������ʧ�ܣ������ļ�����Ȩ��", "����", MB_OK);      // ��ʾ������Ϣ
    } else {
        MessageBox(NULL, "�������ɹ�", newName, MB_OK);     // ��ʾ�ɹ���Ϣ
    }
    strcpy((*l)->listName, cache);
    strcpy((*l)->listAddress, folder);
}

void addSong(Song **head, List *l)  // ��Ӹ������赥
{
    Song *newSong = addSongFromLib(); // ��ȡҪ��ӵĸ���ָ��
    if (newSong != NULL) {
        // ���赥���Ƿ��Ѿ�����ͬ�ĸ���
        Song *current = *head;
        do {
            if (current && current->id == newSong->id) {
                MessageBox(NULL, "�����Ѿ������ڸ赥�С�","����", MB_OK);
                free(newSong);
                return;
            }
            current = current->next;
        } while (current != *head);

        // �赥��û����ͬ�ĸ������������
        addNode(head, newSong); // ��������ӵ�����ĩβ
        savePlaylistToFile(*head, l); // ����赥���ļ�
    }
}

void libPrint(Song *libHead)    //����赥
{
    Song *p;
    p=libHead;
    while(p!=NULL)
    {
        printf("%d  %s\n",p->num,p->name);
        p=p->next;
    }
    printf("\n");
}

Song *createFromLib()   //��ȡ�ļ�
{
    Song *libHead=NULL,*p1,*libRear=NULL;//�赥ͷָ�롢�ֲ�ָ�롢�赥βָ��
    FILE *fp1;
    fp1=fopen("Library/library.txt","r");
    if(fp1==NULL)
    {
        MessageBox(NULL, "�����ļ���ʧ��","����", MB_OK);
        return NULL;
    }

    p1=(Song*)malloc(LEN);//�����½ڵ�

    if(p1==NULL){
        MessageBox(NULL, "�ڴ�������","����", MB_OK);
        exit(1);
    }
    while(fscanf(fp1,"%d%d%d%s%s",&p1->num,&p1->id,&p1->count,p1->name,p1->address)!=EOF)
    {
        if(libHead==NULL)
        {
            libHead=p1;
        }else
        {
            libRear->next=p1;
        }
        libRear=p1;
        p1=(Song*)malloc(LEN);
    }
    libRear->next=NULL;
    fclose(fp1);
    return(libHead);//���ظ赥ͷָ��
}

Song *addSongFromLib()  //��������Ӹ���
{
    void libPrint(Song *libHead);
    Song *createFromLib();

    int m;    //����ѡ��˵����жϱ���
    char n;
    int length=0;
    int found;
    char y[20];     //��������
    Song *p;
    Song *h;    //�赥ͷָ��
    h=createFromLib();      //�����赥
    while(1)    //����ѡ��˵�
    {
        system("cls");
        printf("***************����***************\n");
        libPrint(h);    //����赥
        printf("*********************************\n");
        printf("1. ����������     2. �����������\n");
        printf("0. �����ϼ�\n");
        printf("*********************************\n");
        printf("��ѡ���ܣ�[0-2] > ");
        n=getch();
        switch (n)
        {
        case 0:
            free(h);
            return NULL;
        case 1:
            {
                printf("������Ҫ�����ĸ������\n");
                scanf("%d", &m);
                found = 0;
                for (p = h; p != NULL; p = p->next)
                {
                    if (p->num == m) // �ж��Ƿ��ҵ��������
                    {
                        if (!found)
                        {
                            printf("Song found!\n");
                            found = 1;
                        }
                        printf("%d  %s\n", p->num, p->name);
                        return p;
                    }
                }
                if (!found) printf("δ�ҵ�ƥ��ĸ���\n");
                break;
            }
        case 2:
            {
                printf("������Ҫ�����ĸ�����\n");
                scanf("%s", y);
                found = 0;
                for (p = h; p != NULL; p = p->next)
                {
                    if (strcmp(p->name, y) == 0) // �ж��Ƿ��ҵ�������
                    {
                        if (!found)
                        {
                            printf("Song found!\n");
                            found = 1;
                        }
                        printf("%d  %s\n", p->num, p->name);
                        return p;
                    }
                }
                if (!found) printf("δ�ҵ�ƥ��ĸ���\n");
                break;
            }
        default:
            printf("������������ԣ�\n");
            continue;
        }
    }
}

void deleteSong(Song **head,List *l)    // ɾ������
{
    int choice;
    printSongList(*head);
    printf("������Ҫɾ���ĸ������: ");
    scanf("%d", &choice);

    Song *current = *head;
    Song *prev = NULL;
    do {
        if (current->num == choice) {
            if (current == *head) {
                *head = current->next;
                if (*head) {
                    (*head)->prev = current->prev;
                    current->prev->next = *head;
                }
            } else {
                prev->next = current->next;
                if (current->next) {
                    current->next->prev = prev;
                }
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    } while (current != *head);

    if (current == *head) {
        printf("������Ų����ڡ�\n");
    }
    savePlaylistToFile(*head,l);
    renumberSongs(head); // �ر��
}

void savePlaylistToFile(Song *head,List *l)     // ���赥���浽�ļ�
{
    renumberSongs(&head);   // �ȶԸ����б��������

    FILE *fp = fopen(l->listAddress, "w");
    if (!fp) {
        MessageBox(NULL, "�޷����ļ���","����", MB_OK);
        return;
    }

    Song *current = head;   
    do {
        fprintf(fp, "%d %d %s %s\n", current->num, current->id, current->name, current->address);
        current = current->next;
    } while (current != head);  // ѭ����������

    fclose(fp);
}

void renumberSongs(Song **head) {
    int number = 1;
    Song *current = *head;

    if (*head == NULL || (*head)->next == *head) {
        return;
    }
    //���±��
    do {
        current->num = number++;
        current = current->next;
    } while (current != *head);
}
