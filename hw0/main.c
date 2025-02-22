#include <stdio.h>
#include <string.h>

#define MAX_NODES 1000
#define HASH_SIZE 128  // ASCII 字元範圍

typedef struct Node {
    char character;
    int count;
    int next;
} Node;

Node nodePool[MAX_NODES];
int freeIndex = 0;
int hashTable[HASH_SIZE];  // 新增雜湊表，儲存每個字元對應的節點索引

// 初始化雜湊表
void initHashTable() {
    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = -1;
    }
}

// 使用雜湊表查找字元，O(1)
int findChar(int head, char c) {
    return hashTable[(unsigned char)c];
}

int createNode(char c) {
    if (freeIndex >= MAX_NODES) {
        return -1;
    }
    
    nodePool[freeIndex].character = c;
    nodePool[freeIndex].count = 1;
    nodePool[freeIndex].next = -1;
    
    // 更新雜湊表
    hashTable[(unsigned char)c] = freeIndex;
    
    return freeIndex++;
}

int processChar(int head, char c) {
    int existingNode = findChar(head, c);
    
    if (existingNode != -1) {
        nodePool[existingNode].count++;
        return head;
    }
    
    int newNodeIndex = createNode(c);
    if (newNodeIndex == -1) {
        return head;
    }
    
    if (head == -1) {
        return newNodeIndex;
    }
    
    int current = head;
    while (nodePool[current].next != -1) {
        current = nodePool[current].next;
    }
    nodePool[current].next = newNodeIndex;
    return head;
}

void printList(int head) {
    int current = head;
    while (current != -1) {
        printf("%c : %d\n", 
            nodePool[current].character, 
            nodePool[current].count);
        current = nodePool[current].next;
    }
}

int main() {
    int head = -1;
    char input[] = "#hello##oooyahaha";
    int len = strlen(input);
    int i;
    
    // 初始化雜湊表
    initHashTable();
    
    for (i = 0; i < len; i++) {
        head = processChar(head, input[i]);
    }
    
    printList(head);
    
    return 0;
}

