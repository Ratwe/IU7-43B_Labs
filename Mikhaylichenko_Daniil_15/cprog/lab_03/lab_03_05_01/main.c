#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLUMNS 10
#define EXPECTED_NUMBER_FROM_LENS_INPUT 2
#define EXPECTED_NUMBER_FROM_NUM_INPUT 1
#define SHIFT 3
#define REQUIRED_SUM 10
#define RADIX 10

int enter_lens(size_t *const prows, size_t *const pcolumns);
int fill_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);
int is_needed_num(int num);
int fill_array(int *const arr, int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);
void move_elements(int *const arr, int *const new_arr, const size_t len, size_t shift);
void replace_elements(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m, const int *arr);
int change_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);
void print_matrix(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m);

enum codes
{
    RIGHT_INPUT,
    WRONG_INPUT = 101,
    OUT_OF_RANGE,
    NO_REQUIRED_NUMS,
    THERE_ARE_REQUIRED_NUMS = 0,
    IS_NOT_NEEDED_NUM = 0,
    IS_NEEDED_NUM
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

    check = change_matrix(matrix, rows, columns);
    if (check != EXIT_SUCCESS)
        return check;
        
    print_matrix((const int (*)[MAX_COLUMNS])matrix, rows, columns);

    return EXIT_SUCCESS;
}

int enter_lens(size_t *const prows, size_t *const pcolumns)
{
    printf("Enter rows and columns: ");
    if (scanf("%zu%zu", prows, pcolumns) != EXPECTED_NUMBER_FROM_LENS_INPUT)
        return WRONG_INPUT;

    if (*prows > MAX_ROWS || *prows <= 0 || *pcolumns > MAX_COLUMNS || *pcolumns <= 0)
        return OUT_OF_RANGE;

    return RIGHT_INPUT;
}

int fill_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
        {
            int num;
            printf("Enter next_num: ");
            if (scanf("%d", &num) != EXPECTED_NUMBER_FROM_NUM_INPUT)
                return WRONG_INPUT;

            matrix[i][j] = num;
        }
    return RIGHT_INPUT;
}

int is_needed_num(int num)
{
    int sum = 0;
    
    while (num)
    {
        sum += num % RADIX;
        num /= RADIX;
    }

    if (sum > REQUIRED_SUM)
        return IS_NEEDED_NUM;

    return IS_NOT_NEEDED_NUM;
}

int fill_array(int *const arr, int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m)
{    
    size_t len = 0;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (is_needed_num(abs(matrix[i][j])))
            {
                arr[len] = matrix[i][j];
                len++;
            }

    return len;
}

void move_elements(int *const arr, int *const new_arr, const size_t len, size_t shift)
{
    shift %= RADIX;

    for (size_t i = 0; i < len; i++)
        new_arr[(len + i - shift) % len] = arr[i];

}

void replace_elements(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m, const int *arr)
{
    size_t index = 0;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (is_needed_num(abs(matrix[i][j])))
            {
                matrix[i][j] = arr[index];
                index++;
            }
}

int change_matrix(int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m)
{
    int arr[MAX_ROWS * MAX_COLUMNS], new_arr[MAX_ROWS *  MAX_COLUMNS];

    size_t arr_len = fill_array(arr, matrix, n, m);
    if (arr_len == 0)
        return NO_REQUIRED_NUMS;

    move_elements(arr, new_arr, arr_len, SHIFT);

    replace_elements(matrix, n, m, new_arr);

    return THERE_ARE_REQUIRED_NUMS;
}

void print_matrix(const int (*const matrix)[MAX_COLUMNS], const size_t n, const size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}
