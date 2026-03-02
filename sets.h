#ifndef SETS_H
#define SETS_H

#include <stdlib.h>

enum status {
    MEMORY_ERROR = -1,
    OK = 0,
    INVALID_INPUT = 1,
    ELEM_EXISTS = 2,
};

struct set;

struct set *create_set(const size_t max_capacity,
                       const size_t sizeof_elem,
                       int (*comp_elem)(const void *, const void *),
                       int (*create_copy_elem)(void *, const void *),
                       void (*print_elem)(const void *),
                       void (*destroy_elem)(void *),
                       enum status *status_adr);

int add_elem(struct set *s,
             const void *elem_adr, 
             enum status *status_adr);

int print_set(const struct set *s, enum status *status_adr);

int destroy_set(struct set **s_adr, enum status *status_adr);

struct set *deep_copy_set(const struct set *s, enum status *status_adr);

struct set *union_2set(const struct set *a,
                         const struct set *b,
                         enum status *status_adr);

struct set *intersection_2set(const struct set *a,
                              const struct set *b,
                              enum status *status_adr);

#endif
