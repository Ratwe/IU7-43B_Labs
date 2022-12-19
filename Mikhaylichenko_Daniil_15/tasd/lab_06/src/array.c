#include "../inc/array.h"

size_t get_file_len(FILE **file)
{
    fseek(*file, 0, SEEK_SET);
    size_t counter = 0;
    for(char str[MAX_STR_LEN + 2]; fgets(str, MAX_STR_LEN + 2, *file) != NULL;)
        counter++;
    return counter;
}

void free_array(char **data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        free(data[i]);
    free(data);
}

array_t *new_array(size_t size)
{
    array_t *new_array = malloc(sizeof(array_t));
    if (new_array == NULL)
        return NULL;

    new_array->data = malloc(size * sizeof(char*));
    new_array->size = 0;
    new_array->max_size = size;

    return new_array;
}

array_t *fill_array(char *file_name)
{
    FILE *file = NULL;
    if ((file = fopen(file_name, "r")) == NULL)
    {
        ERROR_LOG("Ошибка открытия файла");
        return NULL;
    }

    size_t arr_size = get_file_len(&file);
    array_t *array = new_array(arr_size);
    if (array == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под массив");
        return NULL;
    }

    fseek(file, 0, SEEK_SET);

    for(char str[MAX_STR_LEN + 2]; fgets(str, MAX_STR_LEN + 2, file) != NULL;)
    {
        array->data[array->size] = malloc(sizeof(char) * (MAX_STR_LEN + 1));
        char *new_str = strtok(str, "\n");
        strcpy(array->data[array->size++], new_str);
    }

    fclose(file);

    return array;
}
