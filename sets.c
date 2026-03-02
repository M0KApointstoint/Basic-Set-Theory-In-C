#include <stdlib.h>
#include "sets.h"

struct set {
    void *arr;
    size_t nr_elem;
    size_t max_capacity;
    size_t sizeof_elem;
    int (*comp_elem)(const void *, const void *);
    int (*create_copy_elem)(void *, const void *);
    void (*print_elem)(const void *);
    void (*destroy_elem)(void *);
};

struct set *create_set(const size_t max_capacity,
                       const size_t sizeof_elem,
                       int (*comp_elem)(const void *, const void *),
                       int (*create_copy_elem)(void *, const void *),
                       void (*print_elem)(const void *),
                       void (*destroy_elem)(void *),
                       enum status *status_adr)
{
    if (!max_capacity ||
        !sizeof_elem ||
        !comp_elem || 
        !create_copy_elem || 
        !print_elem || 
        !destroy_elem) {
        if (status_adr) {
            *status_adr = INVALID_INPUT;
        }
        return NULL;
    }
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
    s->comp_elem = comp_elem;
    s->create_copy_elem = create_copy_elem;
    s->print_elem = print_elem;
    s->destroy_elem = destroy_elem;
    if (status_adr) {
        *status_adr = OK;
    }
    return s;
}

int exist_check(const struct set *s, const void *elem_adr)
{
    for (size_t i = 0; i < s->nr_elem; ++i) {
        char *curr_elem_adr = (char *)s->arr + i * s->sizeof_elem;
        if (!s->comp_elem(curr_elem_adr, elem_adr)) {
            return 1;
        }
    }
    return 0;
}

int add_elem(struct set *s,
             const void *elem_adr, 
             enum status *status_adr)
{
    if (!s || !elem_adr) {
        if (status_adr) {
            *status_adr = INVALID_INPUT;
        }
        return 1;
    }
    if (exist_check(s, elem_adr)) {
        if (status_adr) {
            *status_adr = ELEM_EXISTS;
        }
        return 2;
    }
    if (s->nr_elem == s->max_capacity) {
        s->max_capacity *= 2;
        void *temp = realloc(s, s->max_capacity * s->sizeof_elem);
        if (!temp) {
            s->max_capacity /= 2;
            if (status_adr) {
                *status_adr = MEMORY_ERROR;
            }
            return -1;
        }
        s = temp;
    }
    char *new_elem_adr = (char *)s->arr + s->nr_elem * s->sizeof_elem;
    if (s->create_copy_elem(new_elem_adr, elem_adr) == -1) {
        if (status_adr) {
            *status_adr = MEMORY_ERROR;
        }
        return -1;
    }
    s->nr_elem++;
    if (status_adr) {
        *status_adr = OK;
    }
    return 0;
}

int print_set(const struct set *s, enum status *status_adr)
{
    if (!s) {
        if (status_adr) {
            *status_adr = INVALID_INPUT;
        }
        return 1;
    }
    for (size_t i = 0; i < s->nr_elem; ++i) {
        char *curr_elem_adr = (char *)s->arr + i * s->sizeof_elem;
        s->print_elem(curr_elem_adr);
    }
    if (status_adr) {
        *status_adr = OK;
    }
    return 0;
}

int destroy_set(struct set **s_adr, enum status *status_adr)
{
    if (!s_adr || !*s_adr) {
        if (status_adr) {
            *status_adr = INVALID_INPUT;
        }
        return 1;
    }
    for (size_t i = 0; i < (*s_adr)->nr_elem; ++i) {
        char *curr_elem_adr = (char *)(*s_adr)->arr + i * (*s_adr)->sizeof_elem;
        if (curr_elem_adr) {
            (*s_adr)->destroy_elem(curr_elem_adr);
        }
    }
    free((*s_adr)->arr);
    free(*s_adr);
    *s_adr = NULL;
    if (status_adr) {
        *status_adr = OK;
    }
    return 0;
}

int remove_elem(struct set *s, const void *elem_adr, enum status *status_adr)
{
    if (!s || !elem_adr) {
        if (status_adr) {
            *status_adr = INVALID_INPUT;
        }
        return 1;
    }
    for (size_t i = 0; i < s->nr_elem; ++i) {
        char *curr_elem_adr = (char *)s->arr + i * s->sizeof_elem;
        if (!s->comp_elem(curr_elem_adr, elem_adr)) {
            s->destroy_elem(curr_elem_adr);
            if (status_adr) {
                *status_adr = OK;
            }
            return 0;
        }
    }
    if (status_adr) {
        *status_adr = ELEM_DOES_NOT_EXIST;
    }
    return 3;
}

struct set *deep_copy_set(const struct set *s, enum status *status_adr)
{
    if (!s) {
        if (status_adr) {
            *status_adr = INVALID_INPUT;
        }
        return NULL;
    }
    struct set *copy = create_set(s->max_capacity, 
                                  s->sizeof_elem,
                                  s->comp_elem, 
                                  s->create_copy_elem, 
                                  s->print_elem, 
                                  s->destroy_elem,
                                  NULL);
    if (!copy) {
        if (status_adr) {
            *status_adr = MEMORY_ERROR;
        }
        return NULL;
    }
    for (size_t i = 0; i < s->nr_elem; ++i) {
        char *curr_elem_adr = (char *)copy->arr + i * copy->sizeof_elem;
        copy->create_copy_elem(curr_elem_adr, (char *)s->arr + i * s->sizeof_elem);
    }
    copy->nr_elem = s->nr_elem;
    if (status_adr) {
        *status_adr = OK;
    }
    return copy;
}

struct set *reunion_2set(const struct set *a,
                         const struct set *b,
                         enum status *status_adr)
{
    if (!a ||
        !b ||
        a->sizeof_elem != b->sizeof_elem ||
        a->create_copy_elem != b->create_copy_elem ||
        a->print_elem != b->print_elem ||
        a->destroy_elem != b->destroy_elem) {
        if (status_adr) {
            *status_adr = INVALID_INPUT;
        }
        return NULL;
    }
    struct set *s = create_set(a->max_capacity + b->max_capacity,
                               a->sizeof_elem,
                               a->comp_elem,
                               a->create_copy_elem,
                               a->print_elem,
                               a->destroy_elem,
                               status_adr);
    if (!s) {
        if (status_adr) {
            *status_adr = MEMORY_ERROR;
        }
        return NULL;
    }
    
    if (status_adr) {
        *status_adr = OK;
    }
    return s;
}
