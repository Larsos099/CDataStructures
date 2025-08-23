#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include "generics.h"
#include <cstring>
#include <stddef.h>
#include <stdlib.h>

static inline Node *cl_iterate_to_last_node(Node **root) {
  Node *current = *root;
  while (current->next != *root) {
    current = current->next;
  }
  return current;
}

static inline Node *cl_create_node_cp(void *data, size_t dataSize, Node *next) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->dataLen = dataSize;
  newNode->next = next;
  return newNode;
}

static inline Node *cl_create_node_deep_cp(void *data, size_t dataSize,
                                           Node *next) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = malloc(dataSize);
  memmove(newNode->data, data, dataSize);
  newNode->dataLen = dataSize;
  newNode->next = next;
  return newNode;
}

static inline Node *cl_create_node_mv(void **data, size_t dataSize,
                                      Node *next) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = move(data);
  newNode->dataLen = dataSize;
  newNode->next = next;
  return newNode;
}

static inline void cl_push_front_mv_node(Node **root, Node **toBePushed) {
  if (!(*root)) {
    (*toBePushed)->next = *root;
    *root = (Node *)move((void **)toBePushed);
    return;
  }
  Node *last = cl_iterate_to_last_node(root);
  (*toBePushed)->next = *root;
  last->next = *toBePushed;
  *root = (Node*)move((void**)toBePushed);
}

static inline void cl_push_front_cp_node(Node** root, Node** toBePushed) {
    if(!(*root)) {
        (*toBePushed)->next = *root;
        *root = *toBePushed;
        return;
    }
    Node* last = cl_iterate_to_last_node(root);
    (*toBePushed)->next = *root;
    last->next = *toBePushed;
    *root = *toBePushed;
}

#endif // CIRCULARLINKEDLIST_H