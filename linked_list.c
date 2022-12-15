

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

Node **head;

void initialize_list()
{
    head = (Node **)malloc(sizeof(Node *));
}

void printList()
{
    Node *temp = *head;

    while (temp)
    {
        printf("[%p] [%p]->%p\n", (temp)->address, temp,
               (temp)->next);
        temp = (temp)->next;
    }
    printf("\n\n");
}

Node *find_node(void *address)
{
    Node *temp = *head;

    while (temp)
    {
        if (temp->address == address)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void *push(int size, int index)
{

    Node *node = (Node *)malloc(sizeof(Node));
    node->address = malloc(size);
    node->size = size;
    node->index = index;

    node->next = (*head);
    (*head) = node;
    return node->address;
}

void deleteN(Node *node)
{
    // Store head node
    Node *temp = *head, *prev;

    if (temp != NULL && temp == node)
    {
        *head = temp->next;
        free(node);
        free(node->address);
        return;
    }

    while (temp != NULL && temp != node)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;

    free(node);
    free(node->address);
}