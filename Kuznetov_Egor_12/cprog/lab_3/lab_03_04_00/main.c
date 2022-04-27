/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @breif Print minimal odd element of matrix below main diagonal
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define INCORRECT_SIZE 1
#define INCORRECT_MATRIX 2
#define NO_ODD_NUMBER 3

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
 * @param[in] size Count matrix size
 * @param[in] matrix Matrix to find
 * @return If matrix have odd number below main diagonale return minimal, else 0
 * @breif Find minimal odd number below main matrix diagonal and return that(return 0 if no odd number)
 */
int find_min_odd_number(const size_t size, const int matrix[N][N])
{
    int number = 0;

    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < i; j++)
            if (abs(matrix[i][j]) % 2 == 1 && (matrix[i][j] < number || number == 0))
                number = matrix[i][j];

    return number;
}

int main(void)
{
    size_t rows, cols;
    int result;
    int matrix[N][N];
    int error_code = EXIT_SUCCESS;

    printf("Enter count of rows: ");
    if ((error_code = scan_count(&rows)))
        printf("Incorrect rows value\n");
    
    printf("Enter count of coloums: ");
    
    if (!error_code && (scan_count(&cols) || cols != rows))
    {
        printf("Incorrect coloums value\n");
        error_code = INCORRECT_SIZE;
    }

    if (!error_code && (error_code = scan_matrix(rows, cols, matrix)))
        printf("Incorrect matrix element value\n");

    if (!error_code && !(result = find_min_odd_number(rows, (const int (*)[N])matrix)))
    {
        printf("No odd number below main matrix diagonal\n");
        error_code = NO_ODD_NUMBER;
    }
    
    if (!error_code)
        printf("Minimal odd value: %d\n", result);
    
    return error_code;
}

