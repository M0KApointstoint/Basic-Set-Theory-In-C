#include <stdlib.h>
#include "sets.h"

struct set {
    void *arr;
    size_t nr_elem;
    size_t max_capacity;
    size_t sizeof_elem;
};

struct set *create_set(const size_t max_capacity,
                       const size_t sizeof_elem,
                       enum status *status_adr)
{
    struct set *s = malloc(sizeof(struct set));
    if (!s) {
        if (status_adr) {
            *status_adr = MEMORY_ERROR;
        }
        return NULL;
    }
    s->arr = malloc(max_capacity * sizeof_elem);
    if (!s->arr) {
        free(s);
        if (status_adr) {
            *status_adr = MEMORY_ERROR;
        }
        return NULL;
    }
    s->max_capacity = max_capacity;
    s->sizeof_elem = sizeof_elem;
    if (status_adr) {
        *status_adr = OK;
    }
    return s;
}
