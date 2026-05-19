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



/**
 * @struct QNode
 * @brief Node for a Queue.
 */
typedef struct QNode {
    void* data;         /**< Pointer to stored data */
    struct QNode* next;    /**< Pointer to the next Node */
    size_t dataSize;    /**< Size of the data in bytes */
} QNode;


/**
 * @struct fifo_queue
 * @brief Cointainer & Header Struct for a FIFO Queue
 */
typedef struct fifo_queue {
    struct QNode *root;    /**< Pointer to first QNode */
    struct QNode *back;    /**< Pointer to last QNode */
    size_t len;         /**< Size of FIFO Queue */
} fifo_queue;

#endif // GENERICS_H