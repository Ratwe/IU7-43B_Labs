#include "../inc/graphs.h"

int graph_to_dot(void *graph, char *dot_name, void (*write_paths)(FILE **file, void *graph))
{
    if (graph == NULL)
    {
        ERROR_LOG("Пустой граф");
        return EMPTY_TREE;
    }

    FILE *dot_file = NULL;
    if ((dot_file = fopen(dot_name, "w")) == NULL)
    {
        ERROR_LOG("Ошибка открытия файла");
        return FILE_OPEN_ERROR;
    }

    fprintf(dot_file, "digraph tree {\n");

    write_paths(&dot_file, graph);

    fprintf(dot_file, "}\n");

    if (fclose(dot_file) == EOF)
    {
        ERROR_LOG("Ошибка закрытия файла");
        return FILE_CLOSE_ERROR;
    }

    return EXIT_SUCCESS;
}

int dot_to_svg(char *dot_name, char *svg_name)
{
    int rc;
    pid_t postprocess_id;

    postprocess_id = fork();

    if (postprocess_id == -1)
    {
        ERROR_LOG("Ошибка создания процесса");
        return EXIT_FAILURE;
    }

    if (!postprocess_id)
        execlp("dot", "dot", "-Tsvg", dot_name, "-o", svg_name, NULL);

    waitpid(postprocess_id, &rc, 0);

    if (rc != EXIT_SUCCESS)
        ERROR_LOG("Ошибка создания изображения");

    return rc;
}

int open_svg(char *svg_name)
{
    int rc;
    FILE *dev_null = NULL;

    if (!fork())
    {
        dev_null = fopen("/dev/null", "r");
        dup2(fileno(dev_null), 1);
        dup2(fileno(dev_null), 2);
        rc = execlp("eog", "eog", svg_name, NULL);
        if (rc != EXIT_SUCCESS)
        {
            ERROR_LOG("Ошибка при открытии изображении графика");
            return rc;
        }
        fclose(dev_null);
    }

    return EXIT_SUCCESS;
}
