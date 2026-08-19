#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_CAPACITY 100

// --- Standard Stack Implementation ---
typedef struct {
    int data[STACK_CAPACITY];
    int top;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

void stackPush(Stack* stack, int val) {
    stack->data[++(stack->top)] = val;
}

int stackPop(Stack* stack) {
    return stack->data[(stack->top)--];
}

int stackPeek(Stack* stack) {
    return stack->data[stack->top];
}

bool stackIsEmpty(Stack* stack) {
    return stack->top == -1;
}

void stackFree(Stack* stack) {
    free(stack);
}

// --- MyQueue Implementation using Two Stacks ---
typedef struct {
    Stack* input;
    Stack* output;
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->input = createStack();
    queue->output = createStack();
    return queue;
}

void myQueuePush(MyQueue* obj, int x) {
    // Always push to the input stack
    stackPush(obj->input, x);
}

int myQueuePop(MyQueue* obj) {
    // If output stack is empty, transfer all elements from input stack
    if (stackIsEmpty(obj->output)) {
        while (!stackIsEmpty(obj->input)) {
            stackPush(obj->output, stackPop(obj->input));
        }
    }
    return stackPop(obj->output);
}

int myQueuePeek(MyQueue* obj) {
    // If output stack is empty, transfer all elements from input stack
    if (stackIsEmpty(obj->output)) {
        while (!stackIsEmpty(obj->input)) {
            stackPush(obj->output, stackPop(obj->input));
        }
    }
    return stackPeek(obj->output);
}

bool myQueueEmpty(MyQueue* obj) {
    // The queue is empty only if both stacks are empty
    return stackIsEmpty(obj->input) && stackIsEmpty(obj->output);
}

void myQueueFree(MyQueue* obj) {
    stackFree(obj->input);
    stackFree(obj->output);
    free(obj);
}
