#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

Node *head = NULL;

void addNode(int data);
void createFromFile(const char *filename);
void traverseList();

int main() {
    createFromFile("data.txt"); // 创建链表
    traverseList(); // 遍历链表
    return 0;
}

void createFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("无法打开文件");
        exit(EXIT_FAILURE);
    }

    Node *newNode;
    int data;
    while (fscanf(file, "%d", &data) != EOF) {
        newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            perror("内存分配失败");
            exit(EXIT_FAILURE);
        }
        newNode->data = data;
        newNode->prev = NULL;
        newNode->next = NULL;

        if (head == NULL) { // 如果是第一个节点
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            head->prev->next = newNode;
            newNode->prev = head->prev;
            newNode->next = head;
            head->prev = newNode;
        }
    }
    fclose(file);
}

void traverseList() {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
