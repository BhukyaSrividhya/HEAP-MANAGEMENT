#include <stdio.h>

#define HEAP_SIZE 1024  // Total heap size
static char memory_pool[HEAP_SIZE]; // Simulated heap memory

// Metadata structure for memory blocks
typedef struct Block {
    unsigned int size;
    int free;
    struct Block *next;
} Block;

#define BLOCK_SIZE (unsigned int)sizeof(Block)
static Block *freeList = (Block *)memory_pool;

// Initialize the memory pool
void init_heap() {
    freeList->size = HEAP_SIZE - BLOCK_SIZE;
    freeList->free = 1;
    freeList->next = NULL;
}

// Allocate memory
void *allocate(unsigned int size) {
    if (size == 0) {
        printf("Error: Cannot allocate zero bytes.\n");
        return NULL;
    }

    // Align size to multiples of 4 for efficiency
    size = (size + 3) & ~3;

    Block *current = freeList;

    while (current) {
        if (current->free && current->size >= size) {
            // Split block if it's larger than needed
            if (current->size > size + BLOCK_SIZE) {
                Block *newBlock = (Block *)((char *)current + BLOCK_SIZE + size);
                newBlock->size = current->size - size - BLOCK_SIZE;
                newBlock->free = 1;
                newBlock->next = current->next;

                current->size = size;
                current->next = newBlock;
            }

            current->free = 0; // Mark block as allocated
            return (void *)(current + 1);
        }

        current = current->next;
    }

    printf("Error: Not enough memory available.\n");
    return NULL;
}

// Free allocated memory and merge adjacent free blocks
void deallocate(void *ptr) {
    if (!ptr) {
        printf("Error: Null pointer passed to free.\n");
        return;
    }

    printf("Deallocating memory at address: %p\n", ptr); // Print address before deallocation

    Block *block = (Block *)ptr - 1;
    block->free = 1;

    // Coalesce adjacent free blocks
    Block *current = freeList;
    while (current && current->next) {
        if (current->free && current->next->free) {
            current->size += current->next->size + BLOCK_SIZE;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }

    printf("Memory freed successfully at address: %p\n", ptr); // Print address after deallocation
}

// Display memory blocks
void display_memory() {
    Block *current = freeList;
    printf("\nHeap Memory Blocks:\n");
    while (current) {
        printf("[Addr: %p, Size: %u, Free: %d] -> ", (void *)(current + 1), current->size, current->free);
        current = current->next;
    }
    printf("NULL\n");
}

// Main driver with switch-case interaction
int main() {
    init_heap(); // Initialize the memory pool

    int choice;
    void *ptr1 = NULL;
    unsigned int size;

    while (1) {
        printf("\nHeap Management Menu:\n");
        printf("1. Allocate Memory\n");
        printf("2. Free Memory\n");
        printf("3. Display Memory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size to allocate (bytes): ");
                scanf("%u", &size);
                ptr1 = allocate(size);
                if (ptr1) {
                    printf("Memory allocated successfully at address: %p\n", ptr1);
                }
                break;

            case 2:
                if (ptr1) {
                    printf("About to free memory at address: %p\n", ptr1);
                    deallocate(ptr1);
                    ptr1 = NULL;
                } else {
                    printf("No allocated memory to free.\n");
                }
                break;

            case 3:
                printf("Displaying all memory block addresses:\n");
                display_memory();
                break;

            case 4:
                printf("Last allocated address before exit: %p\n", ptr1);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}