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
    int src_len = strlen(src_string);
    char *new_string = malloc((src_len + 1) * sizeof(char));
    if (!new_string) {
        return -1;
    }
    char *dest_string = *(char **)dest_string_adr;
    strcpy(dest_string, src_string);
    return 0;
}

void print_string(const void *string_adr)
{
    printf("%s\n", *(char **)string_adr);
}

int main(void)
{
    size_t capacity = 32;
    struct set *s = create_set(capacity, sizeof(char *), NULL, comp_string, create_copy_string, print_string);
    print_set(s, NULL);
    return 0;
}

