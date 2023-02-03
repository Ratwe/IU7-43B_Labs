#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "../inc/defines.h"

#define INITIAL_QUEUE_SIZE 100
#define QUEUE_EXPAND_FACTOR 2

typedef struct array_queue array_queue_t;

array_queue_t *new_array_queue(size_t init_size);
void free_array_queue(array_queue_t *array_queue);
int array_queue_expand(array_queue_t *array_queue);
int array_queue_insert(array_queue_t *array_queue, int value, int index);
int array_queue_push(array_queue_t *array_queue, int value);
int array_queue_pop(array_queue_t *array_queue, int *value);
size_t get_array_queue_size(array_queue_t *array_queue);
int array_queue_contains(array_queue_t *array_queue, int value);
void array_queue_print(array_queue_t *array_queue);
size_t get_array_queue_size_bytes(int elements_amount);

#endif  // __ARRAY_H__
