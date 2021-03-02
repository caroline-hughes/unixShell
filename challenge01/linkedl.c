#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedl.h"

const char* get_head(linkedl* list) {
    //const char* copy_of_head = strdup(list->head); // will need to be freed
    return list->head;
}

linkedl*
cons(char* new_head, linkedl* curr_list){
    linkedl* result = malloc(sizeof(linkedl));
    result->head = strdup(new_head);
    result->rest = curr_list;
    return result;
}


void
free_linkedl(linkedl* list) {
    if (list) {
        free_linkedl(list->rest); // recur on the rest
        free(list->head);
        free(list);
    }
}


void
print_order(linkedl* l) {
    for(; l; l = l->rest) {
        printf("%s\n", l->head);
    }
}


long
length(linkedl* l) {
    long len = 0;
    for(; l; l = l->rest) {
        ++len;
    }
    return len;
}


linkedl*
get_reverse(linkedl* l){
    linkedl* result = 0;
    for(; l; l = l->rest) {
        result = cons(l->head, result);
    }
    return result;
}

linkedl*
reverse_and_free(linkedl* l){
    linkedl* rev = get_reverse(l);
    free_linkedl(l); // free the original
    return rev;
}
