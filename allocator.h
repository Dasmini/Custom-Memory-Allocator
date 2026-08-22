#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#define ALIGNMENT_THRESHOLD 8
#define POOL_SIZE 1024
#define FREE 1
#define USED 0
//int pool_size = 1024;
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
 * @brief Allocates a block of memory from the static heap pool.
 *
 * Searches the free list for the first block large enough to
 * satisfy the request (first-fit). The requested size is rounded
 * up to the nearest multiple of ALIGNMENT_THRESHOLD before the
 * search. If the chosen free block is significantly larger than
 * needed, it is split: the used portion is returned to the caller,
 * and the remainder becomes a new free block reinserted into the
 * free list.
 *
 * @param size Number of bytes requested by the caller. A value
 *             of 0 causes the function to return NULL.
 * @return Pointer to a usable memory region of at least @p size
 *         bytes, or NULL if no free block large enough is
 *         available, or if @p size is 0.
 */
void *my_malloc(int size);

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
  * @brief Prints the stats of the memory
  */
 void stat_heap();
 
/**
 * @brief Removes the next free block in memory while colecsing and establishes the correct link
 */
void remove_from_free_list(Block *next_block);


#endif