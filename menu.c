#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu1()
{
    printf("            manba music\n");
    printf("*************************************\n");
    printf("            1.音乐库管理\n");
    printf("            2.播放器\n");
    printf("            3.歌曲推荐\n");
    printf("            0.退出\n");
    printf("*************************************\n");
    printf("请选择：\n");
}
void menu_ku()
{
    int i;
    printf("            manba music\n");
    printf("*************************************\n");
    printf("            1.添加歌曲\n");
    printf("            2.删除歌曲\n");
    printf("            3.修改歌曲\n");
    printf("            4.查看歌曲\n");
    printf("            0.返回\n");
    printf("*************************************\n");
    printf("请选择：\n");
    scanf("%d",&i);
     switch(i)
    {
        case 0: 
        break;
        default:   
        printf("错误\n");
        break;
    }
}

void menu_player()
{
    int i;
    printf("            manba music\n");
    printf("*************************************\n");
    printf("            1.播放\n");
    printf("            2.暂停\n");
    printf("            3.上一曲\n");
    printf("            4.下一曲\n");
    printf("            5.加大音量\n");
    printf("            6.减小音量\n");
    printf("            7.设置播放模式\n");
    printf("            0.返回\n");
    printf("*************************************\n");
    printf("请选择：\n");
    scanf("%d",&i);
    switch(i)
    {
        case 0: 
        break;
        default:
        printf("错误\n");
        break;
    }
}

void menu_recommend()
{
    int i;
    printf("            manba music\n");
    printf("*************************************\n");
    printf("            1.听歌次数记录\n");
    printf("            2.探索模式\n");
    printf("            3.按个人口味推荐\n");
    printf("            0.返回\n");
    printf("*************************************\n");
    printf("请选择：\n");
    scanf("%d",&i);
    switch(i)
    {
        case 0: 
        break;
        default:
        printf("错误\n");
        break;
    }
}

void menu()
{
    int k;
    while (1)
    {
    system("cls");
    menu1();
    scanf("%d",&k);
    switch (k)
    {
    case 1:
        system("cls");
        menu_ku();
        break;
    case 2:
        system("cls");
        menu_player();
        break;
    case 3:
        system("cls");
        menu_recommend();
        break;
    case 0:
    return 1;
    default:
        printf("错误\n");
        break;
    }
    }
}

