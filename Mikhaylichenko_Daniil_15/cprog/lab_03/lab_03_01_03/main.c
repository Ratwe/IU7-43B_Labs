#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 10
#define WRONG_INPUT 101
#define OUT_OF_RANGE 102
#define CHECK_PASS 0
#define CHECK_FAIL 1
#define IT_IS_SEQUENCE 1
#define IT_IS_NOT_SEQUENCE 0
#define EXPECTED_NUMBER_FROM_INPUT 2

int fill_matrix(int matrix[][M], size_t n, size_t m);
int is_positive_sequence(int matrix[][M], size_t n, size_t m);
int is_negetive_sequence(int matrix[][M], size_t n, size_t m);
void find_sequences(int matrix[][M], size_t n, size_t m, int arr[]);
void print_array(int arr[], size_t len);

int main(void)
{
	int matrix[N][M];
	
	size_t rows, columns;
	
	printf("Enter rows and columns: ");
	if (scanf("%lu%lu", &rows, &columns) != EXPECTED_NUMBER_FROM_INPUT)
		return WRONG_INPUT;
	
	if (rows > 10 || rows == 0 || columns > 10 || columns == 0)
		return OUT_OF_RANGE;
	
	int check = fill_matrix(matrix, rows, columns);
	if (check != 0)
		return WRONG_INPUT;
	
	int arr[M];
	find_sequences(matrix, rows, columns, arr);
	
	print_array(arr, rows);
	
	return EXIT_SUCCESS;
}

int fill_matrix(int matrix[][M], size_t n, size_t m)
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
	return CHECK_PASS;
}

int is_positive_sequence(int matrix[][M], size_t i, size_t m)
{
	for (size_t j = 1; j < m; j++)
	{
		if (matrix[i][j] < matrix[i][j - 1])
			return IT_IS_NOT_SEQUENCE;
	}
	return IT_IS_SEQUENCE;
}

int is_negetive_sequence(int matrix[][M], size_t i, size_t m)
{
	for (size_t j = 1; j < m; j++)
	{
		if (matrix[i][j] > matrix[i][j - 1])
			return IT_IS_NOT_SEQUENCE;
	}
	return IT_IS_SEQUENCE;
}

void find_sequences(int matrix[][M], size_t n, size_t m, int arr[])
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

void print_array(int arr[], size_t len)
{
	for (size_t i = 0; i < len; i++)
		printf("%d\n", arr[i]);
}
