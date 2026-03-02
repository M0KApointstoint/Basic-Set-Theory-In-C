enum status {
    MEMORY_ERROR = -1,
    OK = 0,
    INVALID_INPUT = 1,
    ELEM_EXISTS = 2,
    ELEM_DOES_NOT_EXIST = 3,
};

struct set;

struct set *create_set(const size_t max_capacity,
                       const size_t sizeof_elem,
                       enum status *status_adr,
                       int (*comp_elem)(const void *, const void *),
                       int (*create_copy_elem)(void *, const void *),
                       void (*print_elem)(const void *),
                       void (*destroy_elem)(void *));

int add_elem(struct set *s,
             const void *elem_adr, 
             enum status *status_adr);

int print_set(const struct set *s, enum status *status_adr);

int destroy_set(struct set *s, enum status *status_adr);

int remove_elem(struct set *s, const void *elem_adr, enum status *status_adr);
