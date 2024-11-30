
/// These are two-way, meaning that they both refer to their next (child) and their previous (parent) node.

typedef struct list_node {
    void *data;
    struct list_node *next;
    struct list_node *previous;
} list_node;

typedef struct list {
    list_node *start;
} list;

list *create_list();
void delete_list(list *the_list);

list_node *insert_node(list_node *parent_node, void *data);
void delete_node(list_node *node);
void delete_node_and_children(list_node *node);

int get_list_length(list the_list);
list_node* g

