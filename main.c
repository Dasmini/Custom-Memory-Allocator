#include <stdio.h>
#include "allocator.h"


int main()
{
    heap_init();
    char *cptr1 = my_malloc(10);
    char *cptr2 = my_malloc(2);
    char *cptr3 = my_malloc(20);
    char *cptr4 = my_malloc(100);
    my_free(cptr1);
    my_free(cptr2);
    coalesce();
    dump_heap();
    return 0;
}