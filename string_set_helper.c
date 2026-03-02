#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (!dest_string_adr || !src_string_adr) {
        return 1;
    }
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
    }
}

void destroy_string(void *target_string_adr)
{
    if (*(char **)target_string_adr) {
        free(*(char **)target_string_adr);
        *(char **)target_string_adr = NULL;
    }
}
