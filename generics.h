#ifndef GENERICS_H
#define GENERICS_H

#include <stddef.h>

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

#endif // GENERICS_H