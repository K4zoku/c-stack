#define CSTACK_LOGARITHMIC_GROWTH
#include <stdio.h>
#include "cstack.h"

int main(int argc, char ** argv) {
    (void) argc;
    (void) argv;
    const char str[] = "abcdefgh";
    cstack_type(char) rev = cstack_new();
    size_t i;
    for (i = 0; str[i] != '\0'; ++i) {
        cstack_push(rev, str[i]);
    }

    printf("size: %u\n", cstack_size(rev));

    while (!cstack_empty(rev)) {
        putchar(cstack_top(rev));
        cstack_pop(rev);
    }
    putchar('\n');

    cstack_free(rev);
    return 0;
}
