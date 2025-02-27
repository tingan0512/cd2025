#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char character;
    int count;
    struct Node* next;
} Node;

// 檢查是否為有效的 ASCII 字元
int isValidChar(char c) {
    // 只處理可見的 ASCII 字元 (33-126)
    return c >= 33 && c <= 126;
}

Node* createNode(char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "記憶體配置失敗\n");
        return NULL;
    }
    newNode->character = c;
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

Node* findChar(Node* head, char c) {
    Node* current = head;
    while (current != NULL) {
        if (current->character == c) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Node* insertOrUpdate(Node* head, char c) {
    if (!isValidChar(c)) {
        return head;
    }
    
    Node* existingNode = findChar(head, c);
    if (existingNode != NULL) {
        existingNode->count++;
        return head;
    }
    
    Node* newNode = createNode(c);
    if (newNode == NULL) {
        return head;
    }
    
    if (head == NULL) {
        return newNode;
    }
    
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Node* head = NULL;
    char c;
    
    FILE* file = fopen("main.c", "r");
    if (file == NULL) {
        fprintf(stderr, "無法開啟檔案\n");
        return 1;
    }
    
    while ((c = fgetc(file)) != EOF) {
        head = insertOrUpdate(head, c);
    }
    
    Node* current = head;
    while (current != NULL) {
        printf("%c : %d\n", current->character, current->count);
        current = current->next;
    }
    
    fclose(file);
    freeList(head);
    return 0;
}