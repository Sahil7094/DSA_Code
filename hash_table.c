#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define KEY_SIZE 50
#define VALUE_SIZE 100
typedef struct Node {
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
    struct Node* next;
} Node;
Node* hashTable[TABLE_SIZE];
unsigned int hash(const char* key) {
    unsigned int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue += key[i];
    }
    return hashValue % TABLE_SIZE;
}
void insert(const char* key, const char* value) {
    unsigned int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));

    strcpy(newNode->key, key);
    strcpy(newNode->value, value);
    newNode->next = NULL;
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}
char* search(const char* key) {
    unsigned int index = hash(key);
    Node* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}
void deleteKey(const char* key) {
    unsigned int index = hash(key);
    Node* current = hashTable[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                hashTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Deleted key: %s\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Key not found: %s\n", key);
}
void display() {
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d] -> ", i);
        Node* current = hashTable[i];
        while (current != NULL) {
            printf("(%s: %s) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}
int main() {
    insert("apple", "A fruit");
    insert("banana", "Yellow fruit");
    insert("book", "Something to read");
    insert("laptop", "Electronic device");
    insert("ball", "A round object");
    display();
    char* result = search("laptop");
    if (result != NULL) {
        printf("\nFound: laptop -> %s\n", result);
    } else {
        printf("\nlaptop not found\n");
    }
    deleteKey("banana");
    display();

    return 0;
}
