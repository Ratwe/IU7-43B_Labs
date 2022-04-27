/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @breif Create matrix
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define INCORRECT_SIZE 1

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
 * @param[in] rows Count matrix rows
 * @param[in] cols Count matrix coloums
 * @param[out] matrix Matrix to fill
 * @breif Fill matrix 
 */
void fill_matrix(const size_t rows, const size_t cols, int matrix[N][N])
{
    int value = 1;

    for (size_t i = 0; i < cols; i++)
        if (i % 2 != 0)
            for (size_t j = rows; j > 0; j--)
                matrix[j - 1][i] = value++;
        else
            for (size_t j = 0; j < rows; j++)
                matrix[j][i] = value++;
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
    
    if (!error_code)
    {
        fill_matrix(rows, cols, matrix);
    
        printf("Result matrix:\n");
        print_matrix((const int (*)[N])matrix, rows, cols);
    }

    return error_code;
}

