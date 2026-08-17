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

void fix_free_list(Block *current, Block *next_block)
{
    Block *temp = free_list_head;
    Block *prev_block = NULL;
    printf("Free list head : %p\n", free_list_head);
    if(next_block == free_list_head)
    {
        free_list_head = free_list_head -> next;
        printf("Next block is the free list head\n");
    }
        
    if((next_block != temp) && (next_block -> next == current))
    {
        while(temp != next_block)
        {
            prev_block = temp;
            temp = temp -> next;
            printf("temp : %p\n", temp);
        }
        printf("Successfull while\n");
        printf("Prev adress : %p\n", prev_block);
        prev_block -> next = current;
    }
    else
        current -> next = next_block -> next;
}

void coalesce()
{
    Block *current = (Block *)heap;
    Block *next_block;
    int total_size = 0;
    while(total_size < POOL_SIZE)
    {
        
        if(current -> is_free == USED)
        {
            total_size += current -> size + sizeof(Block);
            current = (Block *)((char *)current + (current -> size + sizeof(Block)));
            continue;
        }

        /*
        if(current -> next == NULL)
        {
            total_size += current -> size + sizeof(Block);
            break;
        }
        */
        
        next_block = (Block *)((char *)current + (current -> size + sizeof(Block)));

        if(next_block -> is_free == FREE)
        {
            fix_free_list(current, next_block);
            current -> size = current -> size + sizeof(Block) + next_block -> size;
            if((total_size + current -> size + sizeof(Block)) == POOL_SIZE)
                break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
        }
        else
        {
            total_size += current -> size + sizeof(Block);
            current = next_block;
        }
    }   
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

void my_free(void *ptr)
{
    if(ptr == NULL)
        return;
    char *adrs = (char *)ptr;
    Block *block = (Block *)(adrs - sizeof(Block));
    block -> is_free = FREE;
    block -> next = free_list_head;
    free_list_head = block;
}