#include "../inc/menu.h"
#include <stdlib.h>

void print_menu()
{
    puts("+--------------------------------------------------------------------------------------------------+");
    puts("|Главное меню:                                                                                     |");
    puts("|1.  Загрузить ДДП, АВЛ и хэш-таблицы из файла                                                     |");
    puts("|2.  Очистить деревья и хэш-таблицы                                                                |");
    puts("|3.  Вывести ДДП                                                                                   |");
    puts("|4.  Вывести АВЛ                                                                                   |");
    puts("|5.  Вывести хэш-таблицы                                                                           |");
    puts("|6.  Добавить слово в ДДП, АВЛ и хэш-таблицы                                                       |");
    puts("|7.  Удалить слово из ДДП, АВЛ и хэш-таблицы                                                       |");
    puts("|8.  Найти слово в ДДП, АВЛ и хэш-таблицах                                                         |");
    puts("|9.  Определить кол-во вершин со словами, начинающиеся на указанную букву в ДДП, АВЛ и хэш-таблицах|");
    puts("|10. Сравнить эффективность алгоритмов сортировки и поиска                                         |");
    puts("|0.  Выход                                                                                         |");
    puts("+--------------------------------------------------------------------------------------------------+");
}

int menu(void)
{
    int rc;
    int command;
    char str[MAX_STR_LEN + 1];

    tree_node_t *bst = NULL;
    tree_node_t *avl = NULL;

    size_t size = fget_len(DATABASE);
    if (size == 0)
    {
        ERROR_LOG("Пустая база данных");
        return EMPTY_FILE;
    }
    htable_opened_t *htable_opened = new_hash_table_opened(size * OPENED_COEF);
    htable_closed_t *htable_closed = new_hash_table_closed(size * CLOSED_COEF);

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
                ACTION_LOG("Очистка ДДП...");
                free_tree(&bst);
                ACTION_LOG("Очистка АВЛ...");
                free_tree(&avl);
                ACTION_LOG("Очистка открытой хэш-таблицы...");
                free_htable_opened(htable_opened);
                ACTION_LOG("Очистка закрытой хэш-таблицы...");
                free_htable_closed(htable_closed);

                size_t size = fget_len(DATABASE);
                if (size == 0)
                {
                    ERROR_LOG("Пустая база данных");
                    return EMPTY_FILE;
                }
                htable_opened = new_hash_table_opened(size * OPENED_COEF);
                htable_closed = new_hash_table_closed(size * CLOSED_COEF);

                ACTION_LOG("Открытие файла...");
                FILE *file = fopen(DATABASE, "r");
                if (file == NULL)
                {
                    ERROR_LOG("Ошибка открытия файла");
                    return FILE_OPEN_ERROR;
                }

                ACTION_LOG("Запись в ДДП...");
                rc = fill_bst(&bst, &file);
                if (rc != EXIT_SUCCESS)
                {
                    fclose(file);
                    return rc;
                }

                ACTION_LOG("Запись в АВЛ...");
                rc = fill_avl(&avl, &file);
                if (rc != EXIT_SUCCESS)
                {
                    fclose(file);
                    return rc;
                }

                ACTION_LOG("Запись в открытую хэш-таблицу...");
                rc = fill_htable_opened(htable_opened, &file);
                if (rc != EXIT_SUCCESS)
                {
                    fclose(file);
                    return rc;
                }

                ACTION_LOG("Запись в закрытыю хэш-таблицу...");
                rc = fill_htable_closed(htable_closed, &file);
                if (rc != EXIT_SUCCESS)
                {
                    fclose(file);
                    return rc;
                }

                ACTION_LOG("Закрытие файла...");
                if (fclose(file) == EOF)
                {
                    ERROR_LOG("Ошибка закрытия файла");
                    return FILE_CLOSE_ERROR;
                }

                SUCCESS(">>Операция заверщена.");
                break;
            case 2:
                ACTION_LOG("Очистка ДДП...");
                free_tree(&bst);
                ACTION_LOG("Очистка АВЛ...");
                free_tree(&avl);
                ACTION_LOG("Очистка открытой хэш-таблицы...");
                free_htable_opened(htable_opened);
                ACTION_LOG("Очистка закрытой хэш-таблицы...");
                free_htable_closed(htable_closed);

                SUCCESS(">>Операция завершена...");
                break;
            case 3:
                ACTION_LOG("Создание .dot файла...");
                rc = tree_to_dot(bst, BST_DOT_FILE, write_node_no_color);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Создания .svg изображения...");
                rc = dot_to_svg(BST_DOT_FILE, BST_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Открытие .svg изображения...");
                rc = open_svg(BST_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    break;
                SUCCESS(">>Операция заверщена.");
                break;
            case 4:
                ACTION_LOG("Создание .dot файла...");
                rc = tree_to_dot(avl, AVL_DOT_FILE, write_node_no_color);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Создания .svg изображения...");
                rc = dot_to_svg(AVL_DOT_FILE, AVL_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Открытие .svg изображения...");
                rc = open_svg(AVL_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    break;
                SUCCESS(">>Операция заверщена.");
                break;
            case 5:
                print_htable_opened(htable_opened);
                print_htable_closed(htable_closed);
                break;
            case 6:
                printf("Введите добавляемое слово: ");
                rc = enter_string(str, MAX_STR_LEN);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Введена неверная строка");
                    return rc;
                }

                ACTION_LOG("Вставка слова в ДДП...");
                rc = bst_push(&bst, str);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Вставка слова в АВЛ...");
                rc = avl_push(&avl, str);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Вставка слова в открытую хэш-функцию...");
                rc = htable_opened_insert(htable_opened, str);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Вставка слова в закрытую хэш-таблицу...");
                rc = htable_closed_insert(htable_closed, str);
                if (rc != EXIT_SUCCESS)
                    return rc;

                SUCCESS(">>Операция заверщена.");
                break;
            case 7:
                printf("Введите удаляемое слово: ");
                rc = enter_string(str, MAX_STR_LEN);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Введена неверная строка");
                    return rc;
                }

                ACTION_LOG("Удаление слова из ДДП...");
                rc = bst_pop(&bst, str);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Удаление слова из АВЛ...");
                rc = avl_pop(&avl, str);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Удаление слова из открытой таблицы...");
                rc = htable_opened_pop(htable_opened, str);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Удаление слова из закрытой таблицы...");
                rc = htable_closed_pop(htable_closed, str);
                if (rc != EXIT_SUCCESS)
                    break;

                SUCCESS(">>Операция заверщена.");
                break;
            case 8:
                printf("Введите искомое слово: ");
                rc = enter_string(str, MAX_STR_LEN);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Введена неверная строка");
                    return rc;
                }

                ACTION_LOG("Поиск слова в ДДП...");
                search_word(bst, str);

                ACTION_LOG("Поиск слова в АВЛ...");
                search_word(avl, str);

                ACTION_LOG("Поиск слова в открытой хэш-таблице...");
                search_hash_opened_word(htable_opened, str);

                ACTION_LOG("Поиск слова в закрытой хэш таблице...");
                search_hash_closed_word(htable_closed, str);

                SUCCESS(">>Операция заверщена.");
                break;
            case 9:
                printf("Введите букву: ");
                char ch[1 + 1];
                rc = enter_string(ch, 1);
                if (rc != EXIT_SUCCESS)
                {
                    ERROR_LOG("Введён неверный символ");
                    return rc;
                }

                ACTION_LOG("Поиск слов в ДДП...");
                rc = find_letters(&bst, ch);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Поиск слов в АВЛ...");
                rc = find_letters(&avl, ch);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Поиск слова в открытой хэш-таблице...");
                print_htable_opened_color(htable_opened, ch);

                ACTION_LOG("Поиск слова в закрытой хэш-таблице...");
                print_htable_closed_color(htable_closed, ch);

                ACTION_LOG("Создание bst.dot файла...");
                rc = tree_to_dot(bst, BST_DOT_FILE, write_node_color);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Создания bst.svg изображения...");
                rc = dot_to_svg(BST_DOT_FILE, BST_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Создание avl.dot файла...");
                rc = tree_to_dot(avl, AVL_DOT_FILE, write_node_color);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Создания avl.svg изображения...");
                rc = dot_to_svg(AVL_DOT_FILE, AVL_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    return rc;

                ACTION_LOG("Открытие bst.svg изображения...");
                rc = open_svg(BST_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    break;

                ACTION_LOG("Открытие avl.svg изображения...");
                rc = open_svg(AVL_SVG_FILE);
                if (rc != EXIT_SUCCESS)
                    break;


                SUCCESS(">>Операция заверщена.");
                break;
            case 10:
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
