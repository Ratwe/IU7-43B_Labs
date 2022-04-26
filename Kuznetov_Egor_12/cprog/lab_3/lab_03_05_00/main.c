/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @breif Reverse simple elements of entered matrix
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define INCORRECT_SIZE 1
#define INCORRECT_MATRIX 2
#define NO_SIMPLE_NUMBER 3
#define TRUE 1
#define FALSE 0

/**
 * @param[out] value Value to get
 * @return Error code
 * @breif Scan value from stdin
 */
int scan_count(size_t *const value)
{
    int error_code = EXIT_SUCCESS;

    if (scanf("%zu", value) < 1 || (*value) == 0 || (*value) > N)
        error_code = INCORRECT_SIZE;

    return error_code;
}

/**
 * @param[in] rows Count matrix rows to scan
 * @param[in] cols Count matrix coloums to scan
 * @param[out] matrix Matrix to fill
 * @return Error code
 * @breif Scan matrix from stdin
 */
int scan_matrix(const size_t rows, const size_t cols, int matrix[2 * N][N])
{
    int error_code = EXIT_SUCCESS;

    for (size_t i = 0; i < rows && !error_code; i++)
    {
        printf("Enter row: ");

        for (size_t j = 0; j < cols && !error_code; j++)
            if (scanf("%d", &matrix[i][j]) < 1)
                error_code = INCORRECT_MATRIX;
    }

    return error_code;
}

/**
 * @return Simple number or not
 */
int is_simple(const int number)
{
    int return_value = TRUE;
    double max_dev = sqrt(1. * number) + 0.0001;
    
    if (number <= 1)
        return_value = FALSE;

    for (int i = 2; i < max_dev && return_value; i++)
        if (number % i == 0)
            return_value = FALSE;
    
    return return_value;
}

/**
 * @param[out] a First value
 * @param[out] b Second value
 * @brief Swap first and second value
 */
void swap(int *const a, int *const b)
{
    const int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @param[in] rows Count matrix rows
 * @param[in] cols Count matrix coloums
 * @param[out] matrix Matrix to edit
 * @return Count simple numbers
 * @breif Reverse simple number position
 */
int edit_matrix(const size_t rows, const size_t cols, int matrix[N][N])
{
    size_t elem_size = 0;
    size_t pos_from_start = 0, pos_from_end = rows * cols - 1;
    int is_finded;

    while (pos_from_start <= pos_from_end)
    {
        is_finded = FALSE;

        for (; pos_from_start <= pos_from_end && !is_finded; pos_from_start++)
            if (is_simple(matrix[pos_from_start / cols][pos_from_start % cols]))
                is_finded = TRUE;
        if (is_finded)
            elem_size++;

        is_finded = FALSE;
        
        for (; pos_from_start <= pos_from_end && !is_finded; pos_from_end--)
            if (is_simple(matrix[pos_from_end / cols][pos_from_end % cols]))
                is_finded = TRUE;

        if (is_finded)
        {
            swap(&matrix[(pos_from_start - 1) / cols][(pos_from_start - 1) % cols], &matrix[(pos_from_end + 1) / cols][(pos_from_end + 1) % cols]);
            elem_size++;
        }
    }
    
    return elem_size;
}

/**
 * @param[in] matrix Printed matrix
 * @param[in] rows Matrix rows count
 * @param[in] cols Matrix coloums count
 * @brief Print array
 */
void print_matrix(const int matrix[][N], const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int main(void)
{
    size_t rows, cols;
    int matrix[N][N];
    int error_code = EXIT_SUCCESS;

    printf("Enter count of rows: ");
    
    if ((error_code = scan_count(&rows)))
        printf("Incorrect rows value\n");
    
    printf("Enter count of coloums: ");
    
    if (!error_code && (error_code = scan_count(&cols)))
        printf("Incorrect coloums value\n");\
    
    if (!error_code && (error_code = scan_matrix(rows, cols, matrix)))
        printf("Incorrect matrix element value\n");

    if (!error_code && !edit_matrix(rows, cols, matrix))
    {
        printf("No simple number in matrix\n");
        error_code = NO_SIMPLE_NUMBER;
    }

    if (!error_code)
    {
        printf("Result matrix:\n");
        print_matrix((const int (*)[N])matrix, rows, cols);
    }
    
    return error_code;
}

