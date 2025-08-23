#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include <cstring>
#include <stdlib.h>
#include <stddef.h>
#include "generics.h"

static inline Node* cl_create_node_cp(void* data, size_t dataSize, Node* next) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->dataLen = dataSize;
    newNode->next = next;
    return newNode;
}

static inline Node* cl_create_node_deep_cp(void* data, size_t dataSize, Node* next) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = malloc(dataSize);
    memmove(newNode->data, data, dataSize);
    newNode->dataLen = dataSize;
    newNode->next = next;
    return newNode;
}

static inline Node* cl_create_node_mv(void** data, size_t dataSize, Node* next) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = move(data);
    newNode->dataLen = dataSize;
    newNode->next = next;
    return newNode;
}

#endif // CIRCULARLINKEDLIST_H