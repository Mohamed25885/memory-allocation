
#include "linked_list.h"
#ifndef allocator
    #define allocator

#define BEST_FIT 0
#define WORST_FIT 1
#define FIRST_FIT 2

/*function declaration.*/

void *allocate_memory(int size, const char *name, int mode);
void free_memory(void *);
void free_memory_with_name(const char *);
void print_memory();
void initialize_memory();
#endif