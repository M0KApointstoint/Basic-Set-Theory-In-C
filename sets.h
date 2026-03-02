enum status {
    MEMORY_ERROR = -1,
    OK = 0,
};

struct set;

struct set *create_set(const size_t max_capacity,
                       const size_t sizeof_elem,
                       enum status *status_adr);
