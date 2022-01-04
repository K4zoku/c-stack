#ifndef CSTACK_H_
#define CSTACK_H_

#include <assert.h>
#include <stdlib.h>

/**
 * @brief The stack type used in this library.
 */
#define cstack_type(type) type *

/**
 * @brief Construct new stack.
 * @return stack
 */
#define cstack_new() NULL

/**
 * @brief Test whether container is empty.
 * @param st - The stack
 * @return int - 1 if empty, otherwise 0
 */
#define cstack_empty(st)                                                       \
  (cstack_size(st) == 0)

/**
 * @brief Return size.
 * @param st - The stack
 * @return size_t - Return size of the stack
 */
#define cstack_size(st)                                                        \
    ((st) ? ((size_t *) (st))[-2] : (size_t) 0)

/**
 * @brief Access next element.
 * @param st - The stack
 * @return type - Returns a reference to the top element in the stack
 */
#define cstack_top(st)                                                         \
    (st)[cstack_size(st) - 1]

/**
 * @brief Insert element.
 * @param st - The stack
 * @param value - Value to which the inserted element is initialized.
 * @return void
 */
#define cstack_push(st, value)                                                 \
    do {                                                                       \
        const size_t st_cap = cstack_capacity(st);                             \
        const size_t st_size = cstack_size(st);                                \
        if (st_cap <= st_size) {                                               \
            cstack_grow(st);                                                   \
        }                                                                      \
        st[st_size] = (value);                                                 \
        cstack_set_size((st), st_size + 1);                                    \
    } while (0)

/**
 * @brief Remove top element.
 * @param st - The stack
 * @return void
 */
#define cstack_pop(st)                                                         \
    do {                                                                       \
        if (cstack_empty(st)) {                                                \
            break;                                                             \
        }                                                                      \
        cstack_set_size(st, cstack_size(st) - 1);                              \
        cstack_shrink(st);                                                     \
    } while (0)

/**
 * @brief Frees all memory associated with the stack.
 * @param st - The stack
 * @return void
 */
#define cstack_free(st)                                                        \
    do {                                                                       \
        if (st) {                                                              \
            free(((size_t *) (st)) - 2);                                       \
        }                                                                      \
    } while (0)

/**
 * @brief For internal use, sets the size variable of the stack.
 * @param st - The stack
 * @param size - The new capacity to set
 * @return void
 */
#define cstack_set_size(st, size)                                              \
    do {                                                                       \
        if (st) {                                                              \
            ((size_t *) (st))[-2] = (size);                                    \
        }                                                                      \
    } while (0)

/**
 * @brief For internal use, gets the current capacity of the stack.
 * @param st - The stack
 * @return size_t - The capacity
 */
#define cstack_capacity(st)                                                    \
    ((st) ? ((size_t *) (st))[-1] : (size_t) 0)

/**
 * @brief For internal use, sets the capacity variable of the stack.
 * @param st - The stack
 * @param size - The new capacity to set
 * @return void
 */
#define cstack_set_capacity(st, size)                                          \
    do {                                                                       \
        if (st) {                                                              \
            ((size_t *) (st))[-1] = (size);                                    \
        }                                                                      \
    } while (0)

#ifdef CSTACK_LOGARITHMIC_GROWTH

/**
 * @brief For internal use, ensures that the stack is enough room for new
 * element.
 * @param st - The stack
 * @return void
 */
#define cstack_grow(st)                                                        \
    do {                                                                       \
        const size_t st_cap = cstack_capacity(st);                             \
        cstack_alloc(st, st_cap ? st_cap << 1 : 1);                            \
    } while (0)

/**
 * @brief For internal use, shrink capacity to fit its size.
 * @param st - The stack
 * @return void
 */
#define cstack_shrink(st)                                                      \
    do {                                                                       \
        const size_t st_cap = cstack_capacity(st);                             \
        const size_t st_size = cstack_size(st);                                \
        if (st_cap >= (st_size << 1)) {                                        \
            cstack_alloc(st, st_size);                                         \
        }                                                                      \
    } while (0)

#else

/**
 * @brief For internal use, ensures that the stack is enough room for new
 * element.
 * @param st - The stack
 * @return void
 */
#define cstack_grow(st)                                                        \
    do {                                                                       \
        cstack_alloc(st, cstack_capacity(st) + 1)                              \
    } while (0)

/**
 * @brief For internal use, shrink capacity to fit its size.
 * @param st - The stack
 * @return void
 */
#define cstack_shrink(st)                                                      \
    do {                                                                       \
        cstack_alloc(st, cstack_size(st))                                      \
    } while (0)

#endif /* CSTACK_LOGARITHMIC_GROWTH */

/**
 * @brief For internal use, allocate memory for 2 internal elements and <count> elements.
 * @param st - The stack
 * @param count - The number of elements that need to be allocated
 * @return void
 */
#define cstack_alloc(st, count)                                                \
    do {                                                                       \
        size_t st_size = 2 * sizeof(size_t);                                   \
        if (count) {                                                           \
            st_size += (count) * sizeof(*(st));                                \
        }                                                                      \
        if (st) {                                                              \
            size_t * st_ptr = ((size_t *) (st)) - 2;                           \
            size_t * st_new_ptr = realloc(st_ptr, st_size);                    \
            assert(st_new_ptr);                                                \
            (st) = (void *) (st_new_ptr + 2);                                  \
            cstack_set_capacity((st), (count));                                \
        } else {                                                               \
            size_t * st_ptr = malloc(st_size);                                 \
            assert(st_ptr);                                                    \
            (st) = (void *) (st_ptr + 2);                                      \
            cstack_set_capacity((st), (count));                                \
            cstack_set_size((st), 0);                                          \
        }                                                                      \
    } while (0)

#endif /* CSTACK_H_ */
