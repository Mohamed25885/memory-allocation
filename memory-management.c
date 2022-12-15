#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"

int main(int argc, char const *argv[])
{
    initialize_memory();

    nodeItem *nodeOne = allocate_first_fit_memory(20);

    nodeItem *nodeTwo = allocate_first_fit_memory(30);

    free_memory(nodeOne);
    print_memory();
    printf("\n\n");

    nodeItem *nodeThree = allocate_worst_fit_memory(5);

    nodeItem *nodeFour = allocate_worst_fit_memory(15);

    /* nodeItem *nodeFour = allocate_first_fit_memory(15);

 nodeItem *nodeFive = allocate_first_fit_memory(10);

nodeItem *nodeSix = allocate_first_fit_memory(1); */

    print_memory();

    return 0;
}
