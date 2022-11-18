#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#ifndef MAX_SIZE
#error size constant not defined
#endif

unsigned long long get_microseconds_now(void);
void fill_array(int matrix[][MAX_SIZE], size_t len);
void mult_matrix(int first_matrix[][MAX_SIZE], int second_matrix[][MAX_SIZE], int final_matrix[][MAX_SIZE], size_t len);
void print_matrix(int matrix[][MAX_SIZE]);

int final_matrix[MAX_SIZE][MAX_SIZE];

int main(void)
{
	int first_matrix[MAX_SIZE][MAX_SIZE], second_matrix[MAX_SIZE][MAX_SIZE];

	unsigned long long start, stop;
	
	srand(time(NULL));

	fill_array(first_matrix, MAX_SIZE);
	fill_array(second_matrix, MAX_SIZE);
	print_matrix(first_matrix);
	print_matrix(second_matrix);

	start = get_microseconds_now();

	//for (size_t i = 0; i < 1000; i++)
	mult_matrix(first_matrix, second_matrix, final_matrix, MAX_SIZE);

	stop = get_microseconds_now();

	print_matrix(final_matrix);

	double time = (stop - start);

	printf("%lf\n", time / 1000);

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

void mult_matrix(int first_matrix[][MAX_SIZE], int second_matrix[][MAX_SIZE], int final_matrix[][MAX_SIZE], size_t len)
{
	for (size_t i = 0; i < len; i++)
		for (size_t j = 0; j < len; j++)
		{
			final_matrix[i][j] = 0;
			for (size_t k = 0; k < len; k++)
				final_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];
		}
}

void print_matrix(int matrix[][MAX_SIZE])
{
	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		for (size_t j = 0; j < MAX_SIZE; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
	printf("--------------------\n");
}