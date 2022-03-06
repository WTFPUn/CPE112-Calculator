#ifndef STACK_H
#define STACK_H

#include "arraylist.h"

typedef struct
{
    LIST_T* data;
} STACK_T;

/* Create a new stack with the specify capacity
 * Return pointer to the stack structure if successful
 *        or NULL if the stack can't be created 
 *        e.g. memory allocation error  
 */
STACK_T* stackCreate(int capacity);

/* Destroy the stack and release all memory
 */
void stackDestroy(STACK_T* stack);

/* Returns the number of elements (could be zero)
 * or -1 if the stack has not been created
 */
int stackSize(STACK_T* stack);

/* Add new element to the top of the stack
 * Return -1 if the stack hasn't been created
 *        -2 if the stack is full 
 *         1 if the operation is successful
 */
int stackPush(STACK_T* stack, void* data);

/* Remove an element from the top of the stack
 * Return -1 if the stack hasn't been created
 *         1 if the operation is successful
 */
int stackPop(STACK_T* stack, void** data);

// int stackIsTop(STACK_T*, char data);

int stackTopPrio(STACK_T* stack);

#endif