#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

/// Uses malloc().
list* create_list() {
    list* new_list = malloc(sizeof(list_node));
    return new_list;
}

/// Frees allocated memory.
void delete_list(list *the_list) {
    delete_node_and_children(the_list->start);
    free(the_list);
}

/// Uses malloc().
list_node *insert_node(list_node *parent_node, void *data) {
    list_node* new_node = malloc(sizeof(list_node));
    new_node->data = data;
    if (parent_node == NULL) {
        new_node->next = NULL;
        new_node->previous = NULL;
    } else {
        new_node->next = parent_node->next;
        new_node->previous = parent_node;
        parent_node->next = new_node;
    }
    return new_node;
}

/// Frees allocated memory.
void delete_node(list_node *node) {
    // Error handling
    if (node == NULL) {
        printf("ERROR: Tried to delete a list node, but the node was NULL.");
        exit(EXIT_FAILURE);
    }
    if (node->next != NULL) {
        node->next->previous = node->previous;
    }
    if (node->previous != NULL) {
        node->previous->next = node->next;
    }
    free(node);
}

/// Frees allocated memory.
void delete_node_and_children(list_node *node) {
    if (node->next != NULL) {
        delete_node_and_children(node);
    }
    free(node);
}

int get_list_length(list the_list) {
    int length = 0;
    list_node* node = the_list.start;
    while (node != NULL) {
        length++;
        node = node->next;
    }
    return length;
}

list_node* get_last_node(list the_list) {
    list_node* node = the_list.start;
    while (node != NULL) {
        node = node->next;
    }
    return node;
}


