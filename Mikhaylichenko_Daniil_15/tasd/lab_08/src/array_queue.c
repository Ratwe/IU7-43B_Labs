#include "../inc/array_queue.h"

struct array_queue
{
    int *data;
    size_t size;
    size_t begin;
    size_t end;
    size_t max_size;
};

array_queue_t *new_array_queue(size_t init_size)
{
    array_queue_t *new_array_queue;
    int *data;

    new_array_queue = malloc(sizeof(array_queue_t));
    if (new_array_queue == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под структуру очереди в виде массивn");
        return NULL;
    }

    data = malloc(init_size * sizeof(int));
    if (data == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под массив целых чисел для очереди в виде массива");
        free(new_array_queue);
        return NULL;
    }

    new_array_queue->data = data;
    new_array_queue->size = 0;
    new_array_queue->begin = 0;
    new_array_queue->end = 0;
    new_array_queue->max_size = init_size;

    return new_array_queue;
}

void free_array_queue(array_queue_t *array_queue)
{
    free(array_queue->data);
    free(array_queue);
}

int array_queue_expand(array_queue_t *array_queue)
{
    int *expanded_data;

    expanded_data = realloc(array_queue->data, array_queue->max_size * sizeof(int) * QUEUE_EXPAND_FACTOR);
    if (expanded_data == NULL)
    {
        fputs("Ошибка выделения памяти под расширенную очередь в виде массива\n", stderr);
        return ALLOCATE_ERROR;
    }

    array_queue->data = expanded_data;
    array_queue->max_size = array_queue->size * QUEUE_EXPAND_FACTOR;

    if (array_queue->size > 0 && array_queue->begin >= array_queue->end)
    {
        memcpy(expanded_data + array_queue->size, expanded_data, array_queue->size * sizeof(int));
        array_queue->end = array_queue->begin + array_queue->size;
    }

    return EXIT_SUCCESS;
}

int array_queue_insert(array_queue_t *array_queue, int value, int index)
{
    int rc;
    size_t insertion_index;

    if (array_queue->size == array_queue->max_size)
    {
        rc = array_queue_expand(array_queue);
        if (rc != EXIT_SUCCESS)
            return rc;
    }

    index = MIN(index, array_queue->size);
    insertion_index = (array_queue->begin + index) % array_queue->max_size;

    if (array_queue->end < array_queue->begin)
    {
        if (insertion_index <= array_queue->end)
        {
            memmove(&array_queue->data[insertion_index + 1], &array_queue->data[insertion_index],
                    (array_queue->size - (array_queue->max_size - array_queue->begin) - insertion_index) * sizeof(int));
        }
        else
        {
            memmove(&array_queue->data[1], &array_queue->data[0], array_queue->end * sizeof(int));
            array_queue->data[0] = array_queue->data[array_queue->max_size - 1];
            memmove(&array_queue->data[insertion_index + 1], &array_queue->data[insertion_index], ((array_queue->max_size - 1) - insertion_index) * sizeof(int));
        }
    }
    else
    {
        memmove(&array_queue->data[insertion_index + 1], &array_queue->data[insertion_index], (array_queue->size - index) * sizeof(int));
    }

    array_queue->data[insertion_index] = value;
    array_queue->end = (array_queue->end + 1) % array_queue->max_size;
    array_queue->size++;

    return EXIT_SUCCESS;
}

int array_queue_push(array_queue_t *array_queue, int value)
{
    int rc;

    if (array_queue->size == array_queue->max_size)
    {
        rc = array_queue_expand(array_queue);
        if (rc != EXIT_SUCCESS)
            return rc;
    }

    array_queue->data[array_queue->end] = value;
    array_queue->end = (array_queue->end + 1) % array_queue->max_size;
    array_queue->size++;

    return EXIT_SUCCESS;
}

int array_queue_pop(array_queue_t *array_queue, int *value)
{
    if (array_queue->size == 0)
    {
        ERROR_LOG("Очередь в виде массива пуста");
        return ALLOCATE_ERROR;
    }

    *value = array_queue->data[array_queue->begin];
    array_queue->begin = (array_queue->begin + 1) % array_queue->max_size;

    array_queue->size--;

    return EXIT_SUCCESS;
}

size_t get_array_queue_size(array_queue_t *array_queue)
{
    return array_queue->size;
}

int array_queue_contains(array_queue_t *array_queue, int value)
{
    for (size_t i = 0; i < array_queue->size; i++)
        if (array_queue->data[(array_queue->begin + i) % array_queue->max_size] == value)
            return 1;
    return 0;
}

void array_queue_print(array_queue_t *array_queue)
{
    size_t index;

    if (array_queue->size == 0)
    {
        ERROR_LOG("Очередь в виде массива пуста");
        return;
    }

    ERROR_LOG("Очередь в виде массива, голова слева (1 - задача 1-го типа; 2 - задача 2-го типа):");
    for (size_t i = 0; i < array_queue->size; i++)
    {
        index = (array_queue->begin + i) % array_queue->max_size;
        printf("%d |%c", array_queue->data[index], i + 1 != array_queue->size ? ' ' : '\n');
    }
}

size_t get_array_queue_size_bytes(int elements_amount)
{
    return sizeof(array_queue_t) + elements_amount * sizeof(int);
}
