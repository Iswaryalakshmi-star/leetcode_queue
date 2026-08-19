#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- LeetCode API declarations for context ---
bool NestedIntegerIsInteger(struct NestedInteger*);
int NestedIntegerGetInteger(struct NestedInteger*);
struct NestedInteger** NestedIntegerGetList(struct NestedInteger*);
int NestedIntegerGetListSize(struct NestedInteger*);

// --- Iterator Definition ---
struct NestedIterator {
    int* data;      // Dynamic array holding the completely flattened integers
    int size;       // Total number of integers found
    int capacity;   // Allocated capacity of the array
    int cursor;     // Current tracking pointer for the iterator
};

// Helper function to recursively flatten the data via Depth-First Search
void flattenDFS(struct NestedInteger** list, int listSize, struct NestedIterator* iterator) {
    for (int i = 0; i < listSize; i++) {
        if (NestedIntegerIsInteger(list[i])) {
            // Resize buffer dynamically if capacity runs out
            if (iterator->size >= iterator->capacity) {
                iterator->capacity *= 2;
                iterator->data = (int*)realloc(iterator->data, iterator->capacity * sizeof(int));
            }
            // Store the flat integer
            iterator->data[iterator->size++] = NestedIntegerGetInteger(list[i]);
        } else {
            // Extract the child sublist and its size, then dive deeper
            struct NestedInteger** subList = NestedIntegerGetList(list[i]);
            int subListSize = NestedIntegerGetListSize(list[i]);
            flattenDFS(subList, subListSize, iterator);
        }
    }
}

struct NestedIterator *nestedIterCreate(struct NestedInteger** nestedList, int nestedListSize) {
    struct NestedIterator *iterator = (struct NestedIterator*)malloc(sizeof(struct NestedIterator));
    
    // Initialize properties with default baseline allocations
    iterator->capacity = 100; 
    iterator->size = 0;
    iterator->cursor = 0;
    iterator->data = (int*)malloc(iterator->capacity * sizeof(int));
    
    // Run recursion to flatten the nested structure completely into array blocks
    flattenDFS(nestedList, nestedListSize, iterator);
    
    return iterator;
}

bool nestedIterHasNext(struct NestedIterator *iter) {
    // Returns true if our tracking cursor hasn't read past the flat collection size
    return iter->cursor < iter->size;
}

int nestedIterNext(struct NestedIterator *iter) {
    // Deliver the current index's value and post-increment the tracking cursor pointer
    return iter->data[iter->cursor++];
}

/** Deallocate memory once execution finishes */
void nestedIterFree(struct NestedIterator *iter) {
    if (iter) {
        free(iter->data);
        free(iter);
    }
}
