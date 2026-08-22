#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#define ALIGNMENT_THRESHOLD 8
#define POOL_SIZE 1024
#define FREE 1
#define USED 0

/**
 * @brief Holds the metadata for a single block in the static
 * memory pool, whether that block is currently used or free.
 */
typedef struct Block
{
    int size;            ///< Usable payload size in bytes (excludes this header, always a multiple of ALIGNMENT_THRESHOLD).
    int is_free;         ///< FREE if the block is available for allocation, USED if currently allocated.
    struct Block *next;  ///< Pointer to the next block in the free list. Only meaningful for free blocks; undefined/unused for used blocks.
} Block;

extern Block *free_list_head;

/**
 * @brief Creates the first header for the raw byte memory and
 * sets free-list-head point to this block.
 */
void heap_init();

/**
 * @brief Reduces external fragmentation by combining next adjacent free blocks, 
 *        making previously-unusable split-up free space available for 
 *        larger future allocations again.
 * 
 * It traverses through the blocks using addresses and if comes accross
 * a free block, it checks if the next block in the memory is a free, if yes
 * it removes the next block from the free list using a helper function and
 * updates the size of the current block to the size of the whole merged block.
 * A variable named total-size which includes the header size and the block size.
 * It traverses till the total-size reaches the pool-size.
 * 
 * @return Does not return a value; modifies the heap in place.
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
 * @brief Frees the block of memory in the static heap pool
 * 
 * Traces back to the start of the header of the block from the 
 * address passed by the requester. Checks if the block is already
 * free and does no-op and returns, else, marks the block as free
 * and reinserts the block at the head of the free list. Then it 
 * calls coalesce which merges the adjacent free blocks.
 * 
 * @param ptr This is the address of the block that needs to be freed
 */

void my_free(void *ptr);

/**
 * @brief Gives the dump of information of every block.
 * 
 * It traverses through the blocks through memory and collects the
 * required details of every block and gives the details of each block
 * as the output. 
 * 
 * @return Returns nothing; prints to stdout.
 */
void dump_heap();

/**
 * @brief Gives a statistics of the total size, total used 
 * and free sizes seperately, number of blocks and similar information.
 * 
 * It traverses through the blocks through memory and collects the
 * required details and gives the output as a consolidated
 * data in the last.
 * 
 * @return Returns nothing; prints to stdout. 
 */
 void stat_heap();
 
/**
 * @brief Removes the block from the free list
 * 
 * If the block that need to be removed is the free-list-head,
 * the block next to it is made the free-list-head and then done no-op.
 * If not, traverse till the required block is found and link
 * the previous block to the next block. So now the respective 
 * block is removed from the free list
 * 
 * @param rem_block This is the block that needs to be removed from the free list.
 * @return Returns nothing, modifies the free list in place.
 */
void remove_from_free_list(Block *next_block);


#endif