#include <stdio.h>
#include "sets.h"

int main(void)
{
    size_t capacity = 32;
    struct set *s = create_set(capacity, sizeof(char *), NULL);
    return 0;
}

