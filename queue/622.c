#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* data;      // Dynamic array to store queue elements
    int head;       // Index of the front element
    int tail;       // Index of the rear element
    int size;       // Current number of elements inside the queue
    int capacity;   // Maximum allowed capacity (k)
} MyCircularQueue;

/** Initializes the object with the size of the queue to be k. */
MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* obj = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    obj->data = (int*)malloc(k * sizeof(int));
    obj->head = 0;
    obj->tail = -1; // Initialized to -1 so first insert goes to index 0
    obj->size = 0;
    obj->capacity = k;
    return obj;
}

/** Checks whether the circular queue is empty or not. */
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return obj->size == 0;
}

/** Checks whether the circular queue is full or not. */
bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return obj->size == obj->capacity;
}

/** Inserts an element into the circular queue. Return true if successful. */
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (myCircularQueueIsFull(obj)) {
        return false;
    }
    // Advance tail pointer circularly and insert element
    obj->tail = (obj->tail + 1) % obj->capacity;
    obj->data[obj->tail] = value;
    obj->size++;
    return true;
}

/** Deletes an element from the circular queue. Return true if successful. */
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) {
        return false;
    }
    // Advance head pointer circularly
    obj->head = (obj->head + 1) % obj->capacity;
    obj->size--;
    return true;
}

/** Gets the front item from the queue. If empty, return -1. */
int myCircularQueueFront(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) {
        return -1;
    }
    return obj->data[obj->head];
}

/** Gets the last item from the queue. If empty, return -1. */
int myCircularQueueRear(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj)) {
        return -1;
    }
    return obj->data[obj->tail];
}

/** Deallocates all memory used by the queue. */
void myCircularQueueFree(MyCircularQueue* obj) {
    if (obj) {
        free(obj->data);
        free(obj);
    }
}
