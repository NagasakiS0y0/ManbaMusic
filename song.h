#ifndef SONG_H
#define SONG_H

typedef struct song
{
    int num;  // �������
    int id;  // ����id
	int count;  // ���Ŵ���
	char name[256];  // ������
	char address[256];  // ��������λ��
    struct song *prev;  // ָ����һ���ڵ�
	struct song *next;  // ָ����һ���ڵ�
} Song;

typedef struct list
{
    int listNum;
    char listName[50];
    char listAddress[256];
    struct list *next;
} List;

#define LEN sizeof(Song)    //�赥�ṹ�峤��

#endif // SONG_H