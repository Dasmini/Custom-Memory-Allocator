#include <stdio.h>
#include "allocator.h"

static unsigned char heap[POOL_SIZE];
Block *free_list_head = NULL;

void dump_heap()
{
    Block *block = (Block *)heap;
    int total_size = 0;
    int block_count = 1;
    printf("=============HEAP DUMP=============\n");
    printf("\n");
    while(total_size < POOL_SIZE)
    {
        printf("[%d] %p ", block_count, block);
        printf("Size = %-5d", block -> size);
        if (block -> is_free == USED)
            printf("  USED\n");
        else
            printf("  FREE\n");
        //printf("\n");

        block_count++;
        total_size += block -> size + sizeof(Block);
        block = (Block *)((char *)block + (block -> size + sizeof(Block)));
        if(block ->size < 0)
        {
            printf("Error : Size negative\nDump heap terminating...\n");
            return;
        }
    }
    printf("\n");
    printf("===================================\n");
    printf("\n");
}

void stat_heap()
{
    Block *block = (Block *)heap;
    int total_size = 0;
    int total_used = 0;
    int total_free = 0;
    int block_count = 1;
    int largest_free_block = 0;
    if (free_list_head != NULL)
        largest_free_block = free_list_head -> size;
    while(total_size < POOL_SIZE)
    {
        
        if(block ->is_free == FREE)
        {
            total_free += block -> size;
            largest_free_block = block -> size > largest_free_block ? block -> size : largest_free_block;
        }
        else
        {
            
            total_used += block -> size;
        }
        total_size += block -> size + sizeof(Block);
        block = (Block *)((char *)block + (block -> size + sizeof(Block)));
        block_count++;
    }
    printf("Pool size             : %d\n", POOL_SIZE);
    printf("Total used            : %d\n", total_used);
    printf("Total free            : %d\n", total_free);
    printf("Block count           : %d\n", block_count - 1);
    printf("Largest free block    : %d\n", largest_free_block);
}
void heap_init()
{
    Block *block = (Block *)heap;
    block-> size = POOL_SIZE - sizeof(Block);
    block-> is_free = FREE;
    block-> next = NULL;
    free_list_head = block;
}

void remove_from_free_list(Block *next_block)
{
    Block *temp = free_list_head;
    Block *prev_block = NULL;
    if(next_block == free_list_head)
    {
        free_list_head = free_list_head -> next;
        return;
    }
        
    while(temp != next_block)
    {
        prev_block = temp;
        temp = temp -> next;
    }
    prev_block -> next = next_block -> next;
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

        next_block = (Block *)((char *)current + (current -> size + sizeof(Block)));

        if(next_block -> is_free == FREE)
        {
            remove_from_free_list(next_block);
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

void *my_malloc(int size)
{
    if(size <= 0)
        return NULL;
    Block *temp = free_list_head;
    Block *nextBlock = NULL;
    Block *prevBlock = NULL;
    char *alloc_adrs;
    int free_size;  
    size = (size + ALIGNMENT_THRESHOLD - 1) / ALIGNMENT_THRESHOLD * ALIGNMENT_THRESHOLD;
    while(temp != NULL)
    {
        
        if(temp -> is_free == FREE  && temp -> size >= size)
        {
            temp -> is_free = USED;
            free_size = temp -> size - size;
            nextBlock = temp -> next;
            alloc_adrs = ((char *)temp) + sizeof(Block);

            if(free_size >= sizeof(Block) + ALIGNMENT_THRESHOLD)
            {
                temp -> size = size;
                temp -> next = (Block *)(((char *)temp) + sizeof(Block) + size);
                Block *newBlock = temp -> next;
                newBlock -> size = free_size - sizeof(Block);
                newBlock -> is_free = FREE;
                newBlock -> next = nextBlock;
                nextBlock = newBlock;
            }
            
            if(temp == free_list_head)
            {
                free_list_head = nextBlock;
            }
            else
            {
                prevBlock -> next = nextBlock;
            }
            
            return (void *)alloc_adrs;
        }
        prevBlock = temp;
        temp = temp -> next;
    }
    printf("ERROR : Required size of memory not available\n");
    return NULL; 
}

void my_free(void *ptr)
{
    if(ptr == NULL)
        return;
    char *adrs = (char *)ptr;
    Block *block = (Block *)(adrs - sizeof(Block));
    if(block -> is_free == FREE)
        return;
    block -> is_free = FREE;
    block -> next = free_list_head;
    free_list_head = block;
    coalesce();
}