#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sets.h"

int comp_string(const void *a, const void *b)
{
    char *string_a = *(char **)a;
    char *string_b = *(char **)b;
    int comp = strcmp(string_a, string_b);
    if (!comp) {
        return 0;
    }
    return 1;
}

int create_copy_string(void *dest_string_adr, const void *src_string_adr)
{
    char *src_string = *(char **)src_string_adr;
    size_t src_len = strlen(src_string);
    char *dest_string = malloc((src_len + 1) * sizeof(char));
    if (!dest_string) {
        return -1;
    }
    *(char **)dest_string_adr = dest_string;
    strcpy(dest_string, src_string);
    return 0;
}

void print_string(const void *string_adr)
{
    if (*(char **)string_adr) {
        printf("%s\n", *(char **)string_adr);
    } else {
        printf("\n");
    }
}

void destroy_string(void *target_string_adr)
{
    if (*(char **)target_string_adr) {
        free(*(char **)target_string_adr);
    }
}

int main(void)
{
    size_t capacity = 32;
    struct set *s = create_set(capacity, 
                               sizeof(char *),
                               NULL, 
                               comp_string, 
                               create_copy_string, 
                               print_string, 
                               destroy_string);
    size_t string_size = 32;
    char *s1 = malloc(string_size);
    char *s2 = malloc(string_size);
    char *s3 = malloc(string_size);
    strcpy(s1, "Hello, there!");
    strcpy(s2, "General Kenobi!");
    strcpy(s3, "I love CDL!");
    add_elem(s, &s1, NULL);
    add_elem(s, &s2, NULL);
    add_elem(s, &s2, NULL); // Checking duplicates.
    add_elem(s, &s3, NULL);
    free(s1);
    free(s2); // Deep copy was made.
    free(s3);
    print_set(s, NULL);
    destroy_set(s, NULL);
    return 0;
}
