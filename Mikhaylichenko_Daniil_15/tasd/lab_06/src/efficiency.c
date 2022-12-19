#include "../inc/efficiency.h"
#include "../inc/tree.h"
#include "../inc/array.h"

void print_structs(size_t *tree_results, size_t *file_results, int index)
{
    printf("Двоичное дерево поиска:\t\t\t\033[33m%zu\033[0m\n", tree_results[index]);
    printf("Массив, полученный на основе файла:\033[33m\t%zu\033[0m\n", file_results[index]);
}

void print_results(results_t *results)
{
    printf("\n\n");
    char *file_names[] = { "Маленький файл", "Средний файл",
                           "Большой файл", "Отсортированный файл",
                           "Файл, отсортированный в обратном порядке" };

    printf("\033[43mСортировка (время в микросекундах)\033[0m\n");
    for (size_t i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
    {
        printf("\033[4m%s\033[0m\n", file_names[i]);
        print_structs(results->tree_sorting, results->file_sorting, i);
        printf("\n");
    }
    printf("\n");

    printf("\033[43mПоиск (количество сравнений)\033[0m\n");
    for (size_t i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
    {
        printf("\033[4m%s\033[0m\n", file_names[i]);
        print_structs(results->tree_searching, results->file_searching, i);
        printf("\n");
    }
    printf("\n");

    printf("\033[43mРазмеры\033[0m\n");
    printf("Размер узла дерева в байтах:\t\t\033[33m%lu\033[0m\n", sizeof(tree_node_t));
    printf("Размер структуры массива в байтах:\t\033[33m%lu\033[0m\n", sizeof(array_t));
    printf("Размер элемента массива в байтах:\t\033[33m%lu\033[0m\n", sizeof(char) * (MAX_STR_LEN + 1));
}

int qcmp(void const *a, void const *b)
{
    char const *aa = (char const *)a;
    char const *bb = (char const *)b;

    return strcmp(aa, bb);
}

void run_efficiency(void)
{
    clock_t start, end;
    tree_node_t *tree = NULL;
    tree_node_t *result_tree = NULL;
    results_t results = { 0 };
    array_t *array;

    char *file_names[] = { SMALL_FILE_NAME, MIDDLE_FILE_NAME,
                           BIG_FILE_NAME, SORTED_FILE_NAME,
                           REVERSE_SORTED_FILE_NAME };
    FILE *file;
    size_t len;
    size_t search_compares;
    char **sorted_array;
    int sort_index;

    char *words[ITERS] = { "pizza", "charge", "enjoy", "guess", "talk" };

    for (size_t name = 0; name < sizeof(file_names) / sizeof(file_names[0]); name++)
    {
        printf("Файл: \"%s\"\n", file_names[name]);
        file = fopen(file_names[name], "r");

        for (size_t i = 0; i < ITERS; i++)
        {
            //Замер времени для создания отсортированного массива
            start = clock();
            array = fill_array(file_names[name]);
            qsort(array->data, array->size, sizeof(char*), qcmp);
            end = clock();

            results.file_sorting[name] += (end - start) / (CLOCKS_PER_SEC / 1000000);
            fseek(file, 0, SEEK_SET);
            len = array->size;
            if (i == 0)
                printf("Элементов в файле: %lu\n", len);
            free_array(array->data, array->size);

            // Подсчёт количества сравнений при поиске элемента в массиве
            array = fill_array(file_names[name]);
            for (search_compares = 0; search_compares < array->size; search_compares++)
                if (!strcmp(array->data[search_compares], words[i]))
                    break;
            results.file_searching[name] += search_compares;
            fseek(file, 0, SEEK_SET);
            free_array(array->data, array->size);

            // Замер времени сортировки массива с помощью ДДП в мкс
            start = clock();
            sorted_array = malloc(len * sizeof(char*));
            sort_index = 0;
            fill_tree(&tree, &file);
            tree_sort(tree, sorted_array, &sort_index);
            end = clock();

            results.tree_sorting[name] += (end - start) / (CLOCKS_PER_SEC / 1000000);
            fseek(file, 0, SEEK_SET);
            free_array(sorted_array, len);

            // Подсчёт количества сравнений при поиске элемента в ДДП
            search_compares = 0;
            result_tree = tree;
            for (;result_tree != NULL;)
            {
                int compare = strcmp(words[i], result_tree->word);
                if (compare < 0)
                    result_tree = result_tree->left;
                else if (compare > 0)
                    result_tree = result_tree->right;
                else
                    break;
                search_compares++;
            }
            results.tree_searching[name] += search_compares;
            free_tree(&tree);
        }
        fclose(file);
    }

    // Нахождение среднего всех значений
    for (size_t i = 0; i < sizeof(file_names) / sizeof(file_names[0]); i++)
    {
       results.tree_sorting[i] /= ITERS;
       results.file_sorting[i] /= ITERS;
       results.tree_searching[i] /= ITERS;
       results.file_searching[i] /= ITERS;
    }

    ACTION_LOG("Вывод результатов...");
    print_results(&results);
}
