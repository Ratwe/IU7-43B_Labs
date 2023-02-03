#include "../inc/matrix_graph.h"

void free_matrix_graph(matrix_graph_t *graph)
{
    if (graph == NULL || graph->size == 0)
        return;

    for (size_t i = 0; i < graph->size; i++)
        free(graph->data[i]);

    free(graph->data);
    graph->size = 0;
}

matrix_graph_t *new_matrix_graph(size_t size)
{
    matrix_graph_t *new_graph = malloc(sizeof(matrix_graph_t));
    if (new_graph == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под структура графа");
        return NULL;
    }

    new_graph->data = malloc(size * sizeof(int*));
    if (new_graph->data == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под массив указателей");
        free(new_graph);
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        new_graph->data[i] = calloc(size, sizeof(int));
        if (new_graph->data[i] == NULL)
        {
            ERROR_LOG("Ошибка выделения памяти под столбец");
            free_matrix_graph(new_graph);
            return NULL;
        }
    }

    new_graph->size = size;

    return new_graph;
}

int scan_matrix_paths(matrix_graph_t **graph, FILE **file)
{
    for (int from, to, len, i = 0; i < (*graph)->size * (*graph)->size; i++)
    {
        if (fscanf(*file, "%d%d%d", &from, &to, &len) != 3)
        {
            ERROR_LOG("Ошибка в данных");
            return WRONG_DATA;
        }

        if (from <= 0 || from > (*graph)->size)
        {
            ERROR_LOG("Ошибка в индексе начальной вершины");
            return WRONG_DATA;
        }

        if (to <= 0 || to > (*graph)->size)
        {
            ERROR_LOG("Ошибка в индексе начальной вершины");
            return WRONG_DATA;
        }

        if (len < 0)
        {
            ERROR_LOG("Длина пути должна быть положительным числом");
            return WRONG_DATA;
        }

        if ((*graph)->data[from - 1][to - 1] == 0)
            (*graph)->data[from - 1][to - 1] = len;
        else
        {
            ERROR_LOG("Произошла перезапись пути");
            return WRONG_DATA;
        }
    }

    return EXIT_SUCCESS;
}

int fill_matrix_graph(matrix_graph_t **graph, FILE **file)
{
    fseek(*file, 0, SEEK_SET);

    int size;
    if (fscanf(*file, "%d", &size) != 1 || size <= 0)
    {
        ERROR_LOG("Ошибка считывания количества вершин");
        return WRONG_DATA;
    }

    *graph = new_matrix_graph(size);
    if (graph == NULL)
        return EXIT_FAILURE;

    int rc = scan_matrix_paths(graph, file);
    if (rc != EXIT_SUCCESS)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void print_matrix(matrix_graph_t *graph)
{
    if (graph->size == 0)
    {
        ERROR_LOG("Матрица пуста");
        return;
    }

    printf("\n    ");
    for (size_t i = 0; i < graph->size; i++)
        printf("(%3zu) ", i + 1);
    printf("\n");

    for (size_t i = 0; i < graph->size; i++)
    {
        for (size_t j = 0; j < graph->size; j++)
        {
            if (j == 0)
                printf("(%2zu) ", i + 1);

            printf("%3d   ", graph->data[i][j]);
        }
        printf("\n");
    }
}

void write_matrix_graph(FILE **file, void *graph)
{
    matrix_graph_t *matrix_graph = (matrix_graph_t *) graph;

    for (size_t i = 0; i < matrix_graph->size; i++)
        for (size_t j = 0; j < matrix_graph->size; j++)
            if (matrix_graph->data[i][j] != 0)
                fprintf(*file, "%zu -> %zu [label=%d]\n", i + 1, j + 1, matrix_graph->data[i][j]);
}

void null_str(char *str)
{
    size_t str_len = strlen(str);
    for (size_t i = 0; i < str_len; i++)
        str[i] = '\0';
}

void anti_dijkstra_matrix(matrix_graph_t *graph, int start_index)
{
    if (graph == NULL || graph->size == 0)
    {
        ERROR_LOG("Пустой граф");
        return;
    }

    char path[PATH_STR_LEN + 1] = { 0 };
    char node_path[MAX_STR_LEN + 1];
    bool *visited = malloc(sizeof(bool) * graph->size);
    int *distances = malloc(sizeof(int) * graph->size);
    int maxWeight, maxIndex;

    for (int i = 0; i < graph->size; i++)
    {
        visited[i] = false;
        distances[i] = INT_MIN;
    }

    distances[start_index] = 0;

    do
    {
        maxIndex = INT_MIN;
        maxWeight = INT_MIN;

        for (int i = 0; i < graph->size; i++)
        {
            if (!visited[i] && distances[i] > maxWeight)
            {
                maxIndex = i;
                maxWeight = distances[i];
            }
        }

        if (maxIndex != INT_MIN)
        {
            for (int i = 0; i < graph->size; i++)
                if (graph->data[maxIndex][i])
                {
                    int temp = maxWeight + graph->data[maxIndex][i];
                    if (temp > distances[i])
                        distances[i] = temp;
                }

            visited[maxIndex] = true;
        }
    }
    while (maxIndex > INT_MIN);

    for (int i = 0; i < graph->size; i++)
    {
        null_str(path);
        if (distances[i] != INT_MIN)
        {
            printf("Вес: %d ~> %d = %d \t", start_index + 1, i + 1, distances[i]);

            int end = i;
            int weight = distances[end];

            null_str(node_path);
            sprintf(node_path, "%d >~ ", end + 1);
            strcat(path, node_path);

            while (end != start_index)
            {
                int j = 0;
                for (; j < graph->size; j++)
                {
                    if (graph->data[j][end])
                    {
                        int temp = weight - graph->data[j][end];
                        if (temp == distances[j])
                        {
                            end = j;
                            weight = temp;
                            null_str(node_path);
                            sprintf(node_path, "%d >~ ", j + 1);
                            strcat(path, node_path);
                        }
                    }
                }
            }
            printf("Путь: ");
            for (int j = strlen(path) - 5; j >= 0; j--)
                printf("%c", path[j]);
            printf("\n");
        }
        else
            printf("Вес: %d ~ %d = нет маршрута\n", start_index + 1, i + 1);
    }
}

