node_t *node(int type) {
    node_t *n = pool(sizeof(node_t));
    n->type = type;
    n->ptk = ptoken;
    n->len = -1;
    return n;
}

node_t **narray(node_t *nodes[], int len) {
    if (len == 0) return NULL;
    int size = sizeof(node_t*)*len;
    node_t **array = pool(size);
    memcpy(array, nodes, size);
    return array;
}

link_t *link() {
    return pool(sizeof(link_t));
}

list_t *list() {
    return pool(sizeof(list_t));
}

node_t *op_n(int op, node_t *nodes[], int len) {
    node_t *n = node(op);
    n->len = len;
    n->array = narray(nodes, len);
    return n;
}

node_t *op0(int op) {
    return op_n(op, NULL, 0);
}

node_t *op1(int op, node_t *n1) {
    node_t *a[] = { n1 };
    return op_n(op, a, 1);
}

node_t *op2(int op, node_t *n1, node_t *n2) {
    node_t *a[] = { n1, n2 };
    return op_n(op, a, 2);
}

node_t *op3(int op, node_t *n1, node_t *n2, node_t *n3) {
    node_t *a[] = { n1, n2, n3 };
    return op_n(op, a, 3);
}

node_t *op4(int op, node_t *n1, node_t *n2, node_t *n3, node_t *n4) {
    node_t *a[] = { n1, n2, n3, n4 };
    return op_n(op, a, 4);
}

node_t *op5(int op, node_t *n1, node_t *n2, node_t *n3, node_t *n4, node_t *n5) {
    node_t *a[] = { n1, n2, n3, n4, n5 };
    return op_n(op, a, 5);
}

node_t *pair(node_t *n1, node_t *n2) {
    return op2(Pair, n1, n2);
}

void list_add(list_t *list, node_t *node) {
    link_t *link = pool(sizeof(link_t));
    link->node = node;
    link->next = list->head;
    list->head = link;
}

// ref: https://www.geeksforgeeks.org/reverse-a-linked-list/
void list_reverse(list_t *list) {
    link_t* t=list->head, *prev=NULL, *next=NULL;
    while (t != NULL) {
        next = t->next; // Store next
        t->next = prev; // Reverse current node's pointer
        prev = t;       // Move pointers one position ahead.
        t = next;       // move to the next
    }
    list->head = prev;
}

void list_print(list_t *list) {
    for (link_t* t=list->head; t!=NULL; t=t->next) {
      printf("%p=>", t);
    }
}
