#include "../inc/list_graph.h"

void free_list_graph(list_graph_t *graph)
{
    if (graph == NULL || graph->size == 0)
        return;

    for (size_t i = 0; i < graph->size; i++)
    {
        for (node_t *cur = graph->nodes[i]; cur != NULL;)
        {
            node_t *del = cur;
            cur = cur->next;
            free(del);
        }
        graph->nodes[i] = NULL;
    }
    free(graph->nodes);
    graph->size = 0;
}

list_graph_t *new_list_graph(size_t size)
{
    list_graph_t *new_graph = malloc(sizeof(list_graph_t));
    if (new_graph == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под структуру графа в виде списка");
        return NULL;
    }

    new_graph->nodes = malloc(size * sizeof(node_t*));
    if (new_graph->nodes == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под массив указателей на вершины графа в виде списка");
        free(new_graph);
        return NULL;
    }

    new_graph->size = size;

    for (size_t i = 0; i < size; i++)
        new_graph->nodes[i] = NULL;

    return new_graph;
}

int scan_list_paths(list_graph_t **graph, FILE **file)
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

        if (len == 0)
            continue;

        if ((*graph)->nodes[from - 1] == NULL)
        {
            node_t *node_from = malloc(sizeof(node_t));
            if (node_from == NULL)
            {
                ERROR_LOG("Ошибка выделения памяти под новую вершину");
                return EXIT_FAILURE;
            }
            node_from->index = from;
            node_from->next = NULL;
            node_from->path_len = 0;
            (*graph)->nodes[from - 1] = node_from;
        }

        if ((*graph)->nodes[to - 1] == NULL)
        {
            node_t *head_node_to = malloc(sizeof(node_t));
            if (head_node_to == NULL)
            {
                ERROR_LOG("Ошибка выделения памяти под новую вершину");
                return EXIT_FAILURE;
            }
            head_node_to->index = to;
            head_node_to->next = NULL;
            (*graph)->nodes[to - 1] = head_node_to;
        }

        node_t *node_to = malloc(sizeof(node_t));
        if (node_to == NULL)
        {
            ERROR_LOG("Ошибка выделения памяти под новую вершину");
            return EXIT_FAILURE;
        }
        node_to->index = to;
        node_to->next = (*graph)->nodes[from - 1]->next;
        node_to->path_len = len;
        (*graph)->nodes[from - 1]->next = node_to;
    }

    return EXIT_SUCCESS;

}

int fill_list_graph(list_graph_t **graph, FILE **file)
{
    fseek(*file, 0, SEEK_SET);

    int size;
    if (fscanf(*file, "%d", &size) != 1 || size <= 0)
    {
        ERROR_LOG("Ошибка считывания количества вершин");
        return WRONG_DATA;
    }

    *graph = new_list_graph(size);
    if (graph == NULL)
        return EXIT_FAILURE;

    int rc = scan_list_paths(graph, file);
    if (rc != EXIT_SUCCESS)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;

}

void print_list(list_graph_t *graph)
{
    if (graph->size == 0)
    {
        ERROR_LOG("Матрица пуста");
        return;
    }

    for (size_t i = 0; i < graph->size; i++)
    {
        for (node_t *cur = graph->nodes[i]; cur != NULL; cur = cur->next)
        {
            if (cur->next != NULL)
                printf("%d -(%d)-> ", cur->index, cur->next->path_len);
            else
                printf("%d -> ", cur->index);
        }
        printf("∅\n");
    }
}

void write_list_graph(FILE **file, void *graph)
{
    list_graph_t *list_graph = (list_graph_t *) graph;

    for (size_t i = 0; i < list_graph->size; i++)
    {
        node_t *from = list_graph->nodes[i];

        if (from == NULL)
            continue;

        node_t *to = from->next;

        if (to == NULL)
            fprintf(*file, "%d;\n", from->index);

        for (; to != NULL; to = to->next)
            if (to->path_len != 0)
                fprintf(*file, "%d -> %d [label=%d];\n", from->index, to->index, to->path_len);
    }
}

void anti_dijkstra_list(list_graph_t *graph, int start_number)
{
    array_queue_t *array_queue;
    int number;
    int curr_number;
    int rc;
    node_t *cur;

    if (graph == NULL)
    {
        ERROR_LOG("Граф не существует");
        return;
    }

    if (start_number > graph->size || graph->nodes[start_number - 1] == NULL)
    {
        ERROR_LOG("В графе нет вершины с таким номером");
        return;
    }

    int *min_paths = malloc(graph->size * sizeof(int));
    if (min_paths == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под массив минимальных расстояний");
        return;
    }

    for (size_t i = 0; i < graph->size; i++)
        min_paths[i] = INT_MAX;
    min_paths[start_number - 1] = 0;

    array_queue = new_array_queue(INITIAL_QUEUE_SIZE);
    if (array_queue == NULL)
    {
        ERROR_LOG("Ошибка выделения памяти под очередь");
        free(min_paths);
        return;
    }

    number = start_number;

    do
    {
        cur = graph->nodes[number - 1];
        while (cur != NULL)
        {
            curr_number = cur->index;
            if (min_paths[curr_number - 1] == INT_MAX)// && cur->next != NULL)
            {
                min_paths[curr_number - 1] = min_paths[number - 1] + cur->path_len;
                rc = array_queue_push(array_queue, curr_number);
                if (rc != EXIT_SUCCESS)
                {
                    free(min_paths);
                    free_array_queue(array_queue);
                    return;
                }
            }
            cur = cur->next;
        }
        rc = array_queue_pop(array_queue, &number);
    }
    while (rc == EXIT_SUCCESS);

    free_array_queue(array_queue);

    printf("Пути от %d к остальным вершинам по порядку: ", start_number);
    for (int i = 0; i < graph->size; i++)
        printf("%d ", min_paths[i]);
    printf("\n");
}
