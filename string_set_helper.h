#ifndef STRING_SET_HELPER_H
#define STRING_SET_HELPER_H

int comp_string(const void *a, const void *b);

int create_copy_string(void *dest_string_adr, const void *src_string_adr);

void print_string(const void *string_adr);

void destroy_string(void *target_string_adr);

#endif
