#ifndef CSTACK_H_
#define CSTACK_H_

#include <assert.h>
#include <stdlib.h>

/**
 * @brief cstack_type - The stack type used in this library
 */
#define cstack_type(type) type *

/**
 * @brief cstack_new - construct new stack
 * @return new stack
 */
#define cstack_new() NULL

/**
 * @brief cstack_size - gets the current size of the stack
 * @param st - the stack
 * @return the size as a size_t
 */
#define cstack_size(st)                                                                                                \
    ((st) ? ((size_t *) (st))[-2] : (size_t) 0)

/**
 * @brief cstack_empty - returns non-zero if the stack is empty
 * @param st - the stack
 * @return non-zero if empty, zero if non-empty
 */
#define cstack_empty(st)                                                                                               \
  (cstack_size(st) == 0)

/**
 * @brief cstack_push - adds an element to the end of the stack
 * @param st - the stack
 * @param value - the value to add
 * @return void
 */
#define cstack_push(st, value)                                                                                         \
    do {                                                                                                               \
        const size_t st_cap = cstack_capacity(st);                                                                     \
        const size_t st_size = cstack_size(st);                                                                        \
        if (st_cap <= st_size) cstack_grow(st);                                                                        \
        st[st_size] = (value);                                                                                         \
        cstack_set_size((st), st_size + 1);                                                                            \
    } while (0)


/**
 * @brief cstack_top - get top element of the stack
 * @param st - the stack
 * @return top element
 */
#define cstack_top(st)                                                                                                 \
    (st)[cstack_size(st) - 1]

/**
 * @brief cstack_pop - remove top element of the stack
 * @param st - the stack
 * @return void
 */
#define cstack_pop(st)                                                                                                 \
    do {                                                                                                               \
        if (cstack_empty(st)) break;                                                                                   \
        cstack_set_size(st, cstack_size(st) - 1);                                                                      \
        cstack_shrink(st);                                                                                        \
    } while (0)

/**
 * @brief cstack_free - frees all memory associated with the stack
 * @param st - the stack
 * @return void
 */
#define cstack_free(st)                                                                                                \
    do {                                                                                                               \
        if (st) free(((size_t *) (st)) - 2);                                                                           \
    } while (0)

/**
 * @brief cstack_capacity - For internal use, gets the current capacity of the stack
 * @param st - the stack
 * @return the capacity as a size_t
 */
#define cstack_capacity(st)                                                                                            \
    ((st) ? ((size_t *) (st))[-1] : (size_t) 0)

/**
 * @brief cstack_set_capacity - For internal use, sets the capacity variable of the stack
 * @param st - the stack
 * @param size - the new capacity to set
 * @return void
 */
#define cstack_set_capacity(st, size)                                                                                  \
    do {                                                                                                               \
        if (st) ((size_t *) (st))[-1] = (size);                                                                        \
    } while (0)

/**
 * @brief cstack_set_size - For internal use, sets the size variable of the vector
 * @param vec - the vector
 * @param size - the new capacity to set
 * @return void
 */
#define cstack_set_size(st, size)                                                                                      \
    do {                                                                                                               \
        if (st) ((size_t *) (st))[-2] = (size);                                                                        \
    } while (0)

/**
 * @brief cstack_alloc - For internal use, allocate memory for <count> elements and 2 internal elements
 * @param st - the stack
 * @param count - the new capacity to set
 * @return void
 */
#define cstack_alloc(st, count)                                                                                        \
    do {                                                                                                               \
        size_t st_size = 2 * sizeof(size_t);                                                                           \
        if (count) st_size += (count) * sizeof(*(st));                                                                 \
        if (st) {                                                                                                      \
            size_t * st_ptr = ((size_t *) (st)) - 2;                                                                   \
            size_t * st_new_ptr = realloc(st_ptr, st_size);                                                            \
            assert(st_new_ptr);                                                                                        \
            (st) = (void *) (st_new_ptr + 2);                                                                          \
            cstack_set_capacity((st), (count));                                                                        \
        } else {                                                                                                       \
            size_t * st_ptr = malloc(st_size);                                                                         \
            assert(st_ptr);                                                                                            \
            (st) = (void *) (st_ptr + 2);                                                                              \
            cstack_set_capacity((st), (count));                                                                        \
            cstack_set_size((st), 0);                                                                                  \
        }                                                                                                              \
    } while (0)

#ifdef CSTACK_LOGARITHMIC_GROWTH

/**
 * @brief cstack_grow - For internal use, ensures that the stack is enough room for new element
 * @param st - the stack
 * @return void
 */
#define cstack_grow(st)                                                                                                \
    do {                                                                                                               \
        const size_t st_cap = cstack_capacity(st);                                                                     \
        cstack_alloc(st, st_cap ? st_cap << 1 : 1);                                                                    \
    } while (0)

/**
 * @brief cstack_shrink - For internal use, shrink capacity to fit size
 * @param st - the stack
 * @return void
 */
#define cstack_shrink(st)                                                                                              \
    do {                                                                                                               \
        const size_t st_cap = cstack_capacity(st);                                                                     \
        const size_t st_size = cstack_size(st);                                                                        \
        if (st_cap >= (st_size << 1)) cstack_alloc(st, st_size);                                                       \
    } while (0)

#else

/**
 * @brief cstack_grow - For internal use, ensures that the stack is enough room for new element
 * @param st - the stack
 * @return void
 */
#define cstack_grow(st) cstack_alloc(st, cstack_capacity(st) + 1)

/**
 * @brief cstack_shrink - For internal use, shrink capacity to fit size
 * @param st - the stack
 * @return void
 */
#define cstack_shrink(st) cstack_alloc(st, cstack_size(st))

#endif /* CSTACK_LOGARITHMIC_GROWTH */

#endif /* CSTACK_H_ */
