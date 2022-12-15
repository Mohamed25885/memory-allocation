
#ifndef allocator
    #define allocator

/*function declaration.*/

typedef struct _nodeItem
{
    int id;
    int index;
    int size;
} nodeItem;

nodeItem *allocate_first_fit_memory(int);
nodeItem *allocate_best_fit_memory(int);
nodeItem *allocate_worst_fit_memory(int);
void free_memory(nodeItem *);
void print_node(nodeItem *);
void print_memory();
void initialize_memory();
#endif