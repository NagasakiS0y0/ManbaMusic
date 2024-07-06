#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

int main() {
    // 打开音乐文件
    mciSendString("open \"./resource/angel_s_song.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);

    // 播放音乐文件
    mciSendString("play mp3", NULL, 0, NULL);

    // 等待用户输入，防止程序立即退出
    printf("Press Enter to stop the music and exit...\n");
    getchar();

    // 停止音乐播放
    mciSendString("stop mp3", NULL, 0, NULL);

    // 关闭音乐文件
    mciSendString("close mp3", NULL, 0, NULL);

    return 0;
}
