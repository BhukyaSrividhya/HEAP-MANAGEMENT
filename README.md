This project implements a custom heap memory manager using a fixed-size memory pool and a linked list to simulate dynamic memory allocation in C. It provides a deeper understanding of how memory allocators like malloc and free work internally.
Features
Static heap simulation using a 1024-byte memory pool.

Dynamic memory allocation (allocate):

Aligns allocations to 4-byte boundaries.

Splits larger free blocks to reduce internal fragmentation.

Memory deallocation (deallocate):

Marks blocks as free.

Coalesces adjacent free blocks to minimize fragmentation.

Memory block structure:

Each block contains metadata: size, free flag, and next pointer.

Managed as a singly linked list.

Interactive user interface:

Allocate memory.

Free memory.

Display the current memory state.



