#include <stdio.h>
#include "allocator.h"

void test_fun();

int main()
{

    /*heap_init();
    char *cptr1 = my_malloc(10);
    char *cptr2 = my_malloc(2);
    char *cptr3 = my_malloc(900);
    my_free(cptr2);
    dump_heap();
    stat_heap();
    */
    test_fun();
    return 0;
}