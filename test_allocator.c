#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "allocator.h"

#define MAX_TEST 50


typedef struct Label
{
    char label_name[10];
    char *label_ptr;
} Label;
Label label[MAX_TEST];

void test_fun()
{
    char input[MAX_TEST];
    char  mem_ptr[10];
    char *token, *end_check;
    int line = 1, size, label_iter = 0;

    FILE *fptr = fopen("test.txt", "r");
    if(fptr == NULL)
        perror("fopen");
    while(1){
        end_check = fgets(input, MAX_TEST, fptr);
        if (end_check == NULL)
            break;
        token = strtok(input, " \n");
        if(token == NULL)
        {
            line++;
            continue;
        }
        else if(strcmp(token, "init") == 0)
        {   
            heap_init();
        }
        else if(strcmp(token, "alloc") == 0)
        {
            token = strtok(NULL, " ");
            if(!token)
            {
                printf("Enter proper test case in line %d\n", line);
                break;
            }
            strcpy(mem_ptr, token);
            token = strtok(NULL, " ");
            if(!token)
            {
                printf("Enter proper test case in line %d\n", line);
                break;
            }
            size = atoi(token);
            char *ptr_alloc = my_malloc(size);
            if(ptr_alloc == NULL)
            {
                printf("Allocation failed!\n");
            }
            else
            {
                strcpy(label[label_iter].label_name, mem_ptr);
                label[label_iter].label_ptr = ptr_alloc;
                label_iter++;
                printf("my_malloc(%d) called\n", size);
            }  
        }
        else if(strcmp(token, "free") == 0)
        {
            int found_flag = 0;
            token = strtok(NULL, " \n");
            if(!token)
            {
                printf("Enter proper test case in line %d\n", line);
                break;
            }
            strcpy(mem_ptr, token);
            for (int i = 0; i < label_iter; i++)
            {
                if (strcmp(label[i].label_name, mem_ptr) == 0)
                {
                    my_free(label[i].label_ptr);
                    printf("%s freed\n",label[i].label_name);
                    found_flag = 1;
                    break;
                }
            }
            if( !found_flag)
                printf("Check pointer on test case! Failed to free.\n");
        }
        else if(strcmp(token, "dump") == 0)
        {
            dump_heap();
        }
        else if(strcmp(token, "stats") == 0)
        { 
            stat_heap();
        }
        else
        {
            printf("Invalid operation name in 'line %d' in test case\n", line + 1);
            printf("%s : %ld\n", input, strlen(input));
            break;
        }
        line++;
    }
}
