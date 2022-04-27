#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 10
#define WRONG_INPUT 101
#define EXPECTED_NUMBER_FOM_INPUT 2

void fill_matrix(int arr[][M], size_t n, size_t m);
void print_matrix(int arr[][M], size_t n, size_t m);

int main(void)
{
	int matrix[N][M];

	size_t rows, columns;

	printf("Enter rows and columns: ");
	if (scanf("%lu%lu", &rows, &columns) != EXPECTED_NUMBER_FOM_INPUT)
		return WRONG_INPUT;

	if (rows > 10 || rows == 0 || columns > 10 || columns == 0 || rows != columns)
		return WRONG_INPUT;

	fill_matrix(matrix, rows, columns);

	print_matrix(matrix, rows, columns);

	return EXIT_SUCCESS;
}

void fill_matrix(int matrix[][M], size_t n, size_t m)
{
	size_t ibeg = 0, ifin = 0, jbeg = 0, jfin = 0;
	size_t k = 1;
	size_t i = 0, j = 0;

	while (k <= m * m)
	{
		matrix[i][j] = k;
		
		if (j == jbeg && i < n - ifin - 1)
			i++;
		else if (i == n - ifin - 1 && j < m - jfin - 1)
			j++;
		else if (j == m - jfin - 1 && i > ibeg)
			i--;
		else
			j--;

		if ((j == jbeg + 1) && (i == ibeg) && (ibeg != n - ifin - 1))
		{
			ibeg++;
			ifin++;
			jbeg++;
			jfin++;
		}

		k++;
	}
}

void print_matrix(int matrix[][M], size_t n, size_t m)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

