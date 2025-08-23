#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include "generics.h"
#include <cstring>
#include <iterator>
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
  if (!(*toBePushed))
    return;
  if (!(*root)) {
    (*toBePushed)->next = *root;
    *root = (Node *)move((void **)toBePushed);
    return;
  }
  Node *last = cl_iterate_to_last_node(root);
  (*toBePushed)->next = *root;
  last->next = *toBePushed;
  *root = (Node *)move((void **)toBePushed);
}

static inline void cl_push_front_cp_node(Node **root, Node *toBePushed) {
  if (!toBePushed)
    return;
  if (!(*root)) {
    toBePushed->next = *root;
    *root = toBePushed;
    return;
  }
  Node *last = cl_iterate_to_last_node(root);
  toBePushed->next = *root;
  last->next = toBePushed;
  *root = toBePushed;
}

static inline void cl_push_front_deep_cp_node(Node **root, Node *toBePushed) {
  if (!toBePushed)
    return;
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = malloc(sizeof(toBePushed->dataLen));
  memmove(newNode->data, toBePushed->data, toBePushed->dataLen);
  newNode->dataLen = toBePushed->dataLen;
  if (!(*root)) {
    *root = newNode;
    return;
  }
  Node *last = cl_iterate_to_last_node(root);
  toBePushed->next = *root;
  last->next = toBePushed;
  *root = toBePushed;
}

static inline void cl_push_front_mv_data(Node **root, void **data,
                                         size_t dataSize) {
  Node *newNode = cl_create_node_mv(data, dataSize, NULL);
  cl_push_front_mv_node(root, &newNode);
}

static inline void cl_push_front_cp_data(Node **root, void *data,
                                         size_t dataSize) {
  cl_push_front_cp_node(root, cl_create_node_cp(data, dataSize, NULL));
}

static inline void cl_push_front_deep_cp_data(Node **root, void *data,
                                              size_t dataSize) {
  cl_push_front_deep_cp_node(root,
                             cl_create_node_deep_cp(data, dataSize, NULL));
}

#endif // CIRCULARLINKEDLIST_H