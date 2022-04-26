/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @breif Edit entered matrix when count number started with entered number equal count number ended with this number from a row
 */
#include <stdio.h>
#include <stdlib.h>

#define N 10
#define INCORRECT_SIZE 1
#define INCORRECT_MATRIX 2
#define INCORRECT_NUMBER 3

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
 * @param[out] value Value to get
 * @return Error code
 * @breif Scan value from stdin
 */
int scan_number(int *const value)
{
    int error_code = EXIT_SUCCESS;

    printf("Enter number: ");

    if (scanf("%d", value) < 1 || (*value) < 0 || (*value) > 9)
        error_code = INCORRECT_NUMBER;

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
 * @param[in] rows Count rows in matrix
 * @param[in] cols Count coloums in matrix
 * @param[in] place Rows to insert
 * @param[out] matrix Matrix to insert
 * @breif Insert line of 100 in `place` row 
 */
void insert_row(const size_t rows, const size_t cols, const size_t place, int matrix[2 * N][N])
{
    for (size_t i = rows; i > place; i--)
        for (size_t j = 0; j < cols; j++)
            matrix[i][j] = matrix[i - 1][j];

    for (size_t j = 0; j < cols; j++)
        matrix[place][j] = 100;
}

/**
 * @param[in] value Value to get number
 * @return Last character in number 
 * @breif Find last character in number
 */
int get_first_number(const int value)
{
    int result = 0;
    int temp = value;

    while (temp)
    {
        result = abs(temp) % 10;
        temp /= 10;
    }

    return result;
}

/**
 * @param[in] value Value to get number
 * @return Last character in number 
 * @breif Find last character in number
 */
int get_last_number(const int value)
{
    return abs(value) % 10;
}

/**
 * @param[in] rows Count matrix rows
 * @param[in] cols Count matrix coloums
 * @param[in] number Parameter to edit
 * @param[out] matrix Matrix to edit
 * @return New rows count
 * @breif Edit matrix and return new rows count
 */
int edit_matrix(const size_t rows, const size_t cols, const int number, int matrix[2 * N][N])
{
    size_t new_rows = rows;

    for (size_t i = 0; i < new_rows; i++)
    {
        int count_started = 0;
        int count_ended = 0;
        
        for (size_t j = 0; j < cols; j++)
        {
            if (get_first_number(matrix[i][j]) == number)
                count_started++;
            
            if (get_last_number(matrix[i][j]) == number)
                count_ended++;
        }
        
        if (count_started != 0 && count_started == count_ended)
            insert_row(new_rows++, cols, ++i, matrix);
    }

    return new_rows;
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
    int matrix[2 * N][N];
    int number;
    int error_code = EXIT_SUCCESS;

    printf("Enter count of rows: ");
    
    if ((error_code = scan_count(&rows)))
        printf("Incorrect rows value\n");

    printf("Enter count of coloums: ");
    
    if (!error_code && (error_code = scan_count(&cols)))
        printf("Incorrect coloums value\n");
    
    if (!error_code && (error_code = scan_matrix(rows, cols, matrix)))
        printf("Incorrect matrix element value\n");
        
    if (!error_code && (error_code = scan_number(&number)))
        printf("Incorrect number\n");
    
    if (!error_code)
    {
        rows = edit_matrix(rows, cols, number, matrix);

        printf("Result matrix:\n");
        print_matrix((const int (*)[N])matrix, rows, cols);
    }

    return error_code;
}

