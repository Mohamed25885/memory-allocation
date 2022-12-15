
#include "linked_list.h"
#ifndef allocator
    #define allocator

/*function declaration.*/


void* allocate_first_fit_memory(int);
void* allocate_best_fit_memory(int);
void* allocate_worst_fit_memory(int);
void free_memory(void *);
void print_memory();
void initialize_memory();
#endif