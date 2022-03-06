#ifndef QUEUE_H
#define QUEUE_H

#include "arraylist.h"

typedef struct
{
    LIST_T* data;
} QUEUE_T;

/* Create a new queue with the specify capacity
 * Return pointer to the queue structure if successful
 *        or NULL if the queue can't be created 
 *        e.g. memory allocation error  
 */
QUEUE_T* queueCreate(int capacity);

/* Destroy the queue and release all memory
 */
void queueDestroy(QUEUE_T* queue);

/* Returns the number of elements (could be zero)
 * or -1 if the queue has not been created
 */
int queueSize(QUEUE_T* queue);

/* Add new element to the queue
 * Return -1 if the queue hasn't been created
 *        -2 if the queue is full 
 *         1 if the operation is successful
 */
int queueEnqueue(QUEUE_T* queue, void* data);

/* Remove an element from the queue
 * Return -1 if the queue hasn't been created
 *        -2 if the queue is empty 
 *         1 if the operation is successful
 */
int queueDequeue(QUEUE_T* queue, void** data);


#endif