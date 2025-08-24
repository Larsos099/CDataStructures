#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include "generics.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
static inline Node *cl_iterate_to_last_node(Node *root) {
  Node *current = root;
  while (current->next != root) {
    current = current->next;
  }
  return current;
}

static inline Node *cl_iterate_to_index(Node **root, int idx) {
  Node *current = *root;
  int i = 0;
  while (current->next != *root && i < idx) {
    current = current->next;
    i++;
  }
  if (i < idx)
    return NULL;
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
  Node *last = cl_iterate_to_last_node(*root);
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
  Node *last = cl_iterate_to_last_node(*root);
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
  Node *last = cl_iterate_to_last_node(*root);
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

static inline void cl_push_back_mv_node(Node **root, Node **toBePushed) {
  if (!(*toBePushed))
    return;
  if (root) {
    (*toBePushed)->next = *root;
    (*root)->next = *toBePushed;
    return;
  }

  Node *last = cl_iterate_to_last_node(*root);
  last->next = (Node *)move((void **)toBePushed);
  (*toBePushed)->next = *root;
}

static inline void cl_push_back_cp_node(Node **root, Node *toBePushed) {
  if (!toBePushed)
    return;
  if (root) {
    toBePushed->next = *root;
    (*root)->next = toBePushed;
    return;
  }
  Node *last = cl_iterate_to_last_node(*root);
  toBePushed->next = *root;
  last->next = toBePushed;
}

static inline void cl_push_back_deep_cp_node(Node **root, Node *toBePushed) {
  if (!toBePushed)
    return;
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = malloc(sizeof(toBePushed->dataLen));
  memmove(newNode->data, toBePushed->data, toBePushed->dataLen);
  newNode->dataLen = toBePushed->dataLen;
  if (root) {
    toBePushed->next = *root;
    (*root)->next = toBePushed;
    return;
  }
  Node *last = cl_iterate_to_last_node(*root);
  toBePushed->next = *root;
  last->next = toBePushed;
}

static inline void cl_push_back_mv_data(Node **root, void **data,
                                        size_t dataSize) {
  Node *newNode = cl_create_node_mv(data, dataSize, NULL);
  cl_push_back_mv_node(root, &newNode);
}

static inline void cl_push_back_cp_data(Node **root, void *data,
                                        size_t dataSize) {
  cl_push_back_cp_node(root, cl_create_node_cp(data, dataSize, NULL));
}

static inline void cl_push_back_deep_cp_data(Node **root, void *data,
                                             size_t dataSize) {
  cl_push_back_deep_cp_node(root, cl_create_node_deep_cp(data, dataSize, NULL));
}

static inline Node *cl_get_at_index(Node **root, int idx) {
  return cl_iterate_to_index(root, idx);
}

static inline void *cl_get_data_by_index(Node **root, int idx) {
  Node *nati = cl_iterate_to_index(root, idx);
  return nati->data;
}

static inline void cl_delete_at_index(Node **root, int idx) {
  if (!root || !*root) {
    return;
  }
  Node *last = cl_iterate_to_last_node(*root);
  if (idx == 0) {
    if (*root == last) {
      if ((*root)->data != NULL)
        free((*root)->data);
      free(*root);
      *root = NULL;
      return;
    }
    Node *n = (*root)->next;
    last->next = n;
    if ((*root)->data != NULL) {
      free((*root)->data);
    }
    free(*root);
    *root = n;
    return;
  }
  Node *prevnati = cl_iterate_to_index(root, idx - 1);
  if (prevnati == NULL)
    return;
  Node *nati = prevnati->next;
  Node *natinext = nati->next;
  if (nati->data != NULL) {
    free(nati->data);
  }
  free(nati);
  prevnati->next = natinext;
}

static inline void cl_delete_by_value(Node **root, void *data, size_t size) {
  if (!root || !*root)
    return; 

  Node *current = *root;
  Node *prev = NULL;
  do {
    if (current->dataLen == size && memcmp(current->data, data, size) == 0) {
      if (current == *root) {
        Node *last = cl_iterate_to_last_node(*root);
        if (*root == last) {
          if (current->data)
            free(current->data);
          free(current);
          *root = NULL;
          return;
        }
        *root = current->next;
        last->next = *root;
      } else {
        prev->next = current->next;
      }

      if (current->data)
        free(current->data);
      free(current);
      return;
    }

    prev = current;
    current = current->next;
  } while (current != *root);
}

#endif // CIRCULARLINKEDLIST_H