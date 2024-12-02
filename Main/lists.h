
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
void delete_list(list *list_);

list_node *insert_node(list_node *parent, void *data);
void delete_node(list_node *node);

int get_list_length(list list_);
list_node* get_last_node(list list_);