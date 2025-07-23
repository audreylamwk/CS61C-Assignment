#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    node * tortoise = head;
    node * hare = head;
    // need to check that pointer is not null before using it
    while(hare && hare->next && hare->next->next){
        hare = hare->next->next;
        if (tortoise) {
            tortoise = tortoise->next;
        }
        // pointer point to the same address
        if (tortoise == hare) {
            return 1;
        }
    }
    // return out of while loop
    return 0;
}