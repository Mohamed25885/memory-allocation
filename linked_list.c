

#include "linked_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Node **head;

void initialize_list()
{
    head = (Node **)malloc(sizeof(Node *));
}
Node *getHead()
{
    return *head;
}

void print_list()
{
    if (*head == NULL)
        return;
    Node *temp = *head;

    while (temp)
    {
        printf("(%s)[%d -> %d]\n", (temp)->name, temp->index, (temp->index + temp->size-1));
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
Node *find_node_with_name(const char *name)
{
    Node *temp = *head;

    while (temp)
    {
        if (!strcmp(temp->name, name))
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void *push(int size, int index, const char *name)
{

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->address = malloc(size);
    new_node->size = size;
    new_node->name = name;
    new_node->index = index;

    Node *current;
    /* Special case for the head end */
    if (*head == NULL || (*head)->index >= new_node->index)
    {
        new_node->next = *head;
        *head = new_node;
    }
    else
    {
        /* Locate the node before
            the point of insertion */
        current = *head;
        while (current->next != NULL && current->next->index < new_node->index)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    return new_node->address;
}

void deleteN(Node *node)
{
    // Store head node
    Node *temp = *head, *prev;

    if (temp != NULL && temp == node)
    {
        *head = temp->next;
        free(node->address);
        free(node);
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

    free(node->address);
    free(node);
}
void delete_name(const char *name)
{
    // Store head node
    Node *temp = *head, *prev;

    if (temp != NULL && !strcmp(temp->name, name))
    {
        *head = temp->next;
        free(temp->address);
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->name, name))
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;

    free(temp->address);
    free(temp);
}