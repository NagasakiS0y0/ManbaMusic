#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu1()
{
    printf("            manba music\n");
    printf("*************************************\n");
    printf("            1.���ֿ����\n");
    printf("            2.������\n");
    printf("            3.�����Ƽ�\n");
    printf("            0.�˳�\n");
    printf("*************************************\n");
    printf("��ѡ��\n");
}
void menu_ku()
{
    int i;
    printf("            manba music\n");
    printf("*************************************\n");
    printf("            1.��Ӹ���\n");
    printf("            2.ɾ������\n");
    printf("            3.�޸ĸ���\n");
    printf("            4.�鿴����\n");
    printf("            0.����\n");
    printf("*************************************\n");
    printf("��ѡ��\n");
    scanf("%d",&i);
     switch(i)
    {
        case 0: 
        break;
        default:   
        printf("����\n");
        break;
    }
}

void menu_player()
{
    int i;
    printf("            manba music\n");
    printf("*************************************\n");
    printf("            1.����\n");
    printf("            2.��ͣ\n");
    printf("            3.��һ��\n");
    printf("            4.��һ��\n");
    printf("            5.�Ӵ�����\n");
    printf("            6.��С����\n");
    printf("            7.���ò���ģʽ\n");
    printf("            0.����\n");
    printf("*************************************\n");
    printf("��ѡ��\n");
    scanf("%d",&i);
    switch(i)
    {
        case 0: 
        break;
        default:
        printf("����\n");
        break;
    }
}

void menu_recommend()
{
    int i;
    printf("            manba music\n");
    printf("*************************************\n");
    printf("            1.���������¼\n");
    printf("            2.̽��ģʽ\n");
    printf("            3.�����˿�ζ�Ƽ�\n");
    printf("            0.����\n");
    printf("*************************************\n");
    printf("��ѡ��\n");
    scanf("%d",&i);
    switch(i)
    {
        case 0: 
        break;
        default:
        printf("����\n");
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
        printf("����\n");
        break;
    }
    }
}

