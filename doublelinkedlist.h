#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "generics.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * @brief Returns the first node that matches the given content EXACTLY.
 * @param root Pointer to the root node of the list.
 * @param data void* for the data to match.
 * @return Pointer to the first node that contains matching data
 * @note root must not be NULL.
 * @note If none is found, returns NULL.
 */
static inline DLNode *dl_iterate_to_matching(DLNode **root, void *data) {
  if (*root == NULL || data == NULL)
    return NULL;
  DLNode *current = *root;
  bool found = false;
  while (current->next != NULL && !found) {
    current = current->next;
    found = (memcmp(current->data, data, current->dataSize) != 0);
  }
  if (!found)
    return NULL;
  return current;
}

static inline DLNode *dl_iterate_to_index(DLNode **root, int idx) {
  DLNode *current = *root;
  int i = 0;
  while (current->next && i < idx) {
    current = current->next;
    i++;
  }
  if (i < idx)
    return NULL;
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

/**
 * @brief Inserts a node at the specified index using move semantics.
 * @param root Pointer to the root node of the list.
 * @param toBeInserted Pointer to the node pointer to be moved (ownership
 * transferred).
 * @param idx Zero-based index where the node should be inserted.
 * @note If idx is out of bounds, the function does nothing.
 */

static inline void dl_insert_at_index_mv_node(DLNode **root,
                                              DLNode **toBeInserted, int idx) {
  if (!root || !*root || !toBeInserted || !*toBeInserted)
    return;

  DLNode *nati = dl_iterate_to_index(root, idx);
  if (!nati)
    return;

  DLNode *newNode = (DLNode *)move((void **)toBeInserted);

  if (nati->previous == NULL) {
    newNode->previous = NULL;
    newNode->next = nati;
    nati->previous = newNode;
    *root = newNode;
    return;
  }

  newNode->previous = nati->previous;
  newNode->next = nati;
  nati->previous->next = newNode;
  nati->previous = newNode;
}

/**
 * @brief Inserts a node at the specified index using shallow copy.
 * @param root Pointer to the root node of the list.
 * @param toBeInserted Pointer to the node (not copied).
 * @param idx Zero-based index where the node should be inserted.
 * @note Node is not copied; caller is responsible for data lifetime.
 * @note If idx is out of bounds, the function does nothing.
 */

static inline void dl_insert_at_index_cp_node(DLNode **root,
                                              DLNode *toBeInserted, int idx) {
  if (!root || !*root || !toBeInserted)
    return;

  DLNode *nati = dl_iterate_to_index(root, idx);
  if (!nati)
    return;

  if (nati->previous == NULL) {
    toBeInserted->previous = NULL;
    toBeInserted->next = nati;
    nati->previous = toBeInserted;
    *root = toBeInserted;
    return;
  }

  toBeInserted->previous = nati->previous;
  toBeInserted->next = nati;
  nati->previous->next = toBeInserted;
  nati->previous = toBeInserted;
}

/**
 * @brief Inserts a node at the specified index using deep copy of its data.
 * @param root Pointer to the root node of the list.
 * @param toBeCopied Node whose data should be copied.
 * @param idx Zero-based index where the node should be inserted.
 * @note If idx is out of bounds, the function does nothing.
 */

static inline void
dl_insert_at_index_deep_cp_node(DLNode **root, DLNode *toBeCopied, int idx) {
  if (!root || !*root || !toBeCopied)
    return;

  DLNode *nati = dl_iterate_to_index(root, idx);
  if (!nati)
    return;

  DLNode *newNode = dl_create_node_deep_cp(toBeCopied->data,
                                           toBeCopied->dataSize, NULL, NULL);

  if (nati->previous == NULL) {
    newNode->previous = NULL;
    newNode->next = nati;
    nati->previous = newNode;
    *root = newNode;
    return;
  }

  newNode->previous = nati->previous;
  newNode->next = nati;
  nati->previous->next = newNode;
  nati->previous = newNode;
}

/**
 * @brief Inserts new data at the specified index (move semantics).
 * @param root Pointer to the root node of the list.
 * @param data Pointer to the pointer of data (ownership transferred).
 * @param dataSize Size of the data in bytes.
 * @param idx Zero-based index where the data should be inserted.
 */

static inline void dl_insert_at_index_mv_data(DLNode **root, void **data,
                                              size_t dataSize, int idx) {
  DLNode *node = dl_create_node_mv(data, dataSize, NULL, NULL);
  dl_insert_at_index_mv_node(root, &node, idx);
}

/**
 * @brief Inserts new data at the specified index (shallow copy).
 * @param root Pointer to the root node of the list.
 * @param data Pointer to the data (not copied).
 * @param dataSize Size of the data in bytes.
 * @param idx Zero-based index where the data should be inserted.
 * @note Data is not copied; caller is responsible for data lifetime.
 */

static inline void dl_insert_at_index_cp_data(DLNode **root, void *data,
                                              size_t dataSize, int idx) {
  dl_insert_at_index_cp_node(
      root, dl_create_node_cp(data, dataSize, NULL, NULL), idx);
}

/**
 * @brief Inserts new data at the specified index (deep copy).
 * @param root Pointer to the root node of the list.
 * @param data Pointer to the data to copy.
 * @param dataSize Size of the data in bytes.
 * @param idx Zero-based index where the data should be inserted.
 */

static inline void dl_insert_at_index_deep_cp_data(DLNode **root, void *data,
                                                   size_t dataSize, int idx) {
  dl_insert_at_index_deep_cp_node(
      root, dl_create_node_deep_cp(data, dataSize, NULL, NULL), idx);
}

/**
 * @brief Frees the entire doubly linked list.
 * @param root Pointer to the root node of the list.
 * @note Frees all nodes and their data, then sets *root to NULL.
 */

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
