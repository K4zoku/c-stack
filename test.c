#define CSTACK_LOGARITHMIC_GROWTH
#include <stdio.h>
#include "cstack.h"

int main() {
    const char original[] = "abcdefgh";
    cstack_type(char) rev = cstack_new();
    size_t i;
    for (i = 0; original[i] != '\0'; ++i) {
        cstack_push(rev, original[i]);
    }

    while (!cstack_empty(rev)) {
        putchar(cstack_top(rev));
        cstack_pop(rev);
    }
    putchar('\n');
    cstack_free(rev);
    return 0;
}
