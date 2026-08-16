#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#define POOL_SIZE 1000
#define FREE 1
#define USED 0
typedef struct Block
{
    int size;
    int is_free;
    struct Block *next;
} Block;

extern Block *free_list_head;

/**
 * @brief Initializes the firrst header of the raw free bytes
 */
void heap_init();

/**
 * @brief Performs custom malloc
 * 
 * @param size The number of bytes that need to be allocated
 * @return Returns the base address of the memory allocated if allocation is successful, 
 *                      otherwise returns NULL
 */
unsigned char *my_malloc(int size);

#endif