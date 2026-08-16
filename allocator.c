#include <stdio.h>
#include "allocator.h"

static unsigned char heap[POOL_SIZE];
Block *free_list_head = NULL;

void dump_heap()
{
    Block *block = (Block *)heap;
    int total_size = 0;
    int block_count = 1;
    while(total_size < POOL_SIZE)
    {
        printf("Block - %d\n", block_count);
        printf("Block start address -  %p\n", block);
        printf("Block Size - %d\n", block -> size);
        if (block -> is_free == USED)
            printf("Block status - USED\n");
        else
            printf("Block status - FREE\n");
        printf("\n");

        block_count++;
        total_size += block -> size + sizeof(Block);
        block = (Block *)((char *)block + (block -> size + sizeof(Block)));
    }
}
void heap_init()
{
    Block *block = (Block *)heap;
    block-> size = POOL_SIZE - sizeof(Block);
    block-> is_free = FREE;
    block-> next = NULL;
    free_list_head = block;
}

unsigned char *my_malloc(int size)
{
    Block *temp = free_list_head;
    Block *nextBlock = NULL;
    Block *prevBlock = NULL;
    char *alloc_adrs;
    int free_size;
    while(temp != NULL)
    {
        
        if(temp -> is_free == FREE  && temp -> size >= size)
        {
            //printf("Space is found at %p\n", temp);
            temp -> is_free = USED;
            free_size = temp -> size - size;
            nextBlock = temp -> next;
            temp -> size = size;
            temp -> next = (Block *)(((char *)temp) + sizeof(Block) + size);
            alloc_adrs = ((char *)temp) + sizeof(Block);

            //printf("New free space header starts at %p\n", temp -> next);
            Block *newBlock = temp -> next;
            newBlock -> size = free_size - sizeof(Block);
            newBlock -> is_free = FREE;
            newBlock -> next = nextBlock;

            if(temp == free_list_head)
            {
                //printf("newBlock is being assigned as free list head\n");
                free_list_head = newBlock;
            }
            else
            {
                //printf("Previous block is linked to new block\n");
                prevBlock -> next = newBlock;
            }
            return alloc_adrs;
        }
        prevBlock = temp;
        temp = temp -> next;
    }
    return NULL;
    
}