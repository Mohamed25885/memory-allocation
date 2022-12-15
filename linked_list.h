
#ifndef link_list
#define link_list

typedef struct _node
{
    int index;
    int size;
    void *address;

    struct _node *next;
} Node;
void initialize_list();
void* push(int size, int index);
void deleteN(Node *node);
void printList();
Node *find_node(void *address);
#endif