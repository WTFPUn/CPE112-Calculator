#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct
{
    void** data;
    int currentSize;
    int maxSize;
    int currentIndex;  
} LIST_T;

/* Create a new list with the specify capacity
 * Return pointer to the list structure if successful
 *        or NULL if the list can't be created 
 *        e.g. memory allocation error  
 */
LIST_T* listCreate(int capacity);

/* Destroy the list and release all memory
 */
void listDestroy(LIST_T* list);

/* Returns the number of elements (could be zero)
 * or -1 if the list has not been created
 */
int listSize(LIST_T* list);

/* Returns the maximum number of element that this list can hold
 * or -1 if the list has not been created
 */
int listCapacity(LIST_T* list);

/* Insert new element into the list at the specify index
 * Return -1 if the list hasn't been created
 *        -2 if the list is full 
 *         1 if the operation is successful
 */
int listInsertAt(LIST_T* list, int index, void* data);

/* Add new element at the end of the list
 * Return -1 if the list hasn't been created
 *        -2 if the list is full 
 *         1 if the operation is successful
 */
int listAppend(LIST_T* list, void* data);

/* Remove an element at the specify index
 * Return -1 if the list hasn't been created
 *.       -2 if the index is invalid
 *         1 if the operation is successful
 */
int listRemoveAt(LIST_T* list, int index);

/* Get an element at the specify index
 * Return -1 if the list hasn't been created
 *        -2 if the index is invalid
 *         1 if the operation is successful
 */
int listGet(LIST_T* list, int index, void** data);

/* Reset an internal iterator so that the next call to listGetNext 
 * will return the first element of the list
 * Return -1 if the list hasn't been created
 *         1 if the operation is successful
 */
int listReset(LIST_T* list);

/* Get the current element using an internal iterator
 * Return -1 if the list hasn't been created
 *         1 if the operation is successful
 */
int listGetNext(LIST_T* list, void** data);

/* Check whether there is any element to be returned from listGetNext
 * Return -1 if the list hasn't been created
 *         0 if there still some elements left to be returned from listGetNext
 *         1 if there isn't any element to be returned from listGetNext
 */
int listAtEnd(LIST_T* list);

#endif