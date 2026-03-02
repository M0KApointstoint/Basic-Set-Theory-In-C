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
    printf("%s\n", *(char **)string_adr);
}

void destroy_string(void *target_string_adr)
{
    free(*(char **)target_string_adr);
}

int main(void)
{
    size_t capacity = 32;
    struct set *s = create_set(capacity, sizeof(char *), NULL, comp_string, create_copy_string, print_string, destroy_string);
    char *s1 = malloc(32);
    char *s2 = malloc(23);
    strcpy(s1, "salut");
    strcpy(s2, "ce faci!");
    add_elem(s, &s1, NULL);
    add_elem(s, &s2, NULL);
    add_elem(s, &s2, NULL);
    char *s3 = malloc(7);
    strcpy(s3, "mooe!");
    add_elem(s, &s3, NULL);
    free(s1);
    free(s2);
    free(s3);
    print_set(s, NULL);
    destroy_set(s, NULL);
    return 0;
}

