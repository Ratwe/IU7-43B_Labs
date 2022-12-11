#include "../inc/menu.h"
#include "../inc/scan.h"
#include "../inc/tree.h"
#include "../inc/graphs.h"

void print_menu()
{
    puts("+---------------------------------------------------------------------------------+");
    puts("|Главное меню:                                                                    |");
    puts("|1.+Загрузить ДДП дерево                                                          |");
    puts("|2.+Вывести ДДП                                                                   |");
    puts("|3.-Добавить слово в дерево                                                       |");
    puts("|4.-Удалить слово из дерева                                                       |");
    puts("|5.+Найти слово в дереве                                                          |");
    puts("|6.-Определить кол-во вершин, содержащих слова, начинающиеся на указанную букву   |");
    puts("|7.-Сравнить время поиска начинающихся на указанную букву слов в дереве и в файле |");
    puts("|0.+Выход                                                                         |");
    puts("+---------------------------------------------------------------------------------+");
}

int menu(void)
{
    int rc;
    int command;

    tree_node_t *tree = NULL;

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
                ACTION_LOG("Очистка дерева...");
                free_tree(&tree);

                ACTION_LOG("Открытие файла...");
                FILE *file = fopen(DATABASE, "r");
                if (file == NULL)
                {
                    ERROR_LOG("Ошибка открытия файла");
                    return FILE_OPEN_ERROR;
                }

                ACTION_LOG("Запись в дерево...");
                rc = fill_tree(&tree, &file);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Закрытие файла...");
                if (fclose(file) == EOF)
                {
                    ERROR_LOG("Ошибка закрытия файла");
                    return FILE_CLOSE_ERROR;
                }
                break;
            case 2:
                ACTION_LOG("Создание .dot файла...");
                rc = tree_to_dot(tree, DOT_FILE);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Создания .svg изображения...");
                rc = dot_to_svg(DOT_FILE, SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Открытие .svg изображения...");
                rc = open_svg(SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    break;
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("Введите искомое слово: ");
                char str[MAX_STR_LEN + 1];
                rc = enter_string(str, MAX_STR_LEN);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Введена неверная строка");
                    continue;
                }

                ACTION_LOG("Поиск слова в дереве...");
                search_word(tree, str);
                break;
            case 7:
                break;
        }
        printf("\n");
    }
    while (command);

    return EXIT_SUCCESS;
}
