#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

int main() {
    // �������ļ�
    mciSendString("open \"./resource/angel_s_song.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);

    // ���������ļ�
    mciSendString("play mp3", NULL, 0, NULL);

    // �ȴ��û����룬��ֹ���������˳�
    printf("Press Enter to stop the music and exit...\n");
    getchar();

    // ֹͣ���ֲ���
    mciSendString("stop mp3", NULL, 0, NULL);

    // �ر������ļ�
    mciSendString("close mp3", NULL, 0, NULL);

    return 0;
}
