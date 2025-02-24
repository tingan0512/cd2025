#include <stdio.h>
#include <string.h>

#define MAX_NODES 1000

typedef struct Node {
    char character;
    int count;
    int next;
} Node;

Node nodes[MAX_NODES];
int freeIndex = 0;

// 檢查是否為有效的 ASCII 字元
int isValidChar(char c) {
    // 只處理可見的 ASCII 字元 (33-126)
    return c >= 33 && c <= 126;
}

int createNode(char c) {
    if (freeIndex >= MAX_NODES) {
        return -1;
    }
    nodes[freeIndex].character = c;
    nodes[freeIndex].count = 1;
    nodes[freeIndex].next = -1;
    return freeIndex++;
}

int findChar(int head, char c) {
    int current = head;
    while (current != -1) {
        if (nodes[current].character == c) {
            return current;
        }
        current = nodes[current].next;
    }
    return -1;
}

int insertOrUpdate(int head, char c) {
    if (!isValidChar(c)) {
        return head;
    }
    
    int existingNode = findChar(head, c);
    if (existingNode != -1) {
        nodes[existingNode].count++;
        return head;
    }
    
    int newNode = createNode(c);
    if (newNode == -1) {
        return head;
    }
    
    if (head == -1) {
        return newNode;
    }
    
    int current = head;
    while (nodes[current].next != -1) {
        current = nodes[current].next;
    }
    nodes[current].next = newNode;
    return head;
}

int main() {
    int head = -1;
    char c;
    
    FILE* file = fopen("main.c", "r");
    if (file == NULL) {
        return 1;
    }
    
    while ((c = fgetc(file)) != EOF) {
        head = insertOrUpdate(head, c);
    }
    
    int current = head;
    while (current != -1) {
        printf("%c : %d\n", nodes[current].character, nodes[current].count);
        current = nodes[current].next;
    }
    
    fclose(file);
    return 0;
}