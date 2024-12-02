#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

/// Uses malloc().
list* create_list() {
    list* new_list = malloc(sizeof(list));
    return new_list;
}

/// Frees allocated memory.
void delete_list(list *list_) {
    list_node *node = list_->start;
    while (node->next != NULL) {
        node = node->next;
        free(node->previous);
    }
    free(node);
    free(list_);
}

/// Uses malloc().
list_node *insert_node(list_node *parent, void *data) {
    list_node* insertion = malloc(sizeof(list_node));
    insertion->data = data;
    if (parent == NULL) {
        insertion->next = NULL;
        insertion->previous = NULL;
    } else {
        insertion->next = parent->next;
        insertion->previous = parent;
        parent->next = insertion;
    }
    return insertion;
}

/// Frees allocated memory.
void delete_node(list_node *node) {
    // Error handling
    if (node == NULL) {
        printf("\nERROR: Tried to delete a list node, but the node was NULL.");
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

int get_list_length(list list_) {
    int length = 0;
    list_node* node = list_.start;
    while (node != NULL) {
        length++;
        node = node->next;
    }
    return length;
}

list_node* get_last_node(list list_) {
    list_node* node = list_.start;
    while (node != NULL) {
        node = node->next;
    }
    return node;
}