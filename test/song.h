#ifndef SONG_H
#define SONG_H

typedef struct song
{
    int num;  // �������
    int id;  // ����id
	int count;  // ���Ŵ���
	char name[50];  // ������
	char address[256];  // ��������λ��
    struct song *prev;  // ָ����һ���ڵ�
	struct song *next;  // ָ����һ���ڵ�
} Song;

#endif // SONG_H