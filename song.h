#ifndef SONG_H
#define SONG_H

typedef struct song
{
	int count;  // ���Ŵ���
	char name[50];  // ������
	char singer[50];  // ����
	char address[1024];  // ��������λ��
	struct song *next;  // ָ����һ���ڵ�
} Song;

#endif // SONG_H