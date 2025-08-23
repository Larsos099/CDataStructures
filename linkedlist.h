#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct Node
 * @brief Node structure for a singly linked list.
 * @var data Pointer to the stored data.
 * @var dataLen Size of the data in bytes.
 * @var next Pointer to the next node.
 */
typedef struct Node {
  void *data;
  size_t dataLen;
  struct Node *next;
} Node;

/**
 * @brief Moves a pointer and sets the old pointer to NULL (simulates std::move
 * in C++).
 * @param old Pointer to the pointer to move.
 * @return The moved pointer.
 */
static inline void *move(void **old) {
  void *newPtr = *old;
  *old = NULL;
  return newPtr;
}

/**
 * @brief Creates a new node using move semantics for the data.
 * @param data Pointer to pointer of data (ownership transferred).
 * @param dataLen Size of the data in bytes.
 * @param next Pointer to the next node.
 * @return Pointer to the new node.
 */
static inline Node *sl_create_node_mv(void **data, size_t dataLen, Node *next) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->dataLen = dataLen;
  newNode->data = move(data);
  newNode->next = next;
  return newNode;
}

/**
 * @brief Creates a new node using move semantics and moves a node pointer as
 * next.
 * @param data Pointer to pointer of data (ownership transferred).
 * @param dataLen Size of the data.
 * @param next Pointer to pointer to next node (ownership transferred).
 * @return Pointer to the new node.
 */
static inline Node *sl_create_node_deep_mv(void **data, size_t dataLen,
                                           Node **next) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->dataLen = dataLen;
  newNode->data = move(data);
  newNode->next = (Node *)move((void **)next);
  return newNode;
}

/**
 * @brief Creates a new node using shallow copy of data (pointer not copied).
 * @param data Pointer to the data (not copied).
 * @param dataLen Size of the data.
 * @param next Pointer to the next node.
 * @return Pointer to the new node.
 * @note Node does not own the data.
 */
static inline Node *sl_create_node_cp(void *data, size_t dataLen, Node *next) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->dataLen = dataLen;
  newNode->data = data;
  newNode->next = next;
  return newNode;
}

/**
 * @brief Creates a new node with a deep copy of the data.
 * @param data Pointer to the data to copy.
 * @param dataLen Size of the data.
 * @param next Pointer to the next node.
 * @return Pointer to the new node.
 */
static inline Node *sl_create_node_deep_cp(void *data, size_t dataLen,
                                           Node *next) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->dataLen = dataLen;
  if (data != NULL && dataLen > 0) {
    newNode->data = malloc(dataLen);
    memmove(newNode->data, data, dataLen);
  } else {
    newNode->data = NULL;
  }
  newNode->next = next;
  return newNode;
}

/**
 * @brief Appends a node to the end of the list using move semantics.
 * @param rootPtrPtr Pointer to the root node pointer.
 * @param nodePtrPtr Pointer to node pointer (ownership transferred).
 */
static inline void sl_push_back_mv_node(Node **rootPtrPtr, Node **nodePtrPtr) {
  if (*rootPtrPtr == NULL) {
    *rootPtrPtr = *nodePtrPtr;
    *nodePtrPtr = NULL;
    return;
  } else {
    Node *current = *rootPtrPtr;
    while (current->next != NULL)
      current = current->next;
    current->next = *nodePtrPtr;
    *nodePtrPtr = NULL;
  }
}

/**
 * @brief Appends data to the end of the list using move semantics.
 * @param rootPtrPtr Pointer to the root node pointer.
 * @param data Pointer to pointer of data (ownership transferred).
 * @param dataLen Size of the data.
 */
static inline void sl_push_back_mv_data(Node **rootPtrPtr, void **data,
                                        size_t dataLen) {
  Node *nNode = (Node *)malloc(sizeof(Node));
  nNode->dataLen = dataLen;
  nNode->data = move(data);
  nNode->next = NULL;
  sl_push_back_mv_node(rootPtrPtr, &nNode);
}

/**
 * @brief Appends a node to the end of the list using shallow copy.
 * @param rootPtrPtr Pointer to the root node pointer.
 * @param nodePtr Node to append.
 */
static inline void sl_push_back_cp_node(Node **rootPtrPtr, Node *nodePtr) {
  if (*rootPtrPtr == NULL) {
    *rootPtrPtr = nodePtr;
    return;
  } else {
    Node *current = *rootPtrPtr;
    while (current->next != NULL)
      current = current->next;
    current->next = nodePtr;
  }
}

/**
 * @brief Appends data to the end of the list using deep copy.
 * @param rootPtrPtr Pointer to the root node pointer.
 * @param data Pointer to data to copy.
 * @param dataLen Size of the data.
 */
static inline void sl_push_back_cp_data(Node **rootPtrPtr, void *data,
                                        size_t dataLen) {
  Node *nNode = (Node *)malloc(sizeof(Node));
  nNode->dataLen = dataLen;
  nNode->data = data;
  nNode->next = NULL;
  sl_push_back_cp_node(rootPtrPtr, nNode);
}

/**
 * @brief Appends data to the end of the list using deep copy.
 * @param rootPtrPtr Pointer to the root node pointer.
 * @param data Pointer to data to copy.
 * @param dataLen Size of the data.
 */
static inline void sl_push_back_cp_data_deep(Node **rootPtrPtr, void *data,
                                        size_t dataLen) {
  Node *nNode = (Node *)malloc(sizeof(Node));
  nNode->dataLen = dataLen;
  nNode->data = malloc(dataLen);
  memmove(nNode->data, data, dataLen);
  nNode->next = NULL;
  sl_push_back_cp_node(rootPtrPtr, nNode);
}

/**
 * @brief Prepends a node to the start of the list using move semantics.
 * @param rootPtrPtr Pointer to the root node pointer.
 * @param nodePtrPtr Pointer to node pointer (ownership transferred).
 */
static inline void sl_push_front_mv_node(Node **rootPtrPtr, Node **nodePtrPtr) {
  if (*rootPtrPtr == NULL) {
    *rootPtrPtr = (Node *)move((void **)nodePtrPtr);
    return;
  }
  (*nodePtrPtr)->next = *rootPtrPtr;
  *rootPtrPtr = (Node *)move((void **)nodePtrPtr);
}

/**
 * @brief Prepends data to the start of the list using move semantics.
 */
static inline void sl_push_front_mv_data(Node **rootPtrPtr, void **data,
                                         size_t dataLen) {
  Node *nNode = (Node *)malloc(sizeof(Node));
  nNode->data = move(data);
  nNode->dataLen = dataLen;
  nNode->next = NULL;
  sl_push_front_mv_node(rootPtrPtr, &nNode);
}

/**
 * @brief Prepends a node to the start of the list using shallow copy.
 */
static inline void sl_push_front_cp_node(Node **rootPtrPtr, Node *nodePtr) {
  if (*rootPtrPtr == NULL) {
    *rootPtrPtr = nodePtr;
    return;
  }
  nodePtr->next = *rootPtrPtr;
  *rootPtrPtr = nodePtr;
}

/**
 * @brief Prepends data to the start of the list using deep copy.
 */
static inline void sl_push_front_cp_data(Node **rootPtrPtr, void *data,
                                         size_t dataLen) {
  Node *nNode = (Node *)malloc(sizeof(Node));
  nNode->data = data;
  nNode->dataLen = dataLen;
  sl_push_front_cp_node(rootPtrPtr, nNode);
}

/**
 * @brief Prepends data to the start of the list using deep copy.
 */
static inline void sl_push_front_cp_data_deep(Node **rootPtrPtr, void *data,
                                         size_t dataLen) {
  Node *nNode = (Node *)malloc(sizeof(Node));
  nNode->data = malloc(dataLen);
  memmove(nNode->data, data, dataLen);
  nNode->dataLen = dataLen;
  sl_push_front_cp_node(rootPtrPtr, nNode);
}

/**
 * @brief Returns the data at the specified index.
 * @param rootPtr Root node pointer.
 * @param idx Index to retrieve.
 * @return Pointer to data or NULL if out of bounds.
 */
static inline void *sl_get_at_index(Node *rootPtr, int idx) {
  Node *c = rootPtr;
  int i = 0;
  while (c->next != NULL && i < idx) {
    c = c->next;
    i++;
  }
  if (i < idx) {
    fprintf(stderr, "Error: Index out of bounds.\n");
    return NULL;
  }
  return c->data;
}

/**
 * @brief Returns the first node containing the specified value.
 * @param rootPtr Root node pointer.
 * @param _val Pointer to the value to search for.
 * @return Pointer to node or NULL if value not found.
 */
static inline Node *sl_get_by_value(Node *rootPtr, void *_val) {
  Node *c = rootPtr;
  while (c != NULL) {
    if (memcmp(_val, c->data, c->dataLen) == 0)
      return c;
    c = c->next;
  }
  fprintf(stderr, "Error: Value does not exist in Linked List.\n");
  return NULL;
}

/**
 * @brief Returns the node at the specified index.
 */
static inline Node *sl_get_by_index(Node *rootPtr, int idx) {
  Node *c = rootPtr;
  int i = 0;
  while (c != NULL && i < idx) {
    c = c->next;
    i++;
  }
  if (i < idx) {
    fprintf(stderr, "Error: Index out of bounds.\n");
    return NULL;
  }
  return c;
}

/**
 * @brief Deletes the node at the specified index.
 */
static inline void sl_delete_at_index(Node **rootPtrPtr, int idx) {
  if (*rootPtrPtr == NULL || idx < 0)
    return;
  Node *temp = *rootPtrPtr;
  if (idx == 0) {
    *rootPtrPtr = temp->next;
    free(temp->data);
    free(temp);
    return;
  }
  for (int i = 0; temp != NULL && i < idx - 1; i++)
    temp = temp->next;
  if (temp == NULL || temp->next == NULL)
    return;
  Node *nodeToDelete = temp->next;
  temp->next = nodeToDelete->next;
  free(nodeToDelete->data);
  free(nodeToDelete);
}

/**
 * @brief Deletes the first node containing the specified value.
 */
static inline void sl_delete_by_value(Node **rootPtrPtr, void *val,
                                      size_t dataLen) {
  if (*rootPtrPtr == NULL || val == NULL || dataLen == 0)
    return;
  Node *c = *rootPtrPtr;

  if (c->dataLen == dataLen && memcmp(c->data, val, dataLen) == 0) {
    *rootPtrPtr = c->next;
    free(c->data);
    free(c);
    return;
  }

  while (c->next != NULL) {
    if (c->next->dataLen == dataLen &&
        memcmp(c->next->data, val, dataLen) == 0) {
      Node *nodeToDelete = c->next;
      c->next = nodeToDelete->next;
      free(nodeToDelete->data);
      free(nodeToDelete);
      return;
    }
    c = c->next;
  }
}

/**
 * @brief Inserts a node at a specific index using move semantics.
 * @param rootPtrPtr Pointer to the root node pointer.
 * @param toBeInsertedPtrPtr Pointer to node pointer (ownership transferred).
 * @param idx Index to insert at.
 */
static inline void sl_insert_at_index_mv_node(Node **rootPtrPtr,
                                              Node **toBeInsertedPtrPtr,
                                              int idx) {
  if (!rootPtrPtr || !toBeInsertedPtrPtr || !*toBeInsertedPtrPtr || idx < 0)
    return;

  Node *newNode = (Node *)move((void **)toBeInsertedPtrPtr);

  if (idx == 0) {
    newNode->next = *rootPtrPtr;
    *rootPtrPtr = newNode;
    return;
  }

  Node *current = *rootPtrPtr;
  int i = 0;
  while (current != NULL && i < idx - 1) {
    current = current->next;
    i++;
  }
  if (!current) {
    // index out of bounds
    free(newNode->data);
    free(newNode);
    return;
  }
  newNode->next = current->next;
  current->next = newNode;
}

/**
 * @brief Inserts a node at a specific index using shallow copy.
 */
static inline void sl_insert_at_index_cp_node(Node **rootPtrPtr,
                                              Node *toBeInserted, int idx) {
  if (!rootPtrPtr || !toBeInserted || idx < 0)
    return;

  if (idx == 0) {
    toBeInserted->next = *rootPtrPtr;
    *rootPtrPtr = toBeInserted;
    return;
  }

  Node *current = *rootPtrPtr;
  int i = 0;
  while (current != NULL && i < idx - 1) {
    current = current->next;
    i++;
  }
  if (!current)
    return;

  toBeInserted->next = current->next;
  current->next = toBeInserted;
}

/**
 * @brief Inserts a node at a specific index using deep copy.
 */
static inline void sl_insert_at_index_deep_cp_node(Node **rootPtrPtr,
                                                   Node *toBeCopied, int idx) {
  if (!rootPtrPtr || !toBeCopied || idx < 0)
    return;

  Node *newNode =
      sl_create_node_deep_cp(toBeCopied->data, toBeCopied->dataLen, NULL);

  if (idx == 0) {
    newNode->next = *rootPtrPtr;
    *rootPtrPtr = newNode;
    return;
  }

  Node *current = *rootPtrPtr;
  int i = 0;
  while (current != NULL && i < idx - 1) {
    current = current->next;
    i++;
  }
  if (!current) {
    free(newNode->data);
    free(newNode);
    return;
  }

  newNode->next = current->next;
  current->next = newNode;
}

/**
 * @brief Inserts data at a specific index using move semantics.
 */
static inline void sl_insert_at_index_mv_data(Node **rootPtrPtr, void **data,
                                              size_t dataLen, int idx) {
  Node *node = sl_create_node_mv(data, dataLen, NULL);
  sl_insert_at_index_mv_node(rootPtrPtr, &node, idx);
}

/**
 * @brief Inserts data at a specific index using shallow copy.
 */
static inline void sl_insert_at_index_cp_data(Node **rootPtrPtr, void *data,
                                              size_t dataLen, int idx) {
  Node *node = sl_create_node_cp(data, dataLen, NULL);
  sl_insert_at_index_cp_node(rootPtrPtr, node, idx);
}

/**
 * @brief Inserts data at a specific index using deep copy.
 */
static inline void sl_insert_at_index_deep_cp_data(Node **rootPtrPtr,
                                                   void *data, size_t dataLen,
                                                   int idx) {
  Node *node = sl_create_node_deep_cp(data, dataLen, NULL);
  sl_insert_at_index_deep_cp_node(rootPtrPtr, node, idx);
}

/**
 * @brief Frees all nodes in the list.
 * @param rootPtrPtr Pointer to the root node pointer.
 */
static inline void sl_free_list(Node **rootPtrPtr) {
  Node *c = *rootPtrPtr;
  while (c != NULL) {
    Node *next = c->next;
    free(c->data);
    free(c);
    c = next;
  }
  *rootPtrPtr = NULL;
}

#endif // LINKEDLIST_H
