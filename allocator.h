#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#define POOL_SIZE 1000
typedef struct Block
{
    int size;
    int is_free;
    struct Block *next;
} Block;

extern Block *free_list_head;
void heap_init();
#endif