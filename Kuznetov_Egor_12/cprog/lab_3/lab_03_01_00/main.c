/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @breif From entered matrix print 1 if coloum is sorted in descending order and 0 in another cases 
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
int scan_matrix(const size_t rows, const size_t cols, int matrix[N][N])
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
 * @param[in] matrix Base matrix
 * @param[in] rows Count matrix rows
 * @param[in] cols Count matrix coloums
 * @param[out] array Array to fill
 * @breif Construct array based on matrix
 */
void construct_array(const int matrix[N][N], const size_t rows, const size_t cols, int array[])
{
    for (size_t i = 0; i < cols; i++)
    {
        array[i] = rows > 1 ? 1 : 0;

        for (size_t j = 1; j < rows; j++)
            if (matrix[j][i] >= matrix[j - 1][i])
                array[i] = 0;
    }
}

/**
 * @param[in] array Printed array
 * @param[in] n Array lenght
 * @brief Print array
 */
void print_array(const int array[], const size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main(void)
{
    size_t rows, cols;
    int matrix[N][N];
    int result_array[N];
    int error_code = EXIT_SUCCESS;

    printf("Enter count of rows: ");
    
    if ((error_code = scan_count(&rows)))
        printf("Incorrect rows value\n");
    
    printf("Enter count of coloums: ");
    
    if (!error_code && (error_code = scan_count(&cols)))
        printf("Incorrect coloums value\n");

    if (!error_code && (error_code = scan_matrix(rows, cols, matrix)))
        printf("Incorrect matrix element value");
    
    if (!error_code)
    {
        construct_array((const int (*)[N])matrix, rows, cols, result_array);

        printf("Result array: ");
        print_array(result_array, cols);
    }

    return error_code;
}

