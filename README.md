<h1 align="center"><code>c-stack</code></h1>
<p align="center">
    <img alt="Workflow Status" src="https://img.shields.io/github/workflow/status/K4zoku/c-stack/Make?style=for-the-badge">
    <a href="https://github.com/K4zoku/c-stack/blob/master/LICENSE">
        <img alt="License" src="https://img.shields.io/github/license/K4zoku/c-stack?style=for-the-badge">
    </a>
</p>

## 💡 About

This is an implementation of a std::stack, but in plain C89 code.

This repo is inspired by [c-vector](https://github.com/eteran/c-vector)

### Memory structure

```
┏━━━━━━┳━━━━━━━━━━┳━━━━━━━━━┓
┃ size ┃ capacity ┃ data... ┃
┗━━━━━━┻━━━━━━━━━━┻━━━━━━━━━┛
                  ↑ user's pointer
```

## 📜 Example usage

```c
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

    printf("size: %lu\n", cstack_size(rev));

    while (!cstack_empty(rev)) {
        putchar(cstack_top(rev));
        cstack_pop(rev);
    }
    putchar('\n');

    cstack_free(rev);
    return 0;
}
```

<br>

---

<p align="center">Made with ❤️ by <a href="https://github.com/K4zoku"><i>@K4zoku</i></a></p>
