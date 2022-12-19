#include "../inc/menu.h"
#include "../inc/scan.h"
#include "../inc/tree.h"
#include "../inc/graphs.h"
#include "../inc/efficiency.h"

void print_menu()
{
    puts("+---------------------------------------------------------------------------------+");
    puts("|Главное меню:                                                                    |");
    puts("|1. Загрузить ДДП дерево из файла                                                 |");
    puts("|2. Очистить дерево                                                               |");
    puts("|3. Вывести ДДП                                                                   |");
    puts("|4. Добавить слово в дерево                                                       |");
    puts("|5. Удалить слово из дерева                                                       |");
    puts("|6. Найти слово в дереве                                                          |");
    puts("|7. Определить кол-во вершин, содержащих слова, начинающиеся на указанную букву   |");
    puts("|8. Сравнить эффективность алгоритмов сортировки и поиска                         |");
    puts("|0. Выход                                                                         |");
    puts("+---------------------------------------------------------------------------------+");
}

int menu(void)
{
    int rc;
    int command;
    char str[MAX_STR_LEN + 1];

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
                SUCCESS(">>Операция заверщена.");
                break;
            case 2:
                ACTION_LOG("Очистка дерева...");
                free_tree(&tree);

                SUCCESS(">>Операция завершена...");
                break;
            case 3:
                ACTION_LOG("Создание .dot файла...");
                rc = tree_to_dot(tree, DOT_FILE, write_node_no_color);
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
                SUCCESS(">>Операция заверщена.");
                break;
            case 4:
                printf("Введите добавляемое слово: ");
                rc = enter_string(str, MAX_STR_LEN);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Введена неверная строка");
                    return rc;
                }

                ACTION_LOG("Вставка слова в дерево...");
                rc = tree_push(&tree, str);
                if (rc != EXIT_SUCCESS)
                    return rc;

                SUCCESS(">>Операция заверщена.");
                break;
            case 5:
                printf("Введите удаляемое слово: ");
                rc = enter_string(str, MAX_STR_LEN);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Введена неверная строка");
                    return rc;
                }

                ACTION_LOG("Удаление слова из дерева...");
                rc = tree_pop(&tree, str);
                if (rc != EXIT_SUCCESS)
                    break;

                SUCCESS(">>Операция заверщена.");
                break;
            case 6:
                printf("Введите искомое слово: ");
                rc = enter_string(str, MAX_STR_LEN);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Введена неверная строка");
                    break;
                }

                ACTION_LOG("Поиск слова в дереве...");
                search_word(tree, str);

                SUCCESS(">>Операция заверщена.");
                break;
            case 7:
                printf("Введите букву: ");
                char ch[1 + 1];
                rc = enter_string(ch, 1);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Введён неверный символ");
                    return rc;
                }

                ACTION_LOG("Поиск слов...");
                rc = find_letters(&tree, ch);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Создание .dot файла...");
                rc = tree_to_dot(tree, DOT_FILE, write_node_color);
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

                SUCCESS(">>Операция заверщена.");
                break;
            case 8:
                ACTION_LOG("Сравнение алгоритмов...");
                run_efficiency();

                SUCCESS(">>Операция завершена.");
                break;
        }
        printf("\n");
    }
    while (command);

    return EXIT_SUCCESS;
}
