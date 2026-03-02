// Example of main.c file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sets.h"
#include "string_set_helper.h"

int main(void)
{
    size_t capacity = 32;
    struct set *s = create_set(capacity, 
                               sizeof(char *),
                               comp_string, 
                               create_copy_string, 
                               print_string, 
                               destroy_string,
                               NULL);
    size_t string_size = 32;
    char *s1 = malloc(string_size);
    char *s2 = malloc(string_size);
    char *s3 = malloc(string_size);
    strcpy(s1, "Hello, there!");
    strcpy(s2, "General Kenobi!");
    strcpy(s3, "I love CDL!");

    add_elem(s, &s1, NULL);
    add_elem(s, &s2, NULL);
    
    struct set *t = create_set(capacity,
                               sizeof(char *),
                               comp_string,
                               create_copy_string,
                               print_string,
                               destroy_string,
                               NULL);

    add_elem(t, &s3, NULL);
    add_elem(t, &s1, NULL);

    struct set *intersectie = intersection_2set(s, t, NULL);
    print_set(intersectie, NULL);

    free(s1);
    free(s2);
    free(s3);

    destroy_set(&s, NULL);
    destroy_set(&t, NULL);
    destroy_set(&intersectie, NULL);
    return 0;
}
