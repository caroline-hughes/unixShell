// linked list struct implementation
// based on Nat's implementation

#ifndef LINKEDL_H
#define LINKEDL_H

typedef struct linkedl {
    char* head;
    struct linkedl* rest;
} linkedl;

const char* get_head(linkedl* list);

linkedl* cons(char* new_head, linkedl* curr_list);
void free_linkedl(linkedl* l);
void print_order(linkedl* l);
long length(linkedl* l);
linkedl* reverse_and_free(linkedl* l);
linkedl* get_reverse(linkedl* l);

#endif
