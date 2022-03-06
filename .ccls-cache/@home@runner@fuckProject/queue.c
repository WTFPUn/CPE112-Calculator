#include "queue.h"
#include <stdlib.h>

/* Create a new queue with the specify capacity
 * Return pointer to the queue structure if successful
 *        or NULL if the queue can't be created 
 *        e.g. memory allocation error  
 */
QUEUE_T* queueCreate(int capacity)
{
  QUEUE_T* queue = (QUEUE_T*) calloc(1,sizeof(QUEUE_T));
  if(queue == NULL)
    return NULL;
  queue->data = listCreate(capacity);
  if(queue->data == NULL)
    return NULL;
  return queue;
}

/* Destroy the queue and release all memory
 */
void queueDestroy(QUEUE_T* queue)
{
  listDestroy(queue->data);
  free(queue);
}

/* Returns the number of elements (could be zero)
 * or -1 if the queue has not been created
 */
int queueSize(QUEUE_T* queue)
{
  return queue->data->currentSize;
}

/* Add new element to the queue
 * Return -1 if the queue hasn't been created
 *        -2 if the queue is full 
 *         1 if the operation is successful
 */
int queueEnqueue(QUEUE_T* queue, void* data)
{
  if(queue == NULL)
    return -1;
  return listAppend(queue->data, data);
}

/* Remove an element from the queue
 * Return -1 if the queue hasn't been created
 *        -2 if the queue is empty 
 *         1 if the operation is successful
 */
int queueDequeue(QUEUE_T* queue, void** data)
{
  if(queue == NULL)
    return -1;
  if(queue->data->currentSize == 0)
    return -2;
  listGet(queue->data, 0, data);
  listRemoveAt(queue->data,0);
  return 1;
}