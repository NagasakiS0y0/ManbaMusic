#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "song.h"
#include "player.c"

// 函数声明
Song *addSongFromLib();
void printSongList(Song *head);
void renumberSongs(Song **head);
void selectSongToPlay(Song *head);
void addSong(Song **head, List *l);
void deleteSong(Song **head,List *l);
void addNode(Song **head, Song *newSong);
void renamePlaylist(Song *head,List **l);
void readSongsFromFile(Song **head,List *l);
void savePlaylistToFile(Song *head,List *l);

void listMain(List *l) 
{
    Song *head = NULL; // 初始化链表头指针
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

/*int main()
{
    List *l = (List*)malloc(sizeof(List));
    l->listNum=1;   //序号赋值
    strcpy(l->listName,"123");    //歌名赋值
    strcpy(l->listAddress,"List/123.txt");
    listMain(l);
    return 0;
}*/

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
    Song *current = head; // 将current初始化为head
    
    while (1) { // 使用无限循环，直到用户选择退出
        system("cls");
        printSongList(head);
        printf("请输入要播放的歌曲编号（输入0退出）> ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            return; // 用户选择退出
        }
        
        current = head; // 每次循环开始时重置current为head
        while (current->num != choice) {
            if (current->next == head) {
                printf("歌曲编号不存在，请重新输入。\n");
                break; // 如果到达链表尾部而未找到歌曲，则退出循环
            }
            current = current->next;
        }
        
        if (current->num == choice) {
            player(current); // 找到歌曲，播放
        }
    }
}

void addNode(Song **head, Song *newSong)
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

void renamePlaylist(Song *head,List **l)
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

void addSong(Song **head, List *l)
{
    Song *newSong = addSongFromLib(); // 获取要添加的歌曲指针
    if (newSong != NULL) {
        // 检查歌单中是否已经有相同的歌曲
        Song *current = *head;
        do {
            if (current && current->id == newSong->id) {
                MessageBox(NULL, "歌曲已经存在于歌单中。","错误！", MB_OK);
                free(newSong); // 释放新歌曲的内存
                return;
            }
            current = current->next;
        } while (current != *head);

        // 歌单中没有相同的歌曲，可以添加
        addNode(head, newSong); // 将歌曲添加到链表末尾
        savePlaylistToFile(*head, l); // 保存歌单到文件
    }
}

void libPrint(Song *libHead)//输出歌单
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

Song *createFromLib()//    读取文件
{
    Song *libHead=NULL,*p1,*libRear=NULL;//歌单头指针、局部指针、歌单尾指针
    FILE *fp1;
    fp1=fopen("Library/library.txt","r");
    if(fp1==NULL)
    {
        printf("曲库文件丢失!\n");
        return NULL;
    }

    p1=(Song*)malloc(LEN);//创建新节点

    if(p1==NULL){
        printf("内存分配错误！\n");
        exit(1);
    }
    while(fscanf(fp1,"%d%d%d%s%s",&p1->num,&p1->id,&p1->count,p1->name,p1->address)!=EOF)//读取文件并判断读取是否结束
    {
        if(libHead==NULL){//歌单为空
            libHead=p1;//歌单头指针指向新节点
        }else{
            libRear->next=p1;//歌单尾指针指向新节点
        }
        libRear=p1;
        p1=(Song*)malloc(LEN);//创建新节点
    }
    libRear->next=NULL;//歌单尾指针指向NULL
    fclose(fp1);
    return(libHead);//返回歌单头指针
}

Song *addSongFromLib()
{
    void libPrint(Song *libHead);
    Song *createFromLib();

    int n,m;//功能选择菜单的判断变量
    int length=0;
    int found;
    char y[20];//歌曲名字
    Song *p;
    Song *h;//歌单头指针
    h=createFromLib();//创建歌单
    while(1)//功能选择菜单
    {
        system("cls");
        printf("***************曲库***************\n");
        libPrint(h);//输出歌单
        printf("*********************************\n");
        printf("1. 搜索序号添加     2. 搜索歌名添加\n");
        printf("0. 返回上级\n");
        printf("*********************************\n");
        printf("请选择功能：[0-2] > ");
        scanf("%d",&n);
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
                // 如果删除的是头节点
                *head = current->next;
                if (*head) {
                    // 更新新头节点的prev指针
                    (*head)->prev = current->prev;
                    // 更新链表最后一个节点的next指针
                    current->prev->next = *head;
                }
            } else {
                // 如果删除的不是头节点
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
    renumberSongs(head); // 在这里调用renumberSongs函数
}

void savePlaylistToFile(Song *head,List *l)     // 将歌单保存到文件
{
    renumberSongs(&head);   // 先对歌曲列表进行排序

    FILE *fp = fopen(l->listAddress, "w");
    if (!fp) {
        fprintf(stderr, "无法打开文件\n");
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

    // 如果链表为空或只有一个元素，无需重编号
    if (*head == NULL || (*head)->next == *head) {
        return;
    }

    // 遍历链表，重新设置歌曲编号
    do {
        current->num = number++;
        current = current->next;
    } while (current != *head);
}
