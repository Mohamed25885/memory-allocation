#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"
#include "linked_list.h"
int main(int argc, char const *argv[])
{

    initialize_list();
    initialize_memory();

    int *nodeOne = (int *)allocate_best_fit_memory(sizeof(int));

    allocate_best_fit_memory(30);

    free_memory(nodeOne);

    allocate_best_fit_memory(4);

    allocate_best_fit_memory(15);
    
    //allocate_worst_fit_memory(8);

    print_memory();
    //printList();

    return 0;
}
