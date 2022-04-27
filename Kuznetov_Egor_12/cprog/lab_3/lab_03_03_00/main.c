/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @breif Sort entered matrix by sum of element
 */
#include <stdio.h>
#include <stdlib.h>

#define N 10
#define INCORRECT_SIZE 1
#define INCORRECT_MATRIX 2

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
 * @param[out] a First value
 * @param[out] b Second value
 * @brief Swap first and second value
 */
void swapl(long long *const a, long long *const b)
{
    const long long temp = *a;
    *a = *b;
    *b = temp;
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
 * @param[in] row_1 Swaped row 1
 * @param[in] row_2 Swaped row 2
 * @param[in] cols Count coloums in matrix
 * @param[out] matrix Matrix to swap
 * @breif Swap row in matrix
 */
void swap_rows(const size_t row_1, const size_t row_2, const size_t cols, int matrix[N][N])
{
    for (size_t j = 0; j < cols; j++)
        swap(&matrix[row_1][j], &matrix[row_2][j]);
}

/**
 * @param[in] matrix Base matrix
 * @param[in] row Row to get key
 * @param[in] cols Count coloums in matrix
 * @return Row key
 * @breif Sum elements matrix row and return
 */
long long get_key(int matrix[N][N], const size_t row, const size_t cols)
{
    long long sum = 0;

    for (size_t i = 0; i < cols; i++)
        sum += matrix[row][i];

    return sum;
}

/**
 * @param[in] rows Count matrix rows
 * @param[in] cols Count matrix coloums
 * @param[out] matrix Matrix to sort
 * @breif Sort matrix in place
 */
void sort_matrix(const size_t rows, const size_t cols, int matrix[N][N])
{
    long long keys[N];
    
    for (size_t i = 0; i < rows; i++)
        keys[i] = get_key(matrix, i, cols);
    
    for (size_t i = 0; i < rows - 1; i++)
        for (size_t j = i + 1; j < rows; j++)
            if (keys[i] > keys[j])
            {
                swap_rows(i, j, cols, matrix);
                swapl(&keys[i], &keys[j]);
            }
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
        printf("Incorrect coloums value\n");

    if (!error_code && (error_code = scan_matrix(rows, cols, matrix)))
        printf("Incorrect matrix element value\n");

    if (!error_code)
    {
        sort_matrix(rows, cols, matrix);

        printf("Result matrix:\n");
        print_matrix((const int (*)[N])matrix, rows, cols);
    }
    
    return error_code;
}

