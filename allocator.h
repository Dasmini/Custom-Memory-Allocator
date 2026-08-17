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
 * @brief Joins adjacent free blocks together
 * 
 * @param
 */
void coalesce();

/**
 * @brief Performs custom malloc
 * 
 * @param size The number of bytes that need to be allocated
 * @return Returns the base address of the memory allocated if allocation is successful, 
 *                      otherwise returns NULL
 */
unsigned char *my_malloc(int size);

/**
 * @brief Frees the used memory and markes it available for allocation
 * 
 * @param
 */
void my_free(void *ptr);

/**
 * @brief Prints all block details
 */
void dump_heap();

/**
 * @brief Rearranges the freelist if needed while coalescing
 */
void fix_free_list(Block *current, Block *next_block);


#endif