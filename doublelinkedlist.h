#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @struct DLNode
 * @brief Node for a doubly linked list.
 * @var data Pointer to stored data.
 * @var dataSize Size of the data in bytes.
 * @var next Pointer to the next node.
 * @var previous Pointer to the previous node.
 */
typedef struct DLNode {
  void *data;
  size_t dataSize;
  struct DLNode *next;
  struct DLNode *previous;
} DLNode;

/**
 * @brief Moves a pointer and sets the old pointer to NULL.
 * @param old Pointer to the old pointer.
 * @return The moved pointer.
 */
static inline void *move(void **old) {
  void *newPtr = *old;
  *old = NULL;
  return newPtr;
}

/**
 * @brief Returns the last node of the list.
 * @param root Pointer to the root node of the list.
 * @return Pointer to the last node.
 * @note root must not be NULL.
 */
static inline DLNode *dl_iterate_to_last_node(DLNode **root) {
  DLNode *current = *root;
  while (current->next != NULL) {
    current = current->next;
  }
  return current;
}

/**
 * @brief Creates a new node using move semantics for data ownership.
 * @param data Pointer to the pointer of data (ownership transferred).
 * @param dataSize Size of the data in bytes.
 * @param next Pointer to the next node.
 * @param previous Pointer to the previous node.
 * @return Pointer to the new node.
 */
static inline DLNode *dl_create_node_mv(void **data, size_t dataSize,
                                        DLNode *next, DLNode *previous) {
  DLNode *newNode = (DLNode *)malloc(sizeof(DLNode));
  newNode->dataSize = dataSize;
  newNode->data = move(data);
  newNode->next = next;
  newNode->previous = previous;
  return newNode;
}

/**
 * @brief Creates a new node using shallow copy (pointer is not copied).
 * @param data Pointer to the data (not copied).
 * @param dataSize Size of the data.
 * @param next Pointer to the next node.
 * @param previous Pointer to the previous node.
 * @return Pointer to the new node.
 * @note Node does not own the data; do not free() it from Node.
 */
static inline DLNode *dl_create_node_cp(void *data, size_t dataSize,
                                        DLNode *next, DLNode *previous) {
  DLNode *newNode = (DLNode *)malloc(sizeof(DLNode));
  newNode->dataSize = dataSize;
  newNode->data = data;
  newNode->next = next;
  newNode->previous = previous;
  return newNode;
}

/**
 * @brief Creates a new node with deep copy of the data.
 * @param data Pointer to the data to be copied.
 * @param dataSize Size of the data.
 * @param next Pointer to the next node.
 * @param previous Pointer to the previous node.
 * @return Pointer to the new node.
 */
static inline DLNode *dl_create_node_deep_cp(void *data, size_t dataSize,
                                             DLNode *next, DLNode *previous) {
  DLNode *newNode = (DLNode *)malloc(sizeof(DLNode));
  newNode->dataSize = dataSize;
  if (data != NULL && dataSize > 0) {
    newNode->data = malloc(dataSize);
    memmove(newNode->data, data, dataSize);
  } else
    newNode->data = NULL;
  newNode->next = next;
  newNode->previous = previous;
  return newNode;
}

/**
 * @brief Appends a node at the end of the list (move semantics).
 * @param root Pointer to the root node of the list.
 * @param newNode Pointer to the node pointer to be moved.
 */
static inline void dl_push_back_mv_node(DLNode **root, DLNode **newNode) {
  if (*root == NULL)
    *root = (DLNode *)move((void **)newNode);
  else {
    DLNode *current = dl_iterate_to_last_node(root);
    (*newNode)->previous = current;
    current->next = (DLNode *)move((void **)newNode);
  }
}

/**
 * @brief Appends a node at the end of the list (shallow copy).
 * @param root Pointer to the root node of the list.
 * @param newNode Node to append.
 */
static inline void dl_push_back_cp_node(DLNode **root, DLNode *newNode) {
  if (*root == NULL)
    *root = newNode;
  else {
    DLNode *current = dl_iterate_to_last_node(root);
    current->next = newNode;
    newNode->previous = current;
  }
}

/**
 * @brief Appends a node at the end of the list (deep copy of data).
 * @param root Pointer to the root node of the list.
 * @param newNode Node whose data is copied.
 */
static inline void dl_push_back_deep_cp_node(DLNode **root, DLNode *newNode) {
  if (*root == NULL) {
    *root =
        dl_create_node_deep_cp(newNode->data, newNode->dataSize, NULL, NULL);
    return;
  }
  DLNode *current = dl_iterate_to_last_node(root);
  current->next =
      dl_create_node_deep_cp(newNode->data, newNode->dataSize, NULL, current);
}

/**
 * @brief Appends data at the end of the list (shallow copy).
 */
static inline void dl_push_back_cp_data(DLNode **root, void *data,
                                        size_t dataSize) {
  dl_push_back_cp_node(root, dl_create_node_cp(data, dataSize, NULL, NULL));
}

/**
 * @brief Appends data at the end of the list (move semantics).
 */
static inline void dl_push_back_mv_data(DLNode **root, void **data,
                                        size_t dataSize) {
  DLNode *n = dl_create_node_mv(data, dataSize, NULL, NULL);
  dl_push_back_mv_node(root, &n);
}

/**
 * @brief Appends data at the end of the list (deep copy).
 */
static inline void dl_push_back_deep_cp_data(DLNode **root, void *data,
                                             size_t dataSize) {
  dl_push_back_deep_cp_node(root,
                            dl_create_node_deep_cp(data, dataSize, NULL, NULL));
}

/**
 * @brief Prepends a node at the beginning of the list (shallow copy).
 */
static inline void dl_push_front_cp_node(DLNode **root, DLNode *newNode) {
  if (*root == NULL) {
    *root = newNode;
    newNode->previous = NULL;
    newNode->next = NULL;
    return;
  }
  newNode->next = *root;
  newNode->previous = NULL;
  (*root)->previous = newNode;
  *root = newNode;
}

/**
 * @brief Prepends a node at the beginning of the list (deep copy).
 */
static inline void dl_push_front_deep_cp_node(DLNode **root, DLNode *newNode) {
  if (*root == NULL) {
    *root =
        dl_create_node_deep_cp(newNode->data, newNode->dataSize, NULL, NULL);
    return;
  }
  DLNode *newCopied =
      dl_create_node_deep_cp(newNode->data, newNode->dataSize, NULL, NULL);
  newCopied->next = *root;
  (*root)->previous = newCopied;
  *root = newCopied;
}

/**
 * @brief Prepends a node at the beginning of the list (move semantics).
 */
static inline void dl_push_front_mv_node(DLNode **root, DLNode **newNode) {
  if (*root == NULL) {
    *root = (DLNode *)move((void **)newNode);
    (*root)->previous = NULL;
    (*root)->next = NULL;
    return;
  }
  (*newNode)->next = *root;
  (*newNode)->previous = NULL;
  (*root)->previous = *newNode;
  *root = (DLNode *)move((void **)newNode);
}

/**
 * @brief Prepends data at the beginning of the list (shallow copy).
 */
static inline void dl_push_front_cp_data(DLNode **root, void *data,
                                         size_t dataSize) {
  dl_push_front_cp_node(root, dl_create_node_cp(data, dataSize, NULL, NULL));
}

/**
 * @brief Prepends data at the beginning of the list (deep copy).
 */
static inline void dl_push_front_deep_cp_data(DLNode **root, void *data,
                                              size_t dataSize) {
  dl_push_front_deep_cp_node(
      root, dl_create_node_deep_cp(data, dataSize, NULL, NULL));
}

/**
 * @brief Prepends data at the beginning of the list (move semantics).
 */
static inline void dl_push_front_mv_data(DLNode **root, void **data,
                                         size_t dataSize) {
  DLNode *n = dl_create_node_mv(data, dataSize, NULL, NULL);
  dl_push_front_mv_node(root, &n);
}

/**
 * @brief Deletes a node at the specified index.
 * @param root Pointer to the root node.
 * @param index Zero-based index of the node to delete.
 */
static inline void dl_delete_at_index(DLNode **root, size_t index) {
  if (*root == NULL)
    return;

  DLNode *current = *root;
  size_t i = 0;

  while (current != NULL && i < index) {
    current = current->next;
    i++;
  }
  if (current == NULL)
    return;

  if (current->previous)
    current->previous->next = current->next;
  else
    *root = current->next; // deleting head

  if (current->next)
    current->next->previous = current->previous;

  if (current->data)
    free(current->data);
  free(current);
}

/**
 * @brief Deletes the first node whose data matches the given value.
 * @param root Pointer to the root node.
 * @param data Pointer to the value to match.
 * @param dataSize Size of the value.
 */
static inline void dl_delete_by_value(DLNode **root, void *data,
                                      size_t dataSize) {
  if (*root == NULL)
    return;

  DLNode *current = *root;
  while (current != NULL) {
    if (current->data && data && current->dataSize == dataSize &&
        memcmp(current->data, data, dataSize) == 0) {

      if (current->previous)
        current->previous->next = current->next;
      else
        *root = current->next;

      if (current->next)
        current->next->previous = current->previous;

      if (current->data)
        free(current->data);
      free(current);
      return;
    }
    current = current->next;
  }
}

/**
 * @brief Checks if a value exists in the list.
 * @param root Pointer to the root node.
 * @param data Pointer to the value to match.
 * @param dataSize Size of the value.
 * @return true if found, false otherwise.
 */
static inline bool dl_contains(DLNode *root, void *data, size_t dataSize) {
  DLNode *current = root;
  while (current != NULL) {
    if (current->data && data && current->dataSize == dataSize &&
        memcmp(current->data, data, dataSize) == 0)
      return true;
    current = current->next;
  }
  return false;
}

/**
 * @brief Returns the first node whose data matches the given value.
 * @param root Pointer to the root node.
 * @param data Pointer to the value to match.
 * @param dataSize Size of the value.
 * @return Pointer to the matching node, or NULL if not found.
 */
static inline DLNode *dl_get_by_value(DLNode *root, void *data,
                                      size_t dataSize) {
  DLNode *current = root;
  while (current != NULL) {
    if (current->data && data && current->dataSize == dataSize &&
        memcmp(current->data, data, dataSize) == 0)
      return current;
    current = current->next;
  }
  return NULL;
}

/**
 * @brief Returns the node at the specified index.
 * @param root Pointer to the root node.
 * @param index Zero-based index.
 * @return Pointer to the node, or NULL if out of bounds.
 */
static inline DLNode *dl_get_by_index(DLNode *root, size_t index) {
  DLNode *current = root;
  size_t i = 0;
  while (current != NULL && i < index) {
    current = current->next;
    i++;
  }
  return current; // NULL if out of bounds
}
static inline void dl_free_list(DLNode **root) {
  if (!root || !*root)
    return;

  DLNode *current = *root;
  while (current != NULL) {
    DLNode *next = current->next;
    if (current->data)
      free(current->data);
    free(current);
    current = next;
  }
  *root = NULL;
}

#endif // DOUBLELINKEDLIST_H
