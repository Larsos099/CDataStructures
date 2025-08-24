#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include "generics.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Get the last node in a circular linked list.
 * 
 * @param root Pointer to the first node in the list.
 * @return Node* The last node (its next points back to root).
 */
static inline Node *cl_iterate_to_last_node(Node *root) {
  Node *current = root;
  while (current->next != root) {
    current = current->next;
  }
  return current;
}

/**
 * @brief Get the node at a specific index in a circular linked list.
 * 
 * @param root Double pointer to the head node.
 * @param idx Zero-based index of the node to retrieve.
 * @return Node* The node at the index, or NULL if idx is out of range.
 */
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

/**
 * @brief Create a new node by shallow copying data (pointer only).
 * 
 * @param data Pointer to existing data (ownership not transferred).
 * @param dataSize Size of the data.
 * @param next Pointer to the next node.
 * @return Node* Newly allocated node.
 */
static inline Node *cl_create_node_cp(void *data, size_t dataSize, Node *next) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->dataLen = dataSize;
  newNode->next = next;
  return newNode;
}

/**
 * @brief Create a new node by deep copying the data.
 * 
 * @param data Pointer to the source data.
 * @param dataSize Size of the data.
 * @param next Pointer to the next node.
 * @return Node* Newly allocated node with its own copy of the data.
 */
static inline Node *cl_create_node_deep_cp(void *data, size_t dataSize,
                                           Node *next) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = malloc(dataSize);
  memmove(newNode->data, data, dataSize);
  newNode->dataLen = dataSize;
  newNode->next = next;
  return newNode;
}

/**
 * @brief Create a new node by moving ownership of the data pointer.
 * 
 * @param data Double pointer to data (set to NULL after move).
 * @param dataSize Size of the data.
 * @param next Pointer to the next node.
 * @return Node* Newly allocated node, takes ownership of the data.
 */
static inline Node *cl_create_node_mv(void **data, size_t dataSize,
                                      Node *next) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = move(data);
  newNode->dataLen = dataSize;
  newNode->next = next;
  return newNode;
}

/**
 * @brief Insert a node at the front of the circular linked list (move semantics).
 */
static inline void cl_push_front_mv_node(Node **root, Node **toBePushed) {
  if (!(*toBePushed))
    return;
  if (!(*root)) {
    (*toBePushed)->next = *toBePushed;
    *root = (Node *)move((void **)toBePushed);
    return;
  }
  Node *last = cl_iterate_to_last_node(*root);
  (*toBePushed)->next = *root;
  last->next = *toBePushed;
  *root = (Node *)move((void **)toBePushed);
}

/**
 * @brief Insert a node at the front of the circular linked list (shallow copy).
 */
static inline void cl_push_front_cp_node(Node **root, Node *toBePushed) {
  if (!toBePushed)
    return;
  if (!(*root)) {
    toBePushed->next = toBePushed;
    *root = toBePushed;
    return;
  }
  Node *last = cl_iterate_to_last_node(*root);
  toBePushed->next = *root;
  last->next = toBePushed;
  *root = toBePushed;
}

/**
 * @brief Insert a deep copy of a node at the front of the circular linked list.
 */
static inline void cl_push_front_deep_cp_node(Node **root, Node *toBePushed) {
  if (!toBePushed)
    return;
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = malloc(toBePushed->dataLen);
  memmove(newNode->data, toBePushed->data, toBePushed->dataLen);
  newNode->dataLen = toBePushed->dataLen;
  if (!(*root)) {
    newNode->next = newNode;
    *root = newNode;
    return;
  }
  Node *last = cl_iterate_to_last_node(*root);
  newNode->next = *root;
  last->next = newNode;
  *root = newNode;
}

/**
 * @brief Insert data at the front using move semantics.
 */
static inline void cl_push_front_mv_data(Node **root, void **data,
                                         size_t dataSize) {
  Node *newNode = cl_create_node_mv(data, dataSize, NULL);
  cl_push_front_mv_node(root, &newNode);
}

/**
 * @brief Insert data at the front using shallow copy.
 */
static inline void cl_push_front_cp_data(Node **root, void *data,
                                         size_t dataSize) {
  cl_push_front_cp_node(root, cl_create_node_cp(data, dataSize, NULL));
}

/**
 * @brief Insert data at the front using deep copy.
 */
static inline void cl_push_front_deep_cp_data(Node **root, void *data,
                                              size_t dataSize) {
  cl_push_front_deep_cp_node(root,
                             cl_create_node_deep_cp(data, dataSize, NULL));
}

/**
 * @brief Insert a node at the back of the circular linked list (move semantics).
 */
static inline void cl_push_back_mv_node(Node **root, Node **toBePushed) {
  if (!(*toBePushed))
    return;
  if (!(*root)) {
    (*toBePushed)->next = *toBePushed;
    *root = (Node *)move((void **)toBePushed);
    return;
  }

  Node *last = cl_iterate_to_last_node(*root);
  last->next = (Node *)move((void **)toBePushed);
  last->next->next = *root;
}

/**
 * @brief Insert a node at the back of the circular linked list (shallow copy).
 */
static inline void cl_push_back_cp_node(Node **root, Node *toBePushed) {
  if (!toBePushed)
    return;
  if (!(*root)) {
    toBePushed->next = toBePushed;
    *root = toBePushed;
    return;
  }
  Node *last = cl_iterate_to_last_node(*root);
  toBePushed->next = *root;
  last->next = toBePushed;
}

/**
 * @brief Insert a deep copy of a node at the back of the circular linked list.
 */
static inline void cl_push_back_deep_cp_node(Node **root, Node *toBePushed) {
  if (!toBePushed)
    return;
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = malloc(toBePushed->dataLen);
  memmove(newNode->data, toBePushed->data, toBePushed->dataLen);
  newNode->dataLen = toBePushed->dataLen;
  if (!(*root)) {
    newNode->next = newNode;
    *root = newNode;
    return;
  }
  Node *last = cl_iterate_to_last_node(*root);
  newNode->next = *root;
  last->next = newNode;
}

/**
 * @brief Insert data at the back using move semantics.
 */
static inline void cl_push_back_mv_data(Node **root, void **data,
                                        size_t dataSize) {
  Node *newNode = cl_create_node_mv(data, dataSize, NULL);
  cl_push_back_mv_node(root, &newNode);
}

/**
 * @brief Insert data at the back using shallow copy.
 */
static inline void cl_push_back_cp_data(Node **root, void *data,
                                        size_t dataSize) {
  cl_push_back_cp_node(root, cl_create_node_cp(data, dataSize, NULL));
}

/**
 * @brief Insert data at the back using deep copy.
 */
static inline void cl_push_back_deep_cp_data(Node **root, void *data,
                                             size_t dataSize) {
  cl_push_back_deep_cp_node(root, cl_create_node_deep_cp(data, dataSize, NULL));
}

/**
 * @brief Get node at a given index.
 */
static inline Node *cl_get_at_index(Node **root, int idx) {
  return cl_iterate_to_index(root, idx);
}

/**
 * @brief Get data stored at a given index.
 */
static inline void *cl_get_data_by_index(Node **root, int idx) {
  Node *nati = cl_iterate_to_index(root, idx);
  return nati->data;
}

/**
 * @brief Delete node at a given index.
 */
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

/**
 * @brief Delete the first node containing matching data.
 * 
 * @param root Double pointer to head node.
 * @param data Pointer to data to match.
 * @param size Size of the data.
 */
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

/**
 * @brief Frees all nodes in a circular linked list and sets the root pointer to NULL.
 *
 * This function iterates through a circular linked list starting from the root,
 * deallocating the data payload (if any) and the nodes themselves. Because a
 * circular list has no natural end (like NULL in a singly-linked list), the loop
 * stops once it returns back to the root node. After cleanup, the root pointer
 * is reset to NULL to prevent dangling references.
 *
 * @param rootPtrPtr Double pointer to the root node of the circular linked list.
 *                   If *rootPtrPtr is NULL, the function does nothing.
 *
 * @note
 * - Assumes that each node's `data` was dynamically allocated and should be freed.
 * - After calling this, the list is completely destroyed.
 * - Safe to call on an empty list (rootPtrPtr == NULL or *rootPtrPtr == NULL).
 */
static inline void cl_free_list(Node **rootPtrPtr) {
  if (!rootPtrPtr || !*rootPtrPtr) return;

  Node *root = *rootPtrPtr;
  Node *c = root->next;

  // Free every node until we come back to the root
  while (c != root) {
    Node *next = c->next;
    free(c->data);
    free(c);
    c = next;
  }

  // Finally free the root node
  free(root->data);
  free(root);

  *rootPtrPtr = NULL;
}


#endif // CIRCULARLINKEDLIST_H
