#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define UNCORRECT_VALUE 1

int get_size(size_t *const value)
{
    int error_code = EXIT_SUCCESS;

    if (scanf("%zu", value) < 1 || (*value) == 0 || (*value) > MAX_SIZE)
        error_code = UNCORRECT_VALUE;

    return error_code;
}

int get_matrix(const size_t rows, const size_t cols, int matrix[MAX_SIZE][MAX_SIZE])
{
    int error_code = EXIT_SUCCESS;
    
    printf("Enter matrix\n");
    for (size_t i = 0; i < rows && !error_code; i++)
         for (size_t j = 0; j < cols && !error_code; j++)
              if (scanf("%d", &matrix[i][j]) < 1)
                  error_code = UNCORRECT_VALUE;

    return error_code;
}

void move_up(int matrix[MAX_SIZE][MAX_SIZE], const size_t rows, const size_t cols)
{
    int temp[MAX_SIZE];

    for (size_t i = 0; i < cols; i++)
        temp[i] = matrix[0][i];

    for (size_t i = 1; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            matrix[i - 1][j] = matrix[i][j];
    
    for (size_t i = 0; i < cols; i++)
        matrix[rows - 1][i] = temp[i];
}

void move_left(int matrix[MAX_SIZE][MAX_SIZE], const size_t rows, const size_t cols)
{
    int temp[MAX_SIZE];

    for (size_t i = 0; i < rows; i++)
        temp[i] = matrix[i][0];

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 1; j < cols; j++)
            matrix[i][j - 1] = matrix[i][j];
    
    for (size_t i = 0; i < cols; i++)
        matrix[i][cols - 1] = temp[i];
}

void print_matrix(const int matrix[MAX_SIZE][MAX_SIZE], const size_t rows, const size_t cols)
{
    printf("Result matrix:\n");

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
    int r, l, u, d;
    int count_l, count_u;
    int matrix[MAX_SIZE][MAX_SIZE];
    
    int error_code = EXIT_SUCCESS;
    
    printf("Enter count rows: ");
    if ((error_code = get_size(&rows)))
        printf("Uncorrect rows\n");

    printf("Enter count cols: ");
    if (!error_code && (error_code = get_size(&cols)))
        printf("Uncorrect cols\n");

    if (!error_code && (error_code = get_matrix(rows, cols, matrix)))
        printf("Uncorrect value\n");

    if (!error_code)
    {
        printf("Enrer shift counts: ");

        if ((error_code = (scanf("%d %d %d %d", &l, &r, &u, &d) < 4)))
            printf("Uncorrect value\n");
        else
        {
            count_l = ((int)(l % cols - r % cols) + cols) % cols;
            count_u = ((int)(u % rows - d % rows) + rows) % rows;
            
            for (int i = 0; i < count_l; i++)
                move_left(matrix, rows, cols);

            for (int i = 0; i < count_u; i++)
                move_up(matrix, rows, cols);

            print_matrix((const int(*)[MAX_SIZE]) matrix, rows, cols);
       }
    }

    return error_code;
}
