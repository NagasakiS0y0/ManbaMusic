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
    createFromFile("data.txt"); // ��������
    traverseList(); // ��������
    return 0;
}

void createFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("�޷����ļ�");
        exit(EXIT_FAILURE);
    }

    Node *newNode;
    int data;
    while (fscanf(file, "%d", &data) != EOF) {
        newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            perror("�ڴ����ʧ��");
            exit(EXIT_FAILURE);
        }
        newNode->data = data;
        newNode->prev = NULL;
        newNode->next = NULL;

        if (head == NULL) { // ����ǵ�һ���ڵ�
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
