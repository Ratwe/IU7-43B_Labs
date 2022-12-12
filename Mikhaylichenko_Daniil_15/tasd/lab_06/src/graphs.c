#include "../inc/graphs.h"

void write_node(FILE **file, tree_node_t *tree)
{
    if (tree->left != NULL)
        fprintf(*file, "%s -> %s;\n", tree->word, tree->left->word);
    if (tree->right != NULL)
        fprintf(*file, "%s -> %s;\n", tree->word, tree->right->word);
    else if (tree->left == NULL)
        fprintf(*file, "%s;\n", tree->word);
}

void write_nodes(tree_node_t *tree, FILE **file)
{
    if (tree == NULL)
        return;

    write_node(file, tree);

    write_nodes(tree->left, file);
    write_nodes(tree->right, file);
}

int tree_to_dot(tree_node_t *tree, char *dot_name)
{
    if (tree == NULL)
    {
        ERROR_LOG("Пустое дерево");
        return EMPTY_TREE;
    }

    FILE *dot_file = NULL;
    if ((dot_file = fopen(dot_name, "w")) == NULL)
    {
        ERROR_LOG("Ошибка открытия файла");
        return FILE_OPEN_ERROR;
    }

    fprintf(dot_file, "digraph tree {\n");

    write_nodes(tree, &dot_file);

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
/* int dot_to_svg(char *dot_name, char *svg_name) */
/* { */
/*     int rc; */

/*     if (!fork()) */
/*     { */
/*         rc = execlp("dot", "dot", "-Tsvg", dot_name, "-o", svg_name, NULL); */
/*         if (rc != EXIT_SUCCESS) */
/*         { */
/*             ERROR_LOG("Ошибка создания изображения"); */
/*             return rc; */
/*         } */
/*     } */

/*     return EXIT_SUCCESS; */
/* } */

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
