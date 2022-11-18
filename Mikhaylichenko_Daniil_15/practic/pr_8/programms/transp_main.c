/* Михайличенко Даниил ИУ7-23Б
** Способ перемножения матриц через транспонирование второй
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#ifndef MAX_SIZE
#error size constant not defined
#endif

unsigned long long get_microseconds_now(void);
void fill_array(int matrix[][MAX_SIZE], size_t len);
void transpose(int matrix[][MAX_SIZE], size_t len);
void mult_matrix(int first_matrix[][MAX_SIZE], int second_matrix[][MAX_SIZE], int final_matrix[][MAX_SIZE], size_t len);

int final_matrix[MAX_SIZE][MAX_SIZE];

int main(void)
{
	int first_matrix[MAX_SIZE][MAX_SIZE], second_matrix[MAX_SIZE][MAX_SIZE];

	unsigned long long start, stop;
	
	srand(time(NULL));

	fill_array(first_matrix, MAX_SIZE);
	fill_array(second_matrix, MAX_SIZE);

	start = get_microseconds_now();

	mult_matrix(first_matrix, second_matrix, final_matrix, MAX_SIZE);

	stop = get_microseconds_now();

	double time = (stop - start);

	printf("%lf\n", time);

	return EXIT_SUCCESS;
}

unsigned long long get_microseconds_now(void)
{
	struct timeval val;

	gettimeofday(&val, NULL);

	return val.tv_sec * 1000000ULL + val.tv_usec;
}

void fill_array(int matrix[][MAX_SIZE], size_t len)
{
	for (size_t i = 0; i < len; i++)
		for (size_t j = 0; j < len; j++)	
			matrix[i][j] = rand() % 200 - 100;
}

void transpose(int matrix[][MAX_SIZE], size_t len)
{
	for (size_t i = 0; i < len; i++)
		for (size_t j = i + 1; j < len; j++)
		{
			int temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
}

void mult_matrix(int first_matrix[][MAX_SIZE], int second_matrix[][MAX_SIZE], int final_matrix[][MAX_SIZE], size_t len)
{
	transpose(second_matrix, len);

	for (size_t i = 0; i < len; i++)
		for (size_t j = 0; j < len; j++)
		{
			final_matrix[i][j] = 0;
			for (size_t k = 0; k < len; k++)
				final_matrix[i][j] += first_matrix[i][k] * second_matrix[i][k];
		}
}