#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define LEN sizeof(struct song)
#ifndef SONG_H
#define SONG_H

typedef struct song
{
    struct song *prev;
	int num;
    int id;
    int count;
	char name[50];
	char address[1024];
	struct song *next;
} Song;

#endif
void menu1()
{
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            1.��Ӹ���\n");
    printf("            2.ɾ������\n");
    printf("            3.��������\n");
    printf("            4.�鿴������\n");
    printf("            0.����ǰ�ò˵�\n");
    printf("*************************************\n");
    printf("����������ѡ��[0-4]\n");
}

struct song * create()//����������
{
    struct song *head=NULL,*p1,*rear=NULL;
    p1=(struct song *)malloc(LEN);
    FILE *fp1;
    fp1=fopen("song.txt","r");
    if(fp1==NULL)
    {
        puts("�޷����ļ���");
        exit(0);
    }
    while (fscanf(fp1,"%d%s%s",&p1->id,p1->name,p1->address)!=EOF)
    {
        if (head==NULL)
        {
            head=p1;
            rear=p1;
        }
        else
        {
            rear->next=p1;
            rear=p1;
        }
        rear=p1;
        p1=(struct song*)malloc(LEN);
    }
    rear->next=head;
    fclose(fp1);
    return(head);
}

void print(struct song *head)//��ӡ������
{
    struct song *p;
    p = head;
    if (head == NULL)
    {
        printf("������Ϊ�ա�\n");
        return;
    }
    do
    {
        printf("%d %d %s\n", p->num, p->id, p->name);
        p = p->next;
    } 
    while (p != head);
    printf("\n");
}

void save(struct song *head)//���������
{
    struct song *p;
    p=head;
    FILE *fp2;
    fp2=fopen("song.txt","w");
    if(fp2==NULL)
    {
        puts("�޷����ļ���");
        exit(0);
    }
    if (head!=NULL)
    {
        while(1)
        {
            fprintf(fp2,"%d %d %s\n",p->num,p->id,p->name);
            p=p->next;
            if (p==head)
            {
                break;
            }
        }
    }
    fclose(fp2);
}

/**
 * ������������
 * �ú����ṩ��һ������ʽ�������棬�����û����ո���ID���ļ�������������
 * ����ҵ�ƥ��ĸ���������ӡ�����ı�š�ID�����ơ�
 */
void search(struct song *head)
{
    struct song *p; // ����һ��ָ�����ڱ��������б�
    p = head; // ��ָ��ָ���б�ͷ��
    int j = 0, i = 0; // ����������ڴ洢�û���ѡ���������ID
    char x[50]; // ����һ���ַ��������ڴ洢�û�������ļ���

    // ��ӡ��ӭ��Ϣ������ѡ��
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            ��������ҷ�ʽ��\n");
    printf("            1.��id����\n");
    printf("            2.���ļ�������\n");
    printf("            0.����ǰ�ò˵�\n");
    printf("*************************************\n");

    // ��ȡ�û���ѡ��
    printf("����������ѡ��[0-2]\n");
    scanf("%d", &j);

    // �����û���ѡ����в�ͬ������
    switch (j)
    {
        case 1:
            // ��ID����
            printf("������Ҫ���ҵ�id:");
            scanf("%d", &i);
            while (p != NULL)
            {
                if (p->id == i)
                {
                    // �ҵ�ƥ��ĸ�������ӡ��Ϣ
                    printf("%d %d %s\n", p->num, p->id, p->name);
                    break;
                }
                else
                {
                    // û���ҵ�ƥ��ĸ�������ӡ��ʾ��Ϣ���˳�ѭ��
                    printf("û���ҵ��ø�����\n");
                    break;
                }
                p = p->next; // �ƶ�����һ�׸���
            }
            break;

        case 2:
            // ���ļ�������
            printf("������Ҫ���ҵ��ļ���");
            scanf("%s", &x);
            while (p != NULL)
            {
                if (strcmp(p->name, x) == 0)
                {
                    // �ҵ�ƥ��ĸ�������ӡ��Ϣ
                    printf("%d %d %s\n", p->num, p->id, p->name);
                    break;
                }
                else
                {
                    // û���ҵ�ƥ��ĸ�������ӡ��ʾ��Ϣ���˳�ѭ��
                    printf("û���ҵ��ø�����\n");
                    break;
                }
                p = p->next; // �ƶ�����һ�׸���
            }
            break;

        case 0:
            // �û�ѡ�񷵻�ǰ�ò˵���ֱ���˳�����
            break;

        default:
            // �û���������Ч��ѡ�񣬴�ӡ��ʾ��Ϣ
            printf("\n ����������������룡\n");
    }
}


/**
 * ɾ��������ָ����ŵĽڵ�
 * @param head �����ͷָ��
 * @param x Ҫɾ���Ľڵ�ı��
 * @return ���ش���������ͷָ��
 */
struct song *Del_Node(struct song *head, int x)
{
    struct song *p, *q;
    int found = 0; // ���ڱ���Ƿ��ҵ�Ҫɾ���Ľڵ�
    p = head;
    q = NULL;

    if (head != NULL)
    {
        while (1)
        {
            if (p->num == x)
            {
                found = 1; // �ҵ�Ҫɾ���Ľڵ�
                break;
            }
            else
            {
                q = p; // ��¼ǰһ���ڵ�
                p = p->next; // �ƶ�����һ���ڵ�
            }
            if (p == head)
            {
                break; // �����ص�ͷ�ڵ㣬˵��������û��Ҫɾ���Ľڵ�
            }
        }
    }

    if (found == 1)
    {
        if (p == head)
        {
            head = p->next; // ���Ҫɾ���Ľڵ���ͷ�ڵ㣬����ͷָ��
            q = p;
            while (q->next != p)
            {
                q = q->next; // �ҵ�β�ڵ㣬���ڶϿ�����
            }
            q->next = head; // �Ͽ�����
        }
        else
        {
            q->next = p->next; // ���Ҫɾ���Ľڵ㲻��ͷ�ڵ㣬ֱ�ӶϿ�����
        }
        free(p); // �ͷű�ɾ���ڵ���ڴ�
    }
    else
    {
        printf("�Ҳ�������!\n"); // ���δ�ҵ�Ҫɾ���Ľڵ㣬������ʾ
    }

    return head; // ���ش���������ͷָ��
}

/*
 * �ڸ����б��в���һ���½ڵ�
 * �˺������ȼ��������ƺ�ID�Ƿ������ļ�"list.txt"�д��ڣ�
 * ������ڣ��򲻲����½ڵ㲢����ԭ�б�ͷ��ָ�룻
 * ��������ڣ�������ڴ���½ڵ㣬���Ƹ������ƺ�ID��
 * �������б��Ƿ�Ϊ�������½ڵ�����ӣ���󷵻ظ��º���б�ͷ��ָ�롣
 */
struct song *insert_Node(struct song *head, int x, char y[50])
{
    struct song *p, *q, *s;
    p = head;
    q = NULL;
    s = (struct song *)malloc(LEN);
    strcpy(s->name, y);
    s->id = x;

    /* ���ļ��Լ������Ƿ��Ѵ��� */
    FILE *fp = fopen("list.txt", "r");
    int id;
    char name[50];
    int found;
    found = 0;

    /* �����ļ��е�ÿһ�У�����Ƿ������ͬ�ĸ������ƺ�ID */
    while (fscanf(fp, "%d %s", &id, name) != EOF)
    {
        if (strcmp(name, y) == 0 && id == x)
        {
            found = 1;
            break;
        }
    }
    fclose(fp);

    /* ��������Ѵ��ڣ�����ʾ���󲢷���ԭ�б�ͷ��ָ�� */
    if (found == 0)
    {
        printf("���ݴ��󣺸����������ֿ��С�\n");
        return head;
    }

    /* ����б�Ϊ�գ����½ڵ�����ΪΨһ�ڵ� */
    if (head == NULL)
    {
        s->next = s;
        head = s;
    }
    else
    {
        /* �ҵ��б�����һ���ڵ㣬�����½ڵ���뵽����� */
        while (p->next != head)
        {
            q = p;
            p = p->next;
        }
        q->next = s;
        s->next = head;
    }
    return head;
}


void search_way(char *way) 
{
    WIN32_FIND_DATA Data;// �洢�ļ���Ϣ�Ľṹ��
    HANDLE hFind;// ���Ҿ��

    char path[1024];// ����һ���ַ������飬���ڴ洢����·��
    snprintf(path, sizeof(path), "%s\\*.mp3", way);// �� \*.mp3 ���ӵ��ļ���·������
    printf("��������·��: %s\n", path);
    hFind = FindFirstFile(path, &Data);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("��Ŀ¼��û���ҵ�MP3�ļ���\n");
        return;
    }
        FILE *fp1;
        fp1=fopen("list.txt","w");
        FILE *fp2;
        fp2=fopen("song.txt","w");
        char address[1024];
        strcpy(address, path);
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// �ҵ��ļ����ĺ�׺λ��
            if (dotPos != NULL) // ɾ���ļ����еĺ�׺
            {
                *dotPos = '\0';
            }
            printf("�ҵ�MP3�ļ�: %s.mp3\n", Data.cFileName);
            fprintf(fp1, "%s %s\n", Data.cFileName, address);
            fprintf(fp2, "%s %s\n", Data.cFileName, address); // д����ź��ļ����� song.txt
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// �رղ��Ҿ��
        fclose(fp1);
        fclose(fp2);
}

/*
 * �Ը����б��������
 * �ú���ͨ��ð�������㷨�Ը����б�����������Ȱ��ո�����ţ�num����������
 * Ȼ������Ϊ�����б��е�ÿһ������1��ʼ��˳���š�
 */
void paixu(struct song *head) 
{
    struct song *p, *q;
    int num,id;
    char name[50], address[1024];

    /* ��ʼ��ָ��pΪ�б�ͷ�� */
    p = head;
    /* ���б�Ϊ��ʱ�������� */
    if (p != NULL) 
    {
        /* ʹ��ð��������б�������� */
        while(1)
        {
            /* ��ʼ��ָ��qΪp����һ���ڵ㣬�������б��бȽ� */
            q = p->next;
            /* �����б�ֱ���ص�ͷ�� */
            while (q!=head) 
            {
                /* �����ǰ�ڵ�ĸ�����Ŵ�����һ���ڵ�ı�ţ��򽻻����ǵ���Ϣ */
                if (p->num>q->num) 
                {
                    /* ����������� */
                    num=p->num;
                    p->num=q->num;
                    q->num=num;
                    /* ��������ID */
                    id=p->id;
                    p->id=q->id;
                    q->id=id;
                    /* ������������ */
                    strcpy(name, p->name);
                    strcpy(p->name, q->name);
                    strcpy(q->name, name);
                    /* ����������ַ */
                    strcpy(address, p->address);
                    strcpy(p->address, q->address);
                    strcpy(q->address, address);
                }   
                /* �ƶ�ָ��q����һ���ڵ� */
                q=q->next;
            }
            /* �ƶ�ָ��p����һ���ڵ� */
            p=p->next;
            /* ���p�ص�ͷ������������ɣ�����ѭ�� */
            if (p==head) 
            {
                break; 
            }
        }

        /* ����Ϊ�����б��е�ÿһ������1��ʼ��˳���� */
        p = head;
        int i = 1;
        if(p != NULL) 
        {
            while(1)
            {
                /* ���ڵ����˳���� */
                p->num=i++;
                /* �ƶ�ָ��p����һ���ڵ� */
                p=p->next;
                /* ���p�ص�ͷ����������ɣ�����ѭ�� */
                if (p==head) 
                {
                    break;
                }
            }
        }
    }
}

void give_id(struct song *head) //����������
{
    struct song *p = head;
    int id;
    int repeat;
    repeat=0;
    struct song *q;
    
    FILE *fp1 = fopen("list.txt", "w");
    FILE *fp2 = fopen("song.txt", "w");
    if (fp1 == NULL) 
    {
        puts("�޷��� list.txt �ļ���");
        return;
    }
    
    srand(time(0));

    while (p != NULL) 
    {
        do 
        {
            id = rand() % 9000 + 1000;
            q = head;

            while (q != NULL) 
            {
                if (q->id == id) 
                {
                    repeat = 1;
                    break;
                }
                q = q->next;
                if (q == head) 
                {
                    break;
                }
            }
        } while (repeat==1);

        p->id = id;
        p = p->next;
        if (p== head) 
        {
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
}

/*void copy(struct song *head) //Ҳ�����е�����
{
    if (head == NULL) 
    {
        printf("����Ϊ�ա�\n");
        return;
    }

    struct song *p = head;
    FILE *fp1 = fopen("list.txt", "r");
    FILE *fp2 = fopen("song.txt", "w");

    
    do {
        fprintf(fp2, "%s %s\n", p->name, p->address);
        p = p->next;
    } while (p != head);
        fclose(fp1);
        fclose(fp2);
}*/

int main()
{
    int i, j, k;
    char x[50], y[1024];
    struct song *h;
    h = NULL;
    give_id(h);
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            �Ƿ�������ֿ⣿\n");
    printf("            1.���������ֿ�\n");
    printf("            2.�Ѵ������ֿ�\n");
    printf("            0.����ǰ�ò˵�\n");
    printf("*************************************\n");
    printf("����������ѡ��[0-2]\n");
    scanf("%d", &i);
    while (1)
    {
        if (i == 1)
        {
            system("cls");
            printf("���ڴ������ֿ��ļ���\n");
            char *way = "D:\\code\\C language\\7\\project\\git\\output"; // �滻Ϊʵ��·��
            search_way(way); // ���� search �����ҳ�.mp3�ļ�
            printf("������ɣ�\n");
            //give_id(h);
            //copy(h);
            h = create();
            printf("�����ĸ���������:\n");
            paixu(h);
            print(h);
            break;
        }
        else if (i == 2)
        {
            system("cls");
            printf("���ڴӸ������ļ���ȡ����\n");
            //copy(h);
            h = create();
            paixu(h);
            printf("��ȡ�ɹ�!\n");
            printf("�����б�����:\n");
            print(h);
            break;
        }
        else
        {
            printf("\n ����������������룡\n");
        }
    }
    // ��ѭ���ȴ��û�ѡ�����
    while (1)
    {
        menu1();
        scanf("%d", &j);
        switch (j)
        {
            case 1:
                printf("��������Ҫ��ӵĸ������ļ��� ���֣�:\n");
                scanf("%s %s", &x, &y);
                h = insert_Node(h, x, y);
                paixu(h);
                save(h);
                printf("��ӳɹ���\n");
                print(h);
                break;
            case 2:
                printf("��������Ҫɾ���ĸ�������ţ�:\n");
                scanf("%d", &k);
                h = Del_Node(h, k);
                paixu(h);
                system("cls");
                save(h);
                printf("ɾ���ɹ���\n");
                break;
            case 3:
                printf("��������Ҫ�����ĸ���:\n");
                search(h);
                break;
            case 4:
                system("cls");
                printf("����������:\n");
                print(h);
                break;
            case 0:
                return 1; // ����ǰ�ò˵�
            default:
                printf("\n ����������������룡\n");
        };
    }
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define LEN sizeof(struct song)
#ifndef SONG_H
#define SONG_H

typedef struct song
{
    struct song *prev;
	int num;
    int id;
    int count;
	char name[50];
	char address[1024];
	struct song *next;
} Song;

#endif
void menu1()
{
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            1.��Ӹ���\n");
    printf("            2.ɾ������\n");
    printf("            3.��������\n");
    printf("            4.�鿴������\n");
    printf("            0.����ǰ�ò˵�\n");
    printf("*************************************\n");
    printf("����������ѡ��[0-4]\n");
}

struct song * create()//����������
{
    struct song *head=NULL,*p1,*rear=NULL;
    p1=(struct song *)malloc(LEN);
    FILE *fp1;
    fp1=fopen("song.txt","r");
    if(fp1==NULL)
    {
        puts("�޷����ļ���");
        exit(0);
    }
    while (fscanf(fp1,"%d%s%s",&p1->id,p1->name,p1->address)!=EOF)
    {
        if (head==NULL)
        {
            head=p1;
            rear=p1;
        }
        else
        {
            rear->next=p1;
            rear=p1;
        }
        rear=p1;
        p1=(struct song*)malloc(LEN);
    }
    rear->next=head;
    fclose(fp1);
    return(head);
}

void print(struct song *head)//��ӡ������
{
    struct song *p;
    p = head;
    if (head == NULL)
    {
        printf("������Ϊ�ա�\n");
        return;
    }
    do
    {
        printf("%d %d %s\n", p->num, p->id, p->name);
        p = p->next;
    } 
    while (p != head);
    printf("\n");
}

void save(struct song *head)//���������
{
    struct song *p;
    p=head;
    FILE *fp2;
    fp2=fopen("song.txt","w");
    if(fp2==NULL)
    {
        puts("�޷����ļ���");
        exit(0);
    }
    if (head!=NULL)
    {
        while(1)
        {
            fprintf(fp2,"%d %d %s\n",p->num,p->id,p->name);
            p=p->next;
            if (p==head)
            {
                break;
            }
        }
    }
    fclose(fp2);
}

/**
 * ������������
 * �ú����ṩ��һ������ʽ�������棬�����û����ո���ID���ļ�������������
 * ����ҵ�ƥ��ĸ���������ӡ�����ı�š�ID�����ơ�
 */
void search(struct song *head)
{
    struct song *p; // ����һ��ָ�����ڱ��������б�
    p = head; // ��ָ��ָ���б�ͷ��
    int j = 0, i = 0; // ����������ڴ洢�û���ѡ���������ID
    char x[50]; // ����һ���ַ��������ڴ洢�û�������ļ���

    // ��ӡ��ӭ��Ϣ������ѡ��
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            ��������ҷ�ʽ��\n");
    printf("            1.��id����\n");
    printf("            2.���ļ�������\n");
    printf("            0.����ǰ�ò˵�\n");
    printf("*************************************\n");

    // ��ȡ�û���ѡ��
    printf("����������ѡ��[0-2]\n");
    scanf("%d", &j);

    // �����û���ѡ����в�ͬ������
    switch (j)
    {
        case 1:
            // ��ID����
            printf("������Ҫ���ҵ�id:");
            scanf("%d", &i);
            while (p != NULL)
            {
                if (p->id == i)
                {
                    // �ҵ�ƥ��ĸ�������ӡ��Ϣ
                    printf("%d %d %s\n", p->num, p->id, p->name);
                    break;
                }
                else
                {
                    // û���ҵ�ƥ��ĸ�������ӡ��ʾ��Ϣ���˳�ѭ��
                    printf("û���ҵ��ø�����\n");
                    break;
                }
                p = p->next; // �ƶ�����һ�׸���
            }
            break;

        case 2:
            // ���ļ�������
            printf("������Ҫ���ҵ��ļ���");
            scanf("%s", &x);
            while (p != NULL)
            {
                if (strcmp(p->name, x) == 0)
                {
                    // �ҵ�ƥ��ĸ�������ӡ��Ϣ
                    printf("%d %d %s\n", p->num, p->id, p->name);
                    break;
                }
                else
                {
                    // û���ҵ�ƥ��ĸ�������ӡ��ʾ��Ϣ���˳�ѭ��
                    printf("û���ҵ��ø�����\n");
                    break;
                }
                p = p->next; // �ƶ�����һ�׸���
            }
            break;

        case 0:
            // �û�ѡ�񷵻�ǰ�ò˵���ֱ���˳�����
            break;

        default:
            // �û���������Ч��ѡ�񣬴�ӡ��ʾ��Ϣ
            printf("\n ����������������룡\n");
    }
}


/**
 * ɾ��������ָ����ŵĽڵ�
 * @param head �����ͷָ��
 * @param x Ҫɾ���Ľڵ�ı��
 * @return ���ش���������ͷָ��
 */
struct song *Del_Node(struct song *head, int x)
{
    struct song *p, *q;
    int found = 0; // ���ڱ���Ƿ��ҵ�Ҫɾ���Ľڵ�
    p = head;
    q = NULL;

    if (head != NULL)
    {
        while (1)
        {
            if (p->num == x)
            {
                found = 1; // �ҵ�Ҫɾ���Ľڵ�
                break;
            }
            else
            {
                q = p; // ��¼ǰһ���ڵ�
                p = p->next; // �ƶ�����һ���ڵ�
            }
            if (p == head)
            {
                break; // �����ص�ͷ�ڵ㣬˵��������û��Ҫɾ���Ľڵ�
            }
        }
    }

    if (found == 1)
    {
        if (p == head)
        {
            head = p->next; // ���Ҫɾ���Ľڵ���ͷ�ڵ㣬����ͷָ��
            q = p;
            while (q->next != p)
            {
                q = q->next; // �ҵ�β�ڵ㣬���ڶϿ�����
            }
            q->next = head; // �Ͽ�����
        }
        else
        {
            q->next = p->next; // ���Ҫɾ���Ľڵ㲻��ͷ�ڵ㣬ֱ�ӶϿ�����
        }
        free(p); // �ͷű�ɾ���ڵ���ڴ�
    }
    else
    {
        printf("�Ҳ�������!\n"); // ���δ�ҵ�Ҫɾ���Ľڵ㣬������ʾ
    }

    return head; // ���ش���������ͷָ��
}

/*
 * �ڸ����б��в���һ���½ڵ�
 * �˺������ȼ��������ƺ�ID�Ƿ������ļ�"list.txt"�д��ڣ�
 * ������ڣ��򲻲����½ڵ㲢����ԭ�б�ͷ��ָ�룻
 * ��������ڣ�������ڴ���½ڵ㣬���Ƹ������ƺ�ID��
 * �������б��Ƿ�Ϊ�������½ڵ�����ӣ���󷵻ظ��º���б�ͷ��ָ�롣
 */
struct song *insert_Node(struct song *head, int x, char y[50])
{
    struct song *p, *q, *s;
    p = head;
    q = NULL;
    s = (struct song *)malloc(LEN);
    strcpy(s->name, y);
    s->id = x;

    /* ���ļ��Լ������Ƿ��Ѵ��� */
    FILE *fp = fopen("list.txt", "r");
    int id;
    char name[50];
    int found;
    found = 0;

    /* �����ļ��е�ÿһ�У�����Ƿ������ͬ�ĸ������ƺ�ID */
    while (fscanf(fp, "%d %s", &id, name) != EOF)
    {
        if (strcmp(name, y) == 0 && id == x)
        {
            found = 1;
            break;
        }
    }
    fclose(fp);

    /* ��������Ѵ��ڣ�����ʾ���󲢷���ԭ�б�ͷ��ָ�� */
    if (found == 0)
    {
        printf("���ݴ��󣺸����������ֿ��С�\n");
        return head;
    }

    /* ����б�Ϊ�գ����½ڵ�����ΪΨһ�ڵ� */
    if (head == NULL)
    {
        s->next = s;
        head = s;
    }
    else
    {
        /* �ҵ��б�����һ���ڵ㣬�����½ڵ���뵽����� */
        while (p->next != head)
        {
            q = p;
            p = p->next;
        }
        q->next = s;
        s->next = head;
    }
    return head;
}


void search_way(char *way) 
{
    WIN32_FIND_DATA Data;// �洢�ļ���Ϣ�Ľṹ��
    HANDLE hFind;// ���Ҿ��

    char path[1024];// ����һ���ַ������飬���ڴ洢����·��
    snprintf(path, sizeof(path), "%s\\*.mp3", way);// �� \*.mp3 ���ӵ��ļ���·������
    printf("��������·��: %s\n", path);
    hFind = FindFirstFile(path, &Data);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("��Ŀ¼��û���ҵ�MP3�ļ���\n");
        return;
    }
        FILE *fp1;
        fp1=fopen("list.txt","w");
        FILE *fp2;
        fp2=fopen("song.txt","w");
        char address[1024];
        strcpy(address, path);
        do 
        {
            char *dotPos = strrchr(Data.cFileName, '.');// �ҵ��ļ����ĺ�׺λ��
            if (dotPos != NULL) // ɾ���ļ����еĺ�׺
            {
                *dotPos = '\0';
            }
            printf("�ҵ�MP3�ļ�: %s.mp3\n", Data.cFileName);
            fprintf(fp1, "%s %s\n", Data.cFileName, address);
            fprintf(fp2, "%s %s\n", Data.cFileName, address); // д����ź��ļ����� song.txt
        } 
        while (FindNextFile(hFind, &Data) != 0); 
        FindClose(hFind);// �رղ��Ҿ��
        fclose(fp1);
        fclose(fp2);
}

/*
 * �Ը����б��������
 * �ú���ͨ��ð�������㷨�Ը����б�����������Ȱ��ո�����ţ�num����������
 * Ȼ������Ϊ�����б��е�ÿһ������1��ʼ��˳���š�
 */
void paixu(struct song *head) 
{
    struct song *p, *q;
    int num,id;
    char name[50], address[1024];

    /* ��ʼ��ָ��pΪ�б�ͷ�� */
    p = head;
    /* ���б�Ϊ��ʱ�������� */
    if (p != NULL) 
    {
        /* ʹ��ð��������б�������� */
        while(1)
        {
            /* ��ʼ��ָ��qΪp����һ���ڵ㣬�������б��бȽ� */
            q = p->next;
            /* �����б�ֱ���ص�ͷ�� */
            while (q!=head) 
            {
                /* �����ǰ�ڵ�ĸ�����Ŵ�����һ���ڵ�ı�ţ��򽻻����ǵ���Ϣ */
                if (p->num>q->num) 
                {
                    /* ����������� */
                    num=p->num;
                    p->num=q->num;
                    q->num=num;
                    /* ��������ID */
                    id=p->id;
                    p->id=q->id;
                    q->id=id;
                    /* ������������ */
                    strcpy(name, p->name);
                    strcpy(p->name, q->name);
                    strcpy(q->name, name);
                    /* ����������ַ */
                    strcpy(address, p->address);
                    strcpy(p->address, q->address);
                    strcpy(q->address, address);
                }   
                /* �ƶ�ָ��q����һ���ڵ� */
                q=q->next;
            }
            /* �ƶ�ָ��p����һ���ڵ� */
            p=p->next;
            /* ���p�ص�ͷ������������ɣ�����ѭ�� */
            if (p==head) 
            {
                break; 
            }
        }

        /* ����Ϊ�����б��е�ÿһ������1��ʼ��˳���� */
        p = head;
        int i = 1;
        if(p != NULL) 
        {
            while(1)
            {
                /* ���ڵ����˳���� */
                p->num=i++;
                /* �ƶ�ָ��p����һ���ڵ� */
                p=p->next;
                /* ���p�ص�ͷ����������ɣ�����ѭ�� */
                if (p==head) 
                {
                    break;
                }
            }
        }
    }
}

void give_id(struct song *head) //����������
{
    struct song *p = head;
    int id;
    int repeat;
    repeat=0;
    struct song *q;
    
    FILE *fp1 = fopen("list.txt", "w");
    FILE *fp2 = fopen("song.txt", "w");
    if (fp1 == NULL) 
    {
        puts("�޷��� list.txt �ļ���");
        return;
    }
    
    srand(time(0));

    while (p != NULL) 
    {
        do 
        {
            id = rand() % 9000 + 1000;
            q = head;

            while (q != NULL) 
            {
                if (q->id == id) 
                {
                    repeat = 1;
                    break;
                }
                q = q->next;
                if (q == head) 
                {
                    break;
                }
            }
        } while (repeat==1);

        p->id = id;
        p = p->next;
        if (p== head) 
        {
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
}

/*void copy(struct song *head) //Ҳ�����е�����
{
    if (head == NULL) 
    {
        printf("����Ϊ�ա�\n");
        return;
    }

    struct song *p = head;
    FILE *fp1 = fopen("list.txt", "r");
    FILE *fp2 = fopen("song.txt", "w");

    
    do {
        fprintf(fp2, "%s %s\n", p->name, p->address);
        p = p->next;
    } while (p != head);
        fclose(fp1);
        fclose(fp2);
}*/

int main()
{
    int i, j, k;
    char x[50], y[1024];
    struct song *h;
    h = NULL;
    give_id(h);
    printf("            Manba Music\n");
    printf("*************************************\n");
    printf("            �Ƿ�������ֿ⣿\n");
    printf("            1.���������ֿ�\n");
    printf("            2.�Ѵ������ֿ�\n");
    printf("            0.����ǰ�ò˵�\n");
    printf("*************************************\n");
    printf("����������ѡ��[0-2]\n");
    scanf("%d", &i);
    while (1)
    {
        if (i == 1)
        {
            system("cls");
            printf("���ڴ������ֿ��ļ���\n");
            char *way = "D:\\code\\C language\\7\\project\\git\\output"; // �滻Ϊʵ��·��
            search_way(way); // ���� search �����ҳ�.mp3�ļ�
            printf("������ɣ�\n");
            //give_id(h);
            //copy(h);
            h = create();
            printf("�����ĸ���������:\n");
            paixu(h);
            print(h);
            break;
        }
        else if (i == 2)
        {
            system("cls");
            printf("���ڴӸ������ļ���ȡ����\n");
            //copy(h);
            h = create();
            paixu(h);
            printf("��ȡ�ɹ�!\n");
            printf("�����б�����:\n");
            print(h);
            break;
        }
        else
        {
            printf("\n ����������������룡\n");
        }
    }
    // ��ѭ���ȴ��û�ѡ�����
    while (1)
    {
        menu1();
        scanf("%d", &j);
        switch (j)
        {
            case 1:
                printf("��������Ҫ��ӵĸ������ļ��� ���֣�:\n");
                scanf("%s %s", &x, &y);
                h = insert_Node(h, x, y);
                paixu(h);
                save(h);
                printf("��ӳɹ���\n");
                print(h);
                break;
            case 2:
                printf("��������Ҫɾ���ĸ�������ţ�:\n");
                scanf("%d", &k);
                h = Del_Node(h, k);
                paixu(h);
                system("cls");
                save(h);
                printf("ɾ���ɹ���\n");
                break;
            case 3:
                printf("��������Ҫ�����ĸ���:\n");
                search(h);
                break;
            case 4:
                system("cls");
                printf("����������:\n");
                print(h);
                break;
            case 0:
                return 1; // ����ǰ�ò˵�
            default:
                printf("\n ����������������룡\n");
        };
    }
    return 0;
}

