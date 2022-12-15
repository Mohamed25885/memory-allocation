#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "allocator.h"
#include "linked_list.h"
#define MAX_SIZE 60
#define BEST_FIT 0
#define WORST_FIT 1
int memory[MAX_SIZE] = {-1};
u_int32_t id_initializer = 0;

void *search_available_memory_slots(Node *, int size, int mode);

void min_slot(Node *node, Node *array, int size);

void max_slot(Node *node, Node *array, int size);

void initialize_memory()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        memory[i] = -1;
    }
}
void *allocate_first_fit_memory(int size)
{
    int index = -1;
    u_int32_t size_counter = 0;
    u_int8_t flag = 0;
    id_initializer++;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (size_counter == size) // exit if the allocated size equals to the requested size
        {
            break;
        }
        size_counter++;

        if (!flag) // store the index of the first captured free memory
        {
            index = i;
            flag = 1;
        }
        /* if (memory[i] < 0) // store the id of the current node if the memory is free
        {
            memory[i] = id_initializer;
        } */
        if (memory[i] >= 0)
        {
            // if the current memory space is already assigned

            flag = 0; // set the flag flase, so that the index gets reassigned

            size_counter--;

            // if the next memory space is not empty, and the previous one is the current id, (keeping in mind that the size_count < size)
            if (i >= 1 && memory[i + 1] > 0 && memory[i - 1] < 0)
            {
                /* for (int j = index; j < i; j++) // delocate the allocated memory since it means the space isnt enough to fit the request
                {
                    memory[j] = -1;
                } */
                size_counter = 0; // set the counter to zero to start counting again
            }
            index = -1;
        }
    }

    assert(("Memory is full", index != -1));
    assert(("Requested memory is more than that consecutively available", size_counter == size));

    for (int j = index; j < (size + index); j++) // allocate memory for the given request
    {
        memory[j] = id_initializer;
    }

    Node *node = malloc(sizeof(Node));
    //node->id = id_initializer;
    node->address = malloc(size);
    node->size = size;
    node->index = index;
    push(node);
    return node->address;
}

void *allocate_best_fit_memory(int size)
{
    Node *node = (Node *)malloc(sizeof(Node));
    return search_available_memory_slots(node, size, BEST_FIT);
}

void *allocate_worst_fit_memory(int size)
{
    Node *node = (Node *)malloc(sizeof(Node));
    return search_available_memory_slots(node, size, WORST_FIT);
}

void free_memory(void *address)
{
    Node *node = find_node(address);
    for (size_t i = node->index; i < (node->size + node->index); i++)
    {
        memory[i] = -1;
    }

    node->size = 0;
    node->index = 0;
    deleteN(node);
}

/* void print_node(Node *node)
{

    printf("id: %p\n", node->id);
    printf("address: %p\n", node->address);
    printf("size: %d\n", node->size);
    printf("index: %d\n", node->index);
    printf("global: %d\n", id_initializer);
    printf("\n");
} */

void print_memory()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("[%d] ", memory[i]);
    }
    printf("\n");
}

void *search_available_memory_slots(Node *node, int size, int mode)
{
    int index = -1;
    u_int32_t size_counter = 0, memory_tracer_counter = 0;
    u_int8_t flag = 0, memory_tracer_size = 10;
    id_initializer++;
    Node *memory_tracer = (Node *)malloc(sizeof(Node) * ((int)ceil(MAX_SIZE / (memory_tracer_size))));

    for (int i = 0; i < MAX_SIZE; i++)
    {

        size_counter++;

        if (!flag) // store the index of the first captured free memory
        {
            index = i;
            flag = 1;
        }
        /* if (memory[i] < 0) // store the id of the current node if the memory is free
        {
            memory[i] = id_initializer;
        } */
        if (memory[i] >= 0)
        {
            // if the current memory space is already assigned

            flag = 0; // set the flag flase, so that the index gets reassigned

            size_counter--;

            // if the next memory space is not empty, and the previous one is the current id, (keeping in mind that the size_count < size)
            if (i >= 1 && memory[i + 1] > 0 && memory[i - 1] < 0)
            {
                /* for (int j = index; j < i; j++) // delocate the allocated memory since it means the space isnt enough to fit the request
                {
                    memory[j] = -1;
                } */
                if (size_counter >= size) // exit if the allocated size equals to the requested size
                {

                    if (memory_tracer_counter >= ((int)ceil(MAX_SIZE / (memory_tracer_size - 2))))
                    {
                        memory_tracer_size -= 2;
                        memory_tracer = (Node *)realloc(memory_tracer, ((int)ceil(MAX_SIZE / (memory_tracer_size))));
                    }

                    Node node = {.index = index, .size = size_counter};
                    memory_tracer[memory_tracer_counter++] = node;
                }

                size_counter = 0; // set the counter to zero to start counting again
            }
            index = -1;
        }
    }

    if (size_counter >= size)
    {
        Node node = {.index = index, .size = size_counter};
        memory_tracer[memory_tracer_counter++] = node;
    }
    printf("ID: %d\n", id_initializer);
    printf("REQUEST: %d\n", size);
    for (int i = 0; i < memory_tracer_counter; i++)
    {
        printf("size: %d", memory_tracer[i].size);
        printf("\tindex: %d\n", memory_tracer[i].index);
    }

    assert(("Memory is full", index != -1));
    assert(("Requested memory is more than that consecutively available", memory_tracer_counter != 0));

    switch (mode)
    {
    case BEST_FIT:
        min_slot(node, memory_tracer, memory_tracer_counter);
        break;

    default:
        max_slot(node, memory_tracer, memory_tracer_counter);
        break;
    }

    for (int j = node->index; j < (size + node->index); j++) // allocate memory for the given request
    {
        memory[j] = id_initializer;
    }
    /*  printf("id_initializer: %d\n", id_initializer);
     printf("\n");
     print_memory(); */

    //node->id = id_initializer;
    node->address = malloc(size);
    node->size = size;
    node->index = index;
    push(node);
    return node->address;
}

void min_slot(Node *node, Node *array, int size)
{
    *node = array[0];

    // Loop through the array
    for (int i = 0; i < size; i++)
    {
        // Compare elements of array with min
        if ((array[i].size) < ((*node).size))
            (*node) = array[i];
    }
}

void max_slot(Node *node, Node *array, int size)
{
    *node = array[0];

    // Loop through the array
    for (int i = 0; i < size; i++)
    {
        // Compare elements of array with min
        if ((array[i].size) > ((*node).size))
            (*node) = array[i];
    }
}