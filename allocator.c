#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "allocator.h"
#include "linked_list.h"

#define MAX_SIZE 60
#define BEST_FIT 0
#define WORST_FIT 1
#define FIRST_FIT 2
int memory[MAX_SIZE] = {-1};
u_int32_t id_initializer = 0;

void insert_to_memory_tracer(int new_size, int new_index, int size, Node *memory_tracer, u_int8_t *memory_tracer_size, int *memory_tracer_counter);
void *search_available_memory_slots(int size, int mode);

// return index
int min_slot(Node *array, int size);

// return index
int max_slot(Node *array, int size);

void initialize_memory()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        memory[i] = -1;
    }
}
void *allocate_first_fit_memory(int size)
{
    return search_available_memory_slots(size, FIRST_FIT);
}

void *allocate_best_fit_memory(int size)
{
    return search_available_memory_slots(size, BEST_FIT);
}

void *allocate_worst_fit_memory(int size)
{

    return search_available_memory_slots(size, WORST_FIT);
}

void free_memory(void *address)
{
    Node *node = find_node(address);
    for (size_t i = node->index; i < (node->size + node->index); i++)
    {
        memory[i] = -1;
    }

    deleteN(node);
}

void print_memory()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("[%d] ", memory[i]);
    }
    printf("\n");
}

void *search_available_memory_slots(int size, int mode)
{

    u_int8_t memory_tracer_size = 10;
    id_initializer++;
    Node *memory_tracer = (Node *)malloc(sizeof(Node) * ((int)ceil(MAX_SIZE / (memory_tracer_size)))), *current = getHead(), *prev = getHead();

    int new_index = 0, new_size = MAX_SIZE, memory_tracer_counter = 0;
    for (int i = 0; i < MAX_SIZE && current != NULL; i++, prev = current, current = current->next)
    {
        if (i == 0)
        {
            if (current->index == 0)
            {
                new_index = current->index + current->size;
                new_size = MAX_SIZE - new_index;
            }
            else
            {

                if (current->index >= size)
                {
                    new_size = current->index;
                    new_index = 0;

                    insert_to_memory_tracer(new_size, new_index, size, memory_tracer, &memory_tracer_size, &memory_tracer_counter);
                }
            }

            continue;
        }

        if (prev->index + prev->size == current->index)
        {
            new_index = current->index + current->size;
            new_size = MAX_SIZE - new_index;
        }
        else
        {
            new_index = prev->index + prev->size;
            new_size = current->index - new_index;
            insert_to_memory_tracer(new_size, new_index, size, memory_tracer, &memory_tracer_size, &memory_tracer_counter);
        }
    }

    if (getHead() == NULL || (new_index > 0 && new_size >= size && prev == getHead()))
    {

        insert_to_memory_tracer(new_size, new_index, size, memory_tracer, &memory_tracer_size, &memory_tracer_counter);
    }
    if (prev != NULL && (prev->index + prev->size) >= size)
    {

        insert_to_memory_tracer(MAX_SIZE - (prev->index + prev->size), prev->index + prev->size, size, memory_tracer, &memory_tracer_size, &memory_tracer_counter);
    }

    printf("REQUEST: %d\n", size);
    printf("memory_tracer_counter: %d\n", memory_tracer_counter);
    for (int i = 0; i < memory_tracer_counter; i++)
    {
        printf("size: %d", memory_tracer[i].size);
        printf("\tindex: %d\n", memory_tracer[i].index);
    }

    if (memory_tracer_counter <= 0)
    {
        fprintf(stderr, "%s\n", "Requested memory is more than that consecutively available");
        exit(1);
    }

    // assert(("Memory is full", index != -1));

    int slot_index;
    switch (mode)
    {
    case BEST_FIT:
        slot_index = min_slot(memory_tracer, memory_tracer_counter);
        break;

    case WORST_FIT:
        slot_index = max_slot(memory_tracer, memory_tracer_counter);
        break;

    default:
        slot_index = memory_tracer[0].index;
        break;
    }

    for (int j = slot_index; j < (size + slot_index); j++) // allocate memory for the given request
    {
        memory[j] = id_initializer;
    }

    free(memory_tracer);
    return push(size, slot_index);
}

void insert_to_memory_tracer(int new_size, int new_index, int size, Node *memory_tracer, u_int8_t *memory_tracer_size, int *memory_tracer_counter)
{
    if (new_size >= size)
    {
        if ((*memory_tracer_counter) >= ((int)ceil(MAX_SIZE / ((*memory_tracer_size) - 2))))
        {
            memory_tracer_size -= 2;
            memory_tracer = (Node *)realloc(memory_tracer, ((int)ceil(MAX_SIZE / (*memory_tracer_size))));
        }

        Node node = {.index = new_index, .size = new_size};
        memory_tracer[(*memory_tracer_counter)++] = node;
    }
}

int min_slot(Node *array, int size)
{
    int cmp_size = array[0].size;
    int index = array[0].index;

    // Loop through the array
    for (int i = 0; i < size; i++)
    {
        // Compare elements of array with min
        if ((array[i].size) < cmp_size)
        {
            index = array[i].index;
            cmp_size = array[i].size;
        }
    }

    return index;
}

int max_slot(Node *array, int size)
{

    int cmp_size = array[0].size;
    int index = array[0].index;

    // Loop through the array
    for (int i = 0; i < size; i++)
    {
        // Compare elements of array with max
        if ((array[i].size) > cmp_size)
        {
            index = array[i].index;
            cmp_size = array[i].size;
        }
    }

    return index;
}