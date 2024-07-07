#ifndef SONG_H
#define SONG_H

typedef struct song
{
    int num;  // 歌曲编号
    int id;  // 歌曲id
	int count;  // 播放次数
	char name[50];  // 歌曲名
	char singer[50];  // 歌手
	char address[1024];  // 歌曲绝对位置
    struct song *prev;  // 指向上一个节点
	struct song *next;  // 指向下一个节点
} Song;

#endif // SONG_H