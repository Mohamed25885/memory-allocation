
#ifndef link_list
#define link_list

typedef struct _node
{
    int index;
    int size;
    const char *name;
    void *address;

    struct _node *next;
} Node;
void initialize_list();
void *push(int size, int index, const char *name);
void deleteN(Node *node);
void delete_name(const char *name);
void print_list();
Node *getHead();
Node *find_node(void *address);
Node *find_node_with_name(const char *name);
#endif