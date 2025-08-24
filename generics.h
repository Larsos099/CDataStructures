#ifndef GENERICS_H
#define GENERICS_H

#include <stddef.h>

/**
 * @struct Node
 * @brief Node structure for a singly linked list.
 */
typedef struct Node {
    void *data;        /**< Pointer to the stored data */
    size_t dataLen;    /**< Size of the data in bytes */
    struct Node *next; /**< Pointer to the next node */
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
 */
typedef struct DLNode {
    void *data;            /**< Pointer to stored data */
    size_t dataSize;       /**< Size of the data in bytes */
    struct DLNode *next;     /**< Pointer to the next node */
    struct DLNode *previous; /**< Pointer to the previous node */
} DLNode;

#endif // GENERICS_H