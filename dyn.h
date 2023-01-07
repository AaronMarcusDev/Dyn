#ifndef dyn_h
#define dyn_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *array;
    size_t size;
    size_t capacity;
} dyn_int;

void dyn_int_init(dyn_int *array) {
    array->array = malloc(sizeof(int));
    array->size = 0;
    array->capacity = 1;
}

void dyn_int_free(dyn_int *array) {
    free(array->array);
    array->array = NULL;
    array->size = 0;
    array->capacity = 0;
}

int dyn_int_append(dyn_int *array, int value) {
    if (array->size == array->capacity) {
        size_t new_capacity = array->capacity * 2;
        int *new_array = malloc(new_capacity * sizeof(int));
        memcpy(new_array, array->array, array->size * sizeof(int));
        free(array->array);
        array->array = new_array;
        array->capacity = new_capacity;
    }

    array->array[array->size++] = value;
    return 0;
}

int dyn_int_insert(dyn_int *array, size_t index, int value) {
    if (index > array->size) {
        return 1;
    }

    if (array->size == array->capacity) {
        size_t new_capacity = array->capacity * 2;
        int *new_array = malloc(new_capacity * sizeof(int));
        memcpy(new_array, array->array, index * sizeof(int));
        memcpy(new_array + index + 1, array->array + index, (array->size - index) * sizeof(int));
        free(array->array);
        array->array = new_array;
        array->capacity = new_capacity;
    } else {
        memmove(array->array + index + 1, array->array + index, (array->size - index) * sizeof(int));
    }

    array->array[index] = value;
    array->size++;
    return 0;
}

int dyn_int_remove(dyn_int *array, size_t index) {
    if (index >= array->size) {
        return 1;
    }

    memmove(array->array + index, array->array + index + 1, (array->size - index - 1) * sizeof(int));
    array->size--;
    return 0;
}

int dyn_int_get(dyn_int *array, size_t index, int *value) {
    if (index >= array->size) {
        return 1;
    }

    *value = array->array[index];
    return 0;
}

int dyn_int_set(dyn_int *array, size_t index, int value) {
    if (index >= array->size) {
        return 1;
    }

    array->array[index] = value;
    return 0;
}

int dyn_int_size(dyn_int *array) {
    return array->size;
}

int dyn_int_capacity(dyn_int *array) {
    return array->capacity;
}

#endif /* dyn_h */