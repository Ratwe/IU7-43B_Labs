#include "../inc/menu.h"

void print_menu()
{
    puts("+------------------------------------------------------+");
    puts("|Главное меню:                                         |");
    puts("| 1. Загрузить граф                                    |");
    puts("| 2. Очистить графы                                    |");
    puts("| 3. Вывести матрицу                                   |");
    puts("| 4. Вывести список                                    |");
    puts("| 5. Вывести граф на основе матрицы                    |");
    puts("| 6. Вывести граф на основе списка                     |");
    puts("| 7. Найти максимальное расстояние между парами вершин |");
    puts("| 0. Выход                                             |");
    puts("+------------------------------------------------------+");
}

int menu(void)
{
    int rc;
    int command;
    //int num;

    matrix_graph_t *matrix_graph = NULL;
    list_graph_t *list_graph = NULL;

    do
    {
        print_menu();
        printf("\n");
        rc = scan_command(&command);
        if (rc != EXIT_SUCCESS)
            continue;

        switch (command)
        {
            case 0:
                break;
            case 1:
                ACTION_LOG("Очистка графа на основе матрицы...");
                free_matrix_graph(matrix_graph);
                ACTION_LOG("Очистка графа на основе списка...");
                free_list_graph(list_graph);

                char fname[MAX_STR_LEN + 1];
                printf("    Введите название файла: ");
                rc = enter_string(fname, MAX_STR_LEN + 1);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Открытие файла...");
                FILE *file = fopen(fname, "r");
                if (file == NULL)
                {
                    ERROR_LOG("Ошибка открытия файла");
                    return FILE_OPEN_ERROR;
                }

                ACTION_LOG("Запись в граф на основе матрицы...");
                rc = fill_matrix_graph(&matrix_graph, &file);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Запись в граф на основе списка...");
                rc = fill_list_graph(&list_graph, &file);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Закрытие файла...");
                if (fclose(file) == EOF)
                {
                    ERROR_LOG("Ошибка закрытия файла");
                    return FILE_CLOSE_ERROR;
                }
                SUCCESS(">>Операция заверщена.");
                break;
            case 2:
                ACTION_LOG("Очистка дерева на основе массива...");
                free_matrix_graph(matrix_graph);
                ACTION_LOG("Очистка дерева на основе списка...");
                free_list_graph(list_graph);

                SUCCESS(">>Операция завершена...");
                break;
            case 3:
                ACTION_LOG("Вывод матрицы...");
                print_matrix(matrix_graph);
                SUCCESS("Операция завершена.");
                break;
            case 4:
                ACTION_LOG("Вывод списка...");
                print_list(list_graph);
                SUCCESS("Операция завершена...");
                break;
            case 5:
                ACTION_LOG("Создание .dot файла...");
                rc = graph_to_dot(matrix_graph, MATRIX_DOT_FILE, write_matrix_graph);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Создания .svg изображения...");
                rc = dot_to_svg(MATRIX_DOT_FILE, MATRIX_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Открытие .svg изображения...");
                rc = open_svg(MATRIX_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    break;
                SUCCESS(">>Операция заверщена.");
                break;
            case 6:
                ACTION_LOG("Создание .dot файла...");
                rc = graph_to_dot(list_graph, LIST_DOT_FILE, write_list_graph);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Создания .svg изображения...");
                rc = dot_to_svg(LIST_DOT_FILE, LIST_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Открытие .svg изображения...");
                rc = open_svg(LIST_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    break;
                SUCCESS(">>Операция заверщена.");
                break;
            case 7:
                if (matrix_graph == NULL || matrix_graph->size == 0)
                {
                    ERROR_LOG("Пустой граф");
                    break;
                }

                for (int i = 0; i < matrix_graph->size; i++)
                {
                    printf("\n");
                    anti_dijkstra_matrix(matrix_graph, i);
                }
                SUCCESS(">>Операция заверщена.");
                break;
            case 8:
                anti_dijkstra_list(list_graph, 1);
                break;
        }
        printf("\n");
    }
    while (command);

    return EXIT_SUCCESS;
}
