#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#define DECLARE_STACK(T)\
\
typedef struct stack##T {\
    T *arr;\
    size_t size;\
    size_t capacity;\
} Stack_##T;\
\
static void stack_init_##T(Stack_##T *s, size_t init_capacity)\
{\
    size_t cap = 1;\
    while (cap < init_capacity)\
        cap *= 2;\
    s->capacity = cap;\
    s->size = 0;\
    s->arr = calloc(s->capacity, sizeof(T));\
    if (!s->arr) exit(1);\
}\
\
static bool stack_is_empty_##T(Stack_##T *s) { return s->size == 0; }\
\
static size_t stack_size_##T(Stack_##T *s) { return s->size; }\
\
static T stack_peek_##T(Stack_##T *s)\
{\
    if (s->size == 0)\
        exit(1);\
    return s->arr[s->size - 1];\
}\
\
static void stack_push_##T(Stack_##T *s, T ele)\
{\
    if (s->size >= s->capacity) {\
        s->capacity *= 2;\
        T *new_arr = realloc(s->arr, s->capacity * sizeof(T));\
        if (!new_arr) exit(1);\
        s->arr = new_arr;\
    }\
    s->arr[s->size++] = ele;\
}\
\
static T stack_pop_##T(Stack_##T *s)\
{\
    if (s->size == 0)\
        exit(1);\
    return s->arr[--s->size];\
}\
\
static void stack_clear_##T(Stack_##T *s)\
{\
    free(s->arr);\
    s->arr = NULL;\
    s->size = 0;\
    s->capacity = 0;\
}

#endif