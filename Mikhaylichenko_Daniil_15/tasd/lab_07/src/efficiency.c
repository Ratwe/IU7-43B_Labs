#include "../inc/efficiency.h"

void print_time(results_t *results, int idx)
{
    printf("\t\tМассив на основе файла:\t\t\t\t\033[33m%.1lf\033[0m\n", (double)(results->file_searching[idx])/ITERS);
    printf("\t\tДДП:\t\t\t\t\t\t\033[33m%.1lf\033[0m\n", (double)(results->bst_searching[idx]) / ITERS);
    printf("\t\tАВЛ:\t\t\t\t\t\t\033[33m%.1lf\033[0m\n", (double)(results->avl_searching[idx]) / ITERS);
    printf("\t\tОткрытая хэш-таблица:\t\t\t\t\033[33m%.1lf\033[0m\n", (double)(results->htable_opened_searching[idx]) / ITERS);
    printf("\t\tЗакрытая хэш-таблица:\t\t\t\t\033[33m%.1lf\033[0m\n", (double)(results->htable_closed_searching[idx]) / ITERS);

    printf("\t\tОткрытая реструктуированная хэш-таблица:");
    if (results->htable_opened_restruct_size[idx] != 0)
        printf("\t\033[33m%.1lf\033[0m\n", (double)(results->htable_opened_restruct_searching[idx]) / ITERS);
    else
        printf("\t\033[33m%c\033[0m\n", '-');

    printf("\t\tЗакрытая реструктуированная хэш-таблица:");
    if (results->htable_closed_restruct_size[idx] != 0)
        printf("\t\033[33m%.1lf\033[0m\n", (double)(results->htable_closed_restruct_searching[idx]) / ITERS);
    else
        printf("\t\033[33m%c\033[0m\n", '-');
}

void print_compares(results_t *results, int idx)
{
    printf("\t\tМассив на основе файла:\t\t\t\t\033[33m%.1lf\033[0m\n", (double)(results->file_compares[idx])/ITERS);
    printf("\t\tДДП:\t\t\t\t\t\t\033[33m%.1lf\033[0m\n", (double)(results->bst_compares[idx]) / ITERS);
    printf("\t\tАВЛ:\t\t\t\t\t\t\033[33m%.1lf\033[0m\n", (double)(results->avl_compares[idx]) / ITERS);
    printf("\t\tОткрытая хэш-таблица:\t\t\t\t\033[33m%.1lf\033[0m\n", (double)(results->htable_opened_compares[idx]) / ITERS);
    printf("\t\tЗакрытая хэш-таблица:\t\t\t\t\033[33m%.1lf\033[0m\n", (double)(results->htable_closed_compares[idx]) / ITERS);

    printf("\t\tОткрытая реструктуированная хэш-таблица:");
    if (results->htable_opened_restruct_size[idx] != 0)
        printf("\t\033[33m%.1lf\033[0m\n", (double)(results->htable_opened_restruct_compares[idx]) / ITERS);
    else
        printf("\t\033[33m%c\033[0m\n", '-');

    printf("\t\tЗакрытая реструктуированная хэш-таблица:");
    if (results->htable_closed_restruct_size[idx] != 0)
        printf("\t\033[33m%.1lf\033[0m\n", (double)(results->htable_closed_restruct_compares[idx]) / ITERS);
    else
        printf("\t\033[33m%c\033[0m\n", '-');
}

void print_sizes(results_t *results, int idx)
{
    printf("\t\tМассив на основе файла:\t\t\t\t\033[33m%zu\033[0m\n", results->file_size[idx]);
    printf("\t\tДДП:\t\t\t\t\t\t\033[33m%zu\033[0m\n", results->bst_size[idx]);
    printf("\t\tАВЛ:\t\t\t\t\t\t\033[33m%zu\033[0m\n", results->avl_size[idx]);
    printf("\t\tОткрытая хэш-таблица:\t\t\t\t\033[33m%zu\033[0m\n", results->htable_opened_size[idx]);
    printf("\t\tЗакрытая хэш-таблица:\t\t\t\t\033[33m%zu\033[0m\n", results->htable_closed_size[idx]);

    printf("\t\tОткрытая реструктуированная хэш-таблица:");
    if (results->htable_opened_restruct_size[idx] != 0)
        printf("\t\033[33m%zu\033[0m\n", results->htable_opened_restruct_size[idx]);
    else
        printf("\t\033[33m%c\033[0m\n", '-');

    printf("\t\tЗакрытая реструктуированная хэш-таблица:");
    if (results->htable_closed_restruct_size[idx] != 0)
        printf("\t\033[33m%zu\033[0m\n", results->htable_closed_restruct_size[idx]);
    else
        printf("\t\033[33m%c\033[0m\n", '-');
}

void print_results(results_t *results)
{
    char *file_names[] = { "Маленький файл", "Средний файл",
                           "Большой файл", "Отсортированный файл",
                           "Файл, отсортированный в обратном порядке" };

    printf("\033[43mВремя поиск (мс)\033[0m\n");
    for (size_t i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
    {
        printf("\033[4m\t%s\033[0m\n", file_names[i]);
        print_time(results, i);
        printf("\n");
    }

    printf("\033[43mПоиск (количество сравнений)\033[0m\n");
    for (size_t i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
    {
        printf("\033[4m\t%s\033[0m\n", file_names[i]);
        print_compares(results, i);
        printf("\n");
    }

    printf("\033[43mРазмер структур (в байтах)\033[0m\n");
    for (size_t i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
    {
        printf("\033[4m\t%s\033[0m\n", file_names[i]);
        print_sizes(results, i);
        printf("\n");
    }
}

void run_efficiency(void)
{
    clock_t start, end;
    tree_node_t *bst = NULL;
    tree_node_t *avl = NULL;
    htable_opened_t *htable_opened;
    htable_closed_t *htable_closed;
    results_t results = { 0 };
    array_t *array;

    char *file_names[] = { SMALL_FILE_NAME, MIDDLE_FILE_NAME,
                           BIG_FILE_NAME, SORTED_FILE_NAME,
                           REVERSE_SORTED_FILE_NAME };
    FILE *file;
    int counter = 0;

    double max_compares;
    printf("Введите максимальное среднее количество сравнений (%.0lf - %.0lf): ", MIN_COMPARES, MAX_COMPARES);
    if (scanf("%lf", &max_compares) != 1 || max_compares < MIN_COMPARES || max_compares > MAX_COMPARES)
    {
        ERROR_LOG("Ошибка ввода");
        return;
    }


    // Создание букв при поиске слов
    array_t *words = fill_array(WORDS_FILE);

    for (size_t name = 0; name < sizeof(file_names) / sizeof(file_names[0]); name++)
    {
        printf("Файл: \"%s\"\n", file_names[name]);
        file = fopen(file_names[name], "r");

        for (size_t i = 0; i < ITERS; i++)
        {
            fseek(file, 0, SEEK_SET);

            // Замеры в массиве
            array = fill_array(file_names[name]);
            size_t number_of_elems = array->size;
            counter = 0;
            start = clock();
            for (size_t j = 0; j < array->size; j++)
            {
                counter++;
                if (!strncmp(array->data[j], words->data[i], 1))
                    break;
            }
            end = clock();
            results.file_searching[name] += GET_TIME(start, end);
            results.file_compares[name] += counter;
            if (i == 0)
                results.file_size[name] = get_arr_size_in_bytes(array);

            fseek(file, 0, SEEK_SET);
            free_array(array->data, array->size);

            // Замеры в ДДП
            fill_bst(&bst, &file);
            set_tree_compares(0);
            start = clock();
            find_node(bst, words->data[i]);
            end = clock();
            results.bst_searching[name] += GET_TIME(start, end);
            results.bst_compares[name] += get_tree_compares();
            if (i == 0)
                results.bst_size[name] = get_tree_size_in_bytes(bst);

            fseek(file, 0, SEEK_SET);
            free_tree(&bst);

            // Замеры в АВЛ
            fill_avl(&avl, &file);
            set_tree_compares(0);
            start = clock();
            find_node(avl, words->data[i]);
            end = clock();
            results.avl_searching[name] += GET_TIME(start, end);
            results.avl_compares[name] += get_tree_compares();
            if (i == 0)
                results.avl_size[name] = get_tree_size_in_bytes(avl);

            fseek(file, 0, SEEK_SET);
            free_tree(&avl);

            // Замеры в открытой хэш-таблице
            htable_opened = new_hash_table_opened(number_of_elems * OPENED_COEF);
            fill_htable_opened(htable_opened, &file);
            set_hash_compares(0);
            start = clock();
            htable_opened_find_node(htable_opened, words->data[i]);
            end = clock();
            results.htable_opened_searching[name] += GET_TIME(start, end);
            results.htable_opened_compares[name] += get_hash_compares();
            if (i == 0)
                results.htable_opened_size[name] = get_htable_opened_size_in_bytes(htable_opened);

            fseek(file, 0, SEEK_SET);
            free_htable_opened(htable_opened);


            // Замеры закрытой хэш-таблице
            htable_closed = new_hash_table_closed(number_of_elems * CLOSED_COEF);
            fill_htable_closed(htable_closed, &file);
            set_hash_compares(0);
            start = clock();
            htable_closed_find_node(htable_closed, words->data[i]);
            end = clock();
            results.htable_closed_searching[name] += GET_TIME(start, end);
            results.htable_closed_compares[name] += get_hash_compares();
            if (i == 0)
                results.htable_closed_size[name] = get_htable_closed_size_in_bytes(htable_closed);

            fseek(file, 0, SEEK_SET);
            free_htable_closed(htable_closed);
        }
        fclose(file);
    }

    for (size_t name = 0; name < sizeof(file_names) / sizeof(file_names[0]); name++)
    {
        file = fopen(file_names[name], "r");

        for (size_t i = 0; i < ITERS; i++)
        {
            fseek(file, 0, SEEK_SET);

            array = fill_array(file_names[name]);
            size_t number_of_elems = array->size;
            free_array(array->data, array->size);

            fseek(file, 0, SEEK_SET);

            double average_compares = ((double)results.htable_opened_compares[name]) / ITERS;
            // Замеры в открытой реструктуризированной хэш-таблице
            if (average_compares > max_compares)
            {
                htable_opened = new_hash_table_opened(number_of_elems * OPENED_COEF * RESTRUCT);
                fill_htable_opened(htable_opened, &file);
                set_hash_compares(0);
                start = clock();
                htable_opened_find_node(htable_opened, words->data[i]);
                end = clock();
                results.htable_opened_restruct_searching[name] += GET_TIME(start, end);
                results.htable_opened_restruct_compares[name] += get_hash_compares();
                if (i == 0)
                    results.htable_opened_restruct_size[name] = get_htable_opened_size_in_bytes(htable_opened);

                fseek(file, 0, SEEK_SET);
                free_htable_opened(htable_opened);
            }

            average_compares = ((double)results.htable_closed_compares[name]) / ITERS;
            // Замеры в закрытой реструктуризированной хэш-таблице
            if (average_compares > max_compares)
            {
                htable_closed = new_hash_table_closed(number_of_elems * CLOSED_COEF * RESTRUCT);
                counter = fill_htable_closed(htable_closed, &file);
                set_hash_compares(0);
                start = clock();
                htable_closed_find_node(htable_closed, words->data[i]);
                end = clock();
                results.htable_closed_restruct_searching[name] += GET_TIME(start, end);
                results.htable_closed_restruct_compares[name] += get_hash_compares();
                if (i == 0)
                    results.htable_closed_restruct_size[name] = get_htable_closed_size_in_bytes(htable_closed);

                fseek(file, 0, SEEK_SET);
                free_htable_closed(htable_closed);
            }
        }
        fclose(file);
    }

    free_array(words->data, words->size);

    ACTION_LOG("Вывод результатов...");
    print_results(&results);
}
