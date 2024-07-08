#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // For directory handling
#include <sys/stat.h> // For stat function
#include <time.h> // For time and rand functions
#include "song.h"


// 生成4位随机ID
int generateRandomID() {
    // Seed the random number generator
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    return rand() % 9000 + 1000; // Generates a 4-digit number between 1000 and 9999
}

// 读取指定目录下的所有.wav文件，并将信息写入library.txt
void scanAndSaveWavFiles(const char *directoryPath) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directoryPath)) != NULL) {
        int num = 1; // 歌曲编号
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".wav") != NULL) { // Check if it's a .wav file
                char filePath[256];
                snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, ent->d_name);
                struct stat st;
                if (stat(filePath, &st) == 0 && S_ISREG(st.st_mode)) {
                    Song song;
                    song.num = num++;
                    song.id = generateRandomID();
                    song.count = 0;
                    strncpy(song.name, ent->d_name, sizeof(song.name) - 1);
                    strncpy(song.address, filePath, sizeof(song.address) - 1);
                    song.address[sizeof(song.address) - 1] = '\0'; // Ensure null termination

                    // Write to library.txt
                    FILE *fp = fopen("library.txt", "a");
                    if (fp != NULL) {
                        fprintf(fp, "%d|%d|%d|%s|%s\n", song.num, song.id, song.count, song.name, song.address);
                        fclose(fp);
                    }
                }
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
        return;
    }
}

int main() {
    char directoryPath[256];
    printf("请输入要扫描的文件夹路径: ");
    fgets(directoryPath, sizeof(directoryPath), stdin);
    directoryPath[strcspn(directoryPath, "\n")] = 0; // Remove newline character

    // Clear the library.txt file before writing new data
    FILE *fp = fopen("library.txt", "w");
    if (fp != NULL) {
        fclose(fp);
    }

    scanAndSaveWavFiles(directoryPath);
    printf("扫描完成，信息已保存到library.txt。\n");

    return 0;
}