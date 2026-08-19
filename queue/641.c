#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* data;      // Dynamic array to store elements
    int head;       // Index of the front element
    int tail;       // Index of the rear element
    int size;       // Current number of elements inside the deque
    int capacity;   // Maximum allowed capacity (k)
} MyCircularDeque;

/** Initializes the deque with a maximum size of k. */
MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    obj->data = (int*)malloc(k * sizeof(int));
    obj->head = 0;
    obj->tail = 0;  // Initialized to match head
    obj->size = 0;
    obj->capacity = k;
    return obj;
}

/** Checks whether the circular deque is empty or not. */
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    return obj->size == 0;
}

/** Checks whether the circular deque is full or not. */
bool myCircularDequeIsFull(MyCircularDeque* obj) {
    return obj->size == obj->capacity;
}

/** Adds an item at the front of Deque. Returns true if successful. */
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if (myCircularDequeIsFull(obj)) {
        return false;
    }
    // Move head backward circularly. Add capacity to handle negative wraps.
    obj->head = (obj->head - 1 + obj->capacity) % obj->capacity;
    obj->data[obj->head] = value;
    obj->size++;
    return true;
}

/** Adds an item at the rear of Deque. Returns true if successful. */
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if (myCircularDequeIsFull(obj)) {
        return false;
    }
    // Store data at current tail position, then move tail forward circularly
    obj->data[obj->tail] = value;
    obj->tail = (obj->tail + 1) % obj->capacity;
    obj->size++;
    return true;
}

/** Deletes an item from the front of Deque. Returns true if successful. */
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return false;
    }
    // Move head forward circularly
    obj->head = (obj->head + 1) % obj->capacity;
    obj->size--;
    return true;
}

/** Deletes an item from the rear of Deque. Returns true if successful. */
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return false;
    }
    // Move tail backward circularly. Add capacity to handle negative wraps.
    obj->tail = (obj->tail - 1 + obj->capacity) % obj->capacity;
    obj->size--;
    return true;
}

/** Returns the front item from the Deque. Returns -1 if empty. */
int myCircularDequeGetFront(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return -1;
    }
    return obj->data[obj->head];
}

/** Returns the last item from Deque. Returns -1 if empty. */
int myCircularDequeGetRear(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return -1;
    }
    // The actual last element sits right behind the tail pointer
    int targetIndex = (obj->tail - 1 + obj->capacity) % obj->capacity;
    return obj->data[targetIndex];
}

/** Deallocates all memory used by the deque. */
void myCircularDequeFree(MyCircularDeque* obj) {
    if (obj) {
        free(obj->data);
        free(obj);
    }
}
