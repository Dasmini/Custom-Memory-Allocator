#include <stdio.h>
#include "allocator.h"

static unsigned char heap[POOL_SIZE];

void heap_init()
{
    Block *block = (Block *)heap;
    block-> size = POOL_SIZE - sizeof(Block);
    block-> is_free = 1;
    block-> next = NULL;
    free_list_head = block;
}

unsigned char *my_malloc(int size)
{
    Block temp = *free_list_head;
    while(temp.next != NULL)
    {
        if(free_list_head->size >= size)
        {
            free_list_head -> is_free = 0;
            return &temp;
        }
    }
    
}