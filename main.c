#include <stdio.h>
#include "allocator.h"


int main()
{
    heap_init();
    char *cptr = my_malloc(5);
    printf("Ptr 1 = %p\n",cptr);
    char *cptr1 = my_malloc(10);
    printf("Ptr 2 = %p\n",cptr1);
    char *cptr2 = my_malloc(2);
    printf("Ptr 3 = %p\n",cptr2);
    char *cptr3 = my_malloc(20);

    dump_heap();
    my_free(cptr1);
    my_free(cptr2);
    my_free(cptr3);
    printf("After freeing 1\n");
    dump_heap();
    coalesce();
    printf("After coalece:\n");
    dump_heap();
    return 0;
}