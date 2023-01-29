#include "../inc/hash.h"

static int hash_compares = 0;

void set_hash_compares(size_t compares)
{
    hash_compares = compares;
}

size_t get_hash_compares(void)
{
    return hash_compares;
}

//NOTE: Вспомогательный функции
size_t fget_len(char *fname)
{
    FILE *file = NULL;
    if ((file = fopen(fname, "r")) == NULL)
    {
        ERROR_LOG("Ошибка открытия файла");
        return FILE_OPEN_ERROR;
    }

    size_t len = 0;
    for (char str[MAX_STR_LEN + 2]; fgets(str, MAX_STR_LEN + 2, file) != NULL; len++);

    if (fclose(file) == EOF)
    {
        ERROR_LOG("Ошибка закрытия файла");
        return FILE_CLOSE_ERROR;
    }

    return len;
}

int get_prime(size_t num)
{
    int counter = 0;
    do
    {
        num++;

        counter = 0;
        for (int i = 2; i < num / 2; i++)
            if (num % i == 0)
                counter++;
    }
    while (counter != 0);

    return num;
}

//NOTE: открытая таблица
void free_htable_opened(htable_opened_t *htable)
{
    if (htable->size == 0)
        return;

    hash_node_t *cur, *del;
    for (size_t i = 0; i < htable->max_size; i++)
    {
        for (cur = htable->data[i]->next; cur != NULL; cur = cur->next)
        {
            del = cur;
            free(del);
        }
        free(htable->data[i]);
    }

    free(htable->data);
    free(htable->keys);
    free(htable);

    htable->size = 0;
}

htable_opened_t *new_hash_table_opened(size_t max_size)
{
    htable_opened_t *htable = malloc(sizeof(htable_opened_t));
    if (htable == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под открытую хэш-таблицу");
        return NULL;
    }

    max_size = get_prime(max_size);

    htable->data = malloc(max_size * sizeof(hash_node_t*));
    if (htable->data == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под записи");
        free_htable_opened(htable);
        return NULL;
    }

    htable->keys = malloc(max_size * sizeof(int));
    if (htable->keys == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под ключи");
        free_htable_opened(htable);
        return NULL;
    }

    hash_node_t *new_node;
    for (size_t i = 0; i < max_size; i++)
    {
        new_node = malloc(sizeof(hash_node_t));
        if (new_node == NULL)
        {
            ERROR_LOG("Ошибка выделения записи под отдельную запись");
            htable->max_size = i;
            free_htable_opened(htable);
            return NULL;
        }
        new_node->next = NULL;
        htable->data[i] = new_node;
        htable->keys[i] = NOT_EXIST;
    }

    htable->size = 0;
    htable->max_size = max_size;

    return htable;
}

size_t hash_opened_func(size_t max_size, char *str)
{
    size_t sum = 0;
    for (char *p = str; *p != '\0'; p++)
        sum += *p;

    return (sum % max_size);
}

int htable_opened_find_node(htable_opened_t *htable, char *str)
{
    size_t hash = hash_opened_func(htable->max_size, str);

    if (htable->keys[hash] == NOT_EXIST)
        return EXIT_FAILURE;

    for (hash_node_t *cur = htable->data[hash]; cur != NULL; cur = cur->next)
    {
        hash_compares++;
        if (!strcmp(cur->word, str))
            return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int htable_opened_insert(htable_opened_t *htable, char *str)
{
    size_t hash = hash_opened_func(htable->max_size, str);

    if (htable_opened_find_node(htable, str) == EXIT_SUCCESS)
    {
        ERROR_LOG("Элемент уже находится в открытой хэш-таблице");
        return WRONG_STR;
    }

    if (htable->keys[hash])
    {
        hash_node_t *new_node = malloc(sizeof(hash_node_t));
        if (new_node == NULL)
        {
            ERROR_LOG("Ошибка выделения памяти под узел");
            return ALLOCATE_ERROR;
        }
        strncpy(new_node->word, str, MAX_STR_LEN);
        new_node->next = NULL;

        hash_node_t *cur = htable->data[hash];
        for (; cur->next != NULL; cur = cur->next);
        cur->next = new_node;
    }
    else
    {
        strncpy(htable->data[hash]->word, str, MAX_STR_LEN);
        htable->keys[hash] = EXIST;
    }

    htable->size++;

    return EXIT_SUCCESS;
}

int fill_htable_opened(htable_opened_t *htable, FILE **file)
{
    int rc;

    fseek(*file, 0, SEEK_SET);

    for (char str[MAX_STR_LEN + 2]; fgets(str, MAX_STR_LEN + 2, *file) != NULL;)
    {
        if (strlen(str) > MAX_STR_LEN || str[0] == '\n')
        {
            ERROR_LOG("Введена недопустимая строка");
            return WRONG_STR;
        }
        char *new_str = strtok(str, "\n");
        rc = htable_opened_insert(htable, new_str);
        if (rc != EXIT_SUCCESS)
            return rc;
    }
    return EXIT_SUCCESS;
}

int htable_opened_pop(htable_opened_t *htable, char *str)
{
    size_t hash = hash_opened_func(htable->max_size, str);
    if (htable->keys[hash] == NOT_EXIST)
    {
        ERROR_LOG("Элемент не найден");
        return EXIT_FAILURE;
    }

    if (!strncmp(htable->data[hash]->word, str, MAX_STR_LEN))
    {
        if (htable->data[hash]->next == NULL)
            htable->keys[hash] = NOT_EXIST;
        else
        {
            hash_node_t *temp = htable->data[hash];
            htable->data[hash] = temp->next;
            free(temp);
        }

        htable->size--;

        return EXIT_SUCCESS;
    }

    for (hash_node_t *cur = htable->data[hash]->next, *prev = htable->data[hash];
            cur != NULL; prev = cur, cur = cur->next)
    {
        if (!strncmp(cur->word, str, MAX_STR_LEN))
        {
            prev->next = cur->next;
            free(cur);

            htable->size--;

            return EXIT_SUCCESS;
        }
    }

    ERROR_LOG("Нет элемента в открытой хэш-таблице");
    return EXIT_FAILURE;
}

void search_hash_opened_word(htable_opened_t *htable, char *str)
{
    int rc = htable_opened_find_node(htable, str);

    (rc == EXIT_FAILURE) ? FAILURE("    СЛОВО НЕ НАЙДЕНО") : SUCCESS("    СЛОВО НАЙДЕНО");
}


void print_htable_opened(htable_opened_t *htable)
{
    if (htable->size == 0)
    {
        ERROR_LOG("Открытая хэш-таблица пуста");
        return;
    }

    printf("\n\033[4mОткрытая хэш-таблица\033[0m\n");
    printf(" Ключ |    Значение\n");
    printf(" -----+------------\n");
    for (size_t i = 0; i < htable->max_size; i++)
    {
        if (htable->keys[i] == NOT_EXIST)
            continue;

        printf("%5zu |%12s -> ", i, htable->data[i]->word);
        for (hash_node_t *cur = htable->data[i]->next; cur != NULL; cur = cur->next)
            printf("%s -> ", cur->word);
        printf("∅\n");
    }
}

void print_htable_opened_color(htable_opened_t *htable, char *ch)
{
    if (htable->size == 0)
    {
        ERROR_LOG("Открытая хэш-таблица пуста");
        return;
    }

    printf("\n\033[4mОткрытая хэш-таблица\033[0m\n");
    printf(" Ключ |    Значение\n");
    printf(" -----+------------\n");
    for (size_t i = 0; i < htable->max_size; i++)
    {
        if (htable->keys[i] == NOT_EXIST)
            continue;

        printf("%5zu |%s%12s\033[0m -> ", i, COLOR_WORD(htable->data[i]->word, ch), htable->data[i]->word);
        for (hash_node_t *cur = htable->data[i]->next; cur != NULL; cur = cur->next)
            printf("%s%s\033[0m -> ", COLOR_WORD(cur->word, ch), cur->word);
        printf("∅\n");
    }
}

size_t get_htable_opened_size_in_bytes(htable_opened_t *htable)
{
    size_t size = sizeof(htable_opened_t);
    size += htable->max_size * sizeof(hash_node_t *);
    size += htable->max_size * sizeof(hash_node_t);

    for (size_t i = 0; i < htable->max_size; i++)
    {
        if (htable->keys[i] == NOT_EXIST)
            continue;

        for (hash_node_t *cur = htable->data[i]->next; cur != NULL; cur = cur->next)
            size += sizeof(hash_node_t);
    }

    size += htable->max_size * sizeof(int);

    return size;
}


//NOTE: закрытая хэш-таблица
void free_htable_closed(htable_closed_t *htable)
{
    if (htable->size == 0)
        return;

    for (size_t i = 0; i < htable->max_size; i++)
    {
        free(htable->data[i]);
        htable->keys[i] = EMPTY;
    }

    free(htable->data);
    free(htable->keys);
    free(htable);

    htable->size = 0;
}

size_t hash_closed_func(size_t max_size, char *str, size_t step, size_t iters)
{
    size_t sum = 0;
    for (char *p = str; *p != '\0'; p++)
        sum += *p;

    return (sum + step * iters) % max_size;
}

int htable_closed_find_node(htable_closed_t *htable, char *str)
{
    int step = htable->max_size / HASH_DIV;
    size_t hash, iters = 0;

    do
    {
        hash = hash_closed_func(htable->max_size, str, step, iters++);
        if (htable->keys[hash] == EMPTY)
            return EXIT_FAILURE;

        if (htable->keys[hash] == EXIST)
        {
            hash_compares++;
            if (!strncmp(htable->data[hash], str, MAX_STR_LEN))
                return EXIT_SUCCESS;
        }
    }
    while (iters < htable->max_size);

    return EXIT_FAILURE;
}

int htable_closed_insert(htable_closed_t *htable, char *str)
{
    int step = htable->max_size / HASH_DIV;

    if (htable_closed_find_node(htable, str) == EXIT_SUCCESS)
    {
        ERROR_LOG("Элемент уже находится в закрытой хеш-таблице");
        return WRONG_STR;
    }

    if (htable->size == htable->max_size)
    {
        ERROR_LOG("Закрытая хэш-таблица уже заполнена");
        return OVERFLOW;
    }

    size_t hash, iterations = 0;
    do
    {
        hash = hash_closed_func(htable->max_size, str, step, iterations++);
    }
    while (htable->keys[hash] == EXIST);

    strncpy(htable->data[hash], str, MAX_STR_LEN);
    htable->keys[hash] = EXIST;

    htable->size++;

    return EXIT_SUCCESS;
}

htable_closed_t *new_hash_table_closed(size_t max_size)
{
    htable_closed_t *htable = malloc(sizeof(htable_closed_t));
    if (htable == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под открытую хэш-таблицу");
        return NULL;
    }

    max_size = get_prime(max_size);

    htable->data = calloc(max_size, sizeof(char*));
    if (htable->data == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под массив строк");
        free_htable_closed(htable);
        return NULL;
    }
    for (size_t i = 0; i < max_size; i++)
    {
        htable->data[i] = malloc((MAX_STR_LEN + 1) * sizeof(char));
        if (htable->data[i] == NULL)
        {
            ERROR_LOG("Ошибка выделения памяти под строку в массиве");
            free_htable_closed(htable);
        }
    }

    htable->keys = malloc(max_size * sizeof(int));
    if (htable->keys == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под ключи");
        free_htable_closed(htable);
        return NULL;
    }

   for (size_t i = 0; i < max_size; i++)
       htable->keys[i] = EMPTY;

    htable->size = 0;
    htable->max_size = max_size;

    return htable;
}

int fill_htable_closed(htable_closed_t *htable, FILE **file)
{
    int rc;

    fseek(*file, 0, SEEK_SET);

    for (char str[MAX_STR_LEN + 2]; fgets(str, MAX_STR_LEN + 2, *file) != NULL;)
    {
        if (strlen(str) > MAX_STR_LEN || str[0] == '\n')
        {
            ERROR_LOG("Введена недопустимая строка");
            return WRONG_STR;
        }
        char *new_str = strtok(str, "\n");
        rc = htable_closed_insert(htable, new_str);
        if (rc != EXIT_SUCCESS)
            return rc;
    }
    return EXIT_SUCCESS;
}

int htable_closed_pop(htable_closed_t *htable, char *str)
{
    int step = htable->max_size / HASH_DIV;
    size_t hash, iters = 0;

    do
    {
        hash = hash_closed_func(htable->max_size, str, step, iters++);
        if (htable->keys[hash] == EMPTY)
            break;

        if (htable->keys[hash] == EXIST && !strncmp(htable->data[hash], str, MAX_STR_LEN))
        {
            htable->keys[hash] = DELETED;
            htable->size--;

            return EXIT_SUCCESS;
        }
    }
    while (iters < htable->max_size);

    ERROR_LOG("Нет элемента в закрытой хэш-таблице");
    return EXIT_FAILURE;
}

void search_hash_closed_word(htable_closed_t *htable, char *str)
{
    int rc = htable_closed_find_node(htable, str);

    (rc == EXIT_FAILURE) ? FAILURE("    СЛОВО НЕ НАЙДЕНО") : SUCCESS("    СЛОВО НАЙДЕНО");
}

void print_htable_closed(htable_closed_t *htable)
{
    if (htable->size == 0)
    {
        ERROR_LOG("Закрытая хэш-таюлица пуста");
        return;
    }

    int counter = 0;

    printf("\n\033[4mЗакрытая хэш-таблица\033[0m\n");
    printf(" Ключ |    Значение\n");
    printf(" -----+------------\n");
    for (size_t i = 0; i < htable->max_size; i++)
    {
        if (htable->keys[i] == DELETED)
            counter++;
        if (htable->keys[i] != EXIST)
            continue;
        printf("%5zu |%12s\n", i, htable->data[i]);
    }

    if (counter != 0)
    {
        printf("\nУдалённые:\n");
        printf(" Ключ |    Значение\n");
        printf(" -----+------------\n");
        for (size_t i = 0; i < htable->max_size; i++)
        {
            if (htable->keys[i] != DELETED)
                continue;
            printf("%5zu |%12s\n", i, htable->data[i]);
        }
    }
}

void print_htable_closed_color(htable_closed_t *htable, char *ch)
{
    if (htable->size == 0)
    {
        ERROR_LOG("Закрытая хэш-таюлица пуста");
        return;
    }

    int counter = 0;

    printf("\n\033[4mЗакрытая хэш-таблица\033[0m\n");
    printf(" Ключ |    Значение\n");
    printf(" -----+------------\n");
    for (size_t i = 0; i < htable->max_size; i++)
    {
        if (htable->keys[i] == DELETED)
            counter++;
        if (htable->keys[i] != EXIST)
            continue;
        printf("%5zu |%s%12s\033[0m\n", i, COLOR_WORD(htable->data[i], ch) , htable->data[i]);
    }

    if (counter != 0)
    {
        printf("\nУдалённые:\n");
        printf(" Ключ |    Значение\n");
        printf(" -----+------------\n");
        for (size_t i = 0; i < htable->max_size; i++)
        {
            if (htable->keys[i] != DELETED)
                continue;
            printf("%5zu |%s%12s\033[0m\n", i, COLOR_WORD(htable->data[i], ch), htable->data[i]);
        }
    }
}

size_t get_htable_closed_size_in_bytes(htable_closed_t *htable)
{
    size_t size = sizeof(htable_closed_t);
    size += htable->max_size * sizeof(char*);
    for (int i = 0; i < htable->max_size; i++)
    {
        size += (MAX_STR_LEN + 1) * sizeof(char);
    }
    size += htable->max_size * sizeof(int);
    return size;
}
