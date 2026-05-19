#ifndef FIFO_H
#define FIFO_H
#include "generics.h"
#include <cstddef>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Enqueues an existing node at the back of the FIFO queue.
 * @param queue Pointer to the FIFO queue.
 * @param node Pointer to pointer to the node to enqueue (ownership transferred).
 */
static inline void fifo_enqueue_node(fifo_queue* queue, QNode** node) {
    QNode* oldBack = queue->back;
    (*node)->next = NULL;
    if(!queue->root) {
        queue->root = (QNode*)move((void**)node);
        queue->back = queue->root;
    }
    else {
        queue->back = (QNode*)move((void**)node);
        oldBack->next = queue->back;
    }
    queue->len += 1;
}

/**
 * @brief Dequeues a node from the front of the FIFO queue.
 * @param queue Pointer to the FIFO queue.
 * @return Pointer to the dequeued node, or NULL if the queue is empty.
 */
static inline QNode* fifo_dequeue(fifo_queue* queue) {
    if(!queue->root) return NULL;
    QNode* oldRoot = (QNode*)move((void**)(&(queue->root)));
    QNode* newRoot = (QNode*)move((void**)&(oldRoot->next));
    queue->root = (QNode*)move((void**)&newRoot);
    queue->len -= 1;
    if(queue->len == 1 || queue->len == 0) {
        queue->back = queue->root;
    }
    return oldRoot;
}

/**
 * @brief Creates and initializes an empty FIFO queue.
 * @return Pointer to the new FIFO queue, or NULL on allocation failure.
 */
static inline fifo_queue* create_fifo() {
    fifo_queue *n = (fifo_queue*)malloc(sizeof(fifo_queue));
    if(!n) return NULL;
    n->back = NULL;
    n->root = NULL;
    n->len = 0;
    return n;
}

/**
 * @brief Creates a new queue node using move semantics for the data.
 * @param data Pointer to pointer of data (ownership transferred).
 * @param dataSize Size of the data in bytes.
 * @return Pointer to the new queue node, or NULL on allocation failure.
 */
static inline QNode* qnode_create_move(void** data, size_t dataSize) {
    QNode* n = (QNode*)calloc(1, sizeof(QNode));
    if(!n) return NULL;
    n->data = move(data);
    n->dataSize = dataSize;
    return n;
}

/**
 * @brief Creates a new queue node using shallow copy of data (pointer not copied).
 * @param data Pointer to the data (not copied).
 * @param dataSize Size of the data in bytes.
 * @return Pointer to the new queue node, or NULL on allocation failure.
 * @note Node does not own the data.
 */
static inline QNode* qnode_create_shallow(void* data, size_t dataSize) {
    QNode* n = (QNode*)calloc(1, sizeof(QNode));
    if(!n) return NULL;
    n->data = data;
    n->dataSize = dataSize;
    return n;
}

/**
 * @brief Creates a new queue node with a deep copy of the data.
 * @param data Pointer to the data to copy.
 * @param dataSize Size of the data in bytes.
 * @return Pointer to the new queue node, or NULL on allocation failure.
 */
static inline QNode* qnode_create_copy(void* data, size_t dataSize) {
    QNode* n = (QNode*)calloc(1, sizeof(QNode));
    if(!n) return NULL;
    n->data = calloc(1, dataSize);
    memmove(n->data, data, dataSize);
    n->dataSize = dataSize;
    return n;
}

/**
 * @brief Enqueues data at the back of the queue using move semantics.
 * @param queue Pointer to the FIFO queue.
 * @param data Pointer to pointer of data (ownership transferred).
 * @param dataSize Size of the data in bytes.
 */
static inline void fifo_enqueue_data_move(fifo_queue* queue, void** data, size_t dataSize) {
    QNode* n = qnode_create_move(data, dataSize);
    fifo_enqueue_node(queue, &n);
}

/**
 * @brief Enqueues data at the back of the queue using shallow copy.
 * @param queue Pointer to the FIFO queue.
 * @param data Pointer to the data (not copied).
 * @param dataSize Size of the data in bytes.
 */
static inline void fifo_enqueue_data_shallow(fifo_queue* queue, void* data, size_t dataSize) {
    QNode* n = qnode_create_shallow(data, dataSize);
    fifo_enqueue_node(queue, &n);
}

/**
 * @brief Enqueues data at the back of the queue using deep copy.
 * @param queue Pointer to the FIFO queue.
 * @param data Pointer to data to copy.
 * @param dataSize Size of the data in bytes.
 */
static inline void fifo_enqueue_data_copy(fifo_queue *queue, void *data, size_t dataSize) {
    QNode* n = qnode_create_copy(data, dataSize);
    fifo_enqueue_node(queue, &n);
}
#endif // FIFO_H