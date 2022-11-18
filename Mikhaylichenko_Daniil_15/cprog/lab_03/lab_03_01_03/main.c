#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLUMNS 10
#define WRONG_INPUT 101
#define OUT_OF_RANGE 102
#define EXPECTED_NUMBER_FROM_LENS_INPUT 2

int enter_lens(size_t *const prows, size_t *const pcolumns);
int fill_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);
int is_positive_sequence(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);
int is_negetive_sequence(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);
void find_sequences(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m, int arr[]);
void print_array(const int *const arr, const size_t len);

enum codes
{
    IT_IS_NOT_SEQUENCE,
    IT_IS_SEQUENCE,
    RIGHT_INPUT = 0
};

int main(void)
{
    int matrix[MAX_ROWS][MAX_COLUMNS];
    
    size_t rows, columns;
    int check = enter_lens(&rows, &columns);
    if (check != EXIT_SUCCESS)
        return check;
    
    check = fill_matrix(matrix, rows, columns);
    if (check != EXIT_SUCCESS)
        return check;
    
    int arr[MAX_ROWS];

    find_sequences((const int (*)[MAX_COLUMNS])matrix, rows, columns, arr);
    
    print_array(arr, rows);
    
    return EXIT_SUCCESS;
}

int enter_lens(size_t *const prows, size_t *const pcolumns)
{
    printf("Enter rows and columns: ");
    if (scanf("%zu%zu", prows, pcolumns) != EXPECTED_NUMBER_FROM_LENS_INPUT)
        return WRONG_INPUT;

    if (*prows > MAX_ROWS || *prows <= 0 || *pcolumns > MAX_COLUMNS || *pcolumns <= 0)
        return WRONG_INPUT;

    return RIGHT_INPUT;
}

int fill_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            int num;
            printf("Enter num: ");
            if (scanf("%d", &num) != 1)
                return WRONG_INPUT;
                
            matrix[i][j] = num;
        }
    }
    return RIGHT_INPUT;
}

int is_positive_sequence(const int (*const matrix)[MAX_COLUMNS], const size_t i, const size_t m)
{
    for (size_t j = 1; j < m; j++)
    {
        if (matrix[i][j] < matrix[i][j - 1])
            return IT_IS_NOT_SEQUENCE;
    }
    return IT_IS_SEQUENCE;
}

int is_negetive_sequence(const int (*const matrix)[MAX_COLUMNS], const size_t i, const size_t m)
{
    for (size_t j = 1; j < m; j++)
    {
        if (matrix[i][j] > matrix[i][j - 1])
            return IT_IS_NOT_SEQUENCE;
    }
    return IT_IS_SEQUENCE;
}

void find_sequences(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m, int arr[])
{
    if (m == 1)
    {
        for (size_t i = 0; i < n; i++)
            arr[i] = 0;
        return;
    }
    for (size_t i = 0; i < n; i++)
    {
        if (is_positive_sequence(matrix, i, m) || is_negetive_sequence(matrix, i, m))
            arr[i] = 1;
        else
            arr[i] = 0;
    }
}

void print_array(const int *const arr, const size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%d\n", arr[i]);
}
