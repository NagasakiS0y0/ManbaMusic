#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "song.h"
#include "player.c"

Song *addSongFromLib();     //从曲库读取歌曲信息
void printSongList(Song *head);     //输出歌单
void renumberSongs(Song **head);    //重新编号
void selectSongToPlay(Song *head);      //选择歌曲
void addSong(Song **head, List *l);     //添加歌曲
void deleteSong(Song **head,List *l);       //删除歌曲
void addNode(Song **head, Song *newSong);       //添加节点
void renamePlaylist(Song *head,List **l);       //重命名歌单
void readSongsFromFile(Song **head,List *l);    //从文件读取歌曲信息
void savePlaylistToFile(Song *head,List *l);    //保存歌单到文件

void listMain(List *l)      //歌单内部操作，接受指向歌单的指针，可调用
{
    Song *head = NULL;
    Song *current;
    readSongsFromFile(&head,l);   // 从文件中读取歌曲信息并构建链表

    char choice;
    while(1) 
    {
        system("cls");
        printf("[当前歌单]> [%s]\n\n",l->listName);
        printSongList(head);
        printf("*********************************\n");
        printf("   1. 播放音乐    2. 增加歌曲\n");
        printf("   3. 删除歌曲    4. 重命名歌单\n");
        printf("   0. 退出\n");
        printf("*********************************\n");
        printf("请选择功能：[0-4] > ");
        
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
                printf("无效的选择，请重新输入。\n");
                break;
        }
    }

    // 清理链表
    

    return;
}

void readSongsFromFile(Song **head,List *l) {
    FILE *fp;
    fp = fopen(l->listAddress, "r");
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
        printf("请输入要播放的歌曲编号（输入0返回）> ");
        scanf("%d",&choice);
        current = head;
        while (current->num != choice) {
            if (current->next == head) {
                MessageBox(NULL, "歌曲序号不存在，请重新输入！","错误！", MB_OK);
                break; //未找到歌曲，退出
            }
            current = current->next;
        }
        
        if (current->num == choice) {
            player(current);
        }
    }
}

void addNode(Song **head, Song *newSong)    //添加节点
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

void renamePlaylist(Song *head,List **l)    //重命名歌单
{
    char newName[50];
    char cache[256];
    char folder[10];
    strcpy(folder,"List/");
    printf("请输入新的歌单名称: ");
    scanf("%49s", newName);
    strcpy(cache, newName);
    strcat(newName, ".txt"); // 添加 .txt 后缀
    strcat(folder, newName);
    if (rename((*l)->listAddress, folder) != 0) {
        MessageBox(NULL, "重命名失败，请检查文件名或权限", "错误", MB_OK);      // 显示错误信息
    } else {
        MessageBox(NULL, "重命名成功", newName, MB_OK);     // 显示成功信息
    }
    strcpy((*l)->listName, cache);
    strcpy((*l)->listAddress, folder);
}

void addSong(Song **head, List *l)  // 添加歌曲到歌单
{
    Song *newSong = addSongFromLib(); // 获取要添加的歌曲指针
    if (newSong != NULL) {
        // 检查歌单中是否已经有相同的歌曲
        Song *current = *head;
        do {
            if (current && current->id == newSong->id) {
                MessageBox(NULL, "歌曲已经存在于歌单中。","错误！", MB_OK);
                free(newSong);
                return;
            }
            current = current->next;
        } while (current != *head);

        // 歌单中没有相同的歌曲，可以添加
        addNode(head, newSong); // 将歌曲添加到链表末尾
        savePlaylistToFile(*head, l); // 保存歌单到文件
    }
}

void libPrint(Song *libHead)    //输出歌单
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

Song *createFromLib()   //读取文件
{
    Song *libHead=NULL,*p1,*libRear=NULL;//歌单头指针、局部指针、歌单尾指针
    FILE *fp1;
    fp1=fopen("Library/library.txt","r");
    if(fp1==NULL)
    {
        MessageBox(NULL, "曲库文件丢失！","错误！", MB_OK);
        return NULL;
    }

    p1=(Song*)malloc(LEN);//创建新节点

    if(p1==NULL){
        MessageBox(NULL, "内存分配错误！","错误！", MB_OK);
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
    return(libHead);//返回歌单头指针
}

Song *addSongFromLib()  //从曲库添加歌曲
{
    void libPrint(Song *libHead);
    Song *createFromLib();

    int m;    //功能选择菜单的判断变量
    char n;
    int length=0;
    int found;
    char y[20];     //歌曲名字
    Song *p;
    Song *h;    //歌单头指针
    h=createFromLib();      //创建歌单
    while(1)    //功能选择菜单
    {
        system("cls");
        printf("***************曲库***************\n");
        libPrint(h);    //输出歌单
        printf("*********************************\n");
        printf("1. 搜索序号添加     2. 搜索歌名添加\n");
        printf("0. 返回上级\n");
        printf("*********************************\n");
        printf("请选择功能：[0-2] > ");
        n=getch();
        switch (n)
        {
        case 0:
            free(h);
            return NULL;
        case 1:
            {
                printf("请输入要搜索的歌曲序号\n");
                scanf("%d", &m);
                found = 0;
                for (p = h; p != NULL; p = p->next)
                {
                    if (p->num == m) // 判断是否找到歌曲序号
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
                if (!found) printf("未找到匹配的歌曲\n");
                break;
            }
        case 2:
            {
                printf("请输入要搜索的歌曲名\n");
                scanf("%s", y);
                found = 0;
                for (p = h; p != NULL; p = p->next)
                {
                    if (strcmp(p->name, y) == 0) // 判断是否找到歌曲名
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
                if (!found) printf("未找到匹配的歌曲\n");
                break;
            }
        default:
            printf("输入出错，请重试！\n");
            continue;
        }
    }
}

void deleteSong(Song **head,List *l)    // 删除歌曲
{
    int choice;
    printSongList(*head);
    printf("请输入要删除的歌曲编号: ");
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
        printf("歌曲编号不存在。\n");
    }
    savePlaylistToFile(*head,l);
    renumberSongs(head); // 重编号
}

void savePlaylistToFile(Song *head,List *l)     // 将歌单保存到文件
{
    renumberSongs(&head);   // 先对歌曲列表进行排序

    FILE *fp = fopen(l->listAddress, "w");
    if (!fp) {
        MessageBox(NULL, "无法打开文件！","错误！", MB_OK);
        return;
    }

    Song *current = head;   
    do {
        fprintf(fp, "%d %d %s %s\n", current->num, current->id, current->name, current->address);
        current = current->next;
    } while (current != head);  // 循环遍历链表

    fclose(fp);
}

void renumberSongs(Song **head) {
    int number = 1;
    Song *current = *head;

    if (*head == NULL || (*head)->next == *head) {
        return;
    }
    //重新编号
    do {
        current->num = number++;
        current = current->next;
    } while (current != *head);
}
