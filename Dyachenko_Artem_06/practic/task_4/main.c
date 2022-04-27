#include <stdio.h>

#define N 2
#define M 3
#define L 4

int main(void)
{
	int a[2][3][4] = {0};
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			for (int k = 0; k < L; k++)
			{
				a[i][j][k] = i * 2 + j * 3 + k * 4;
//				printf("a[%d][%d][%d] = %d\n", i, j, k, i * 2 + j * 3 + k * 4);
			}

	int *p1, *p2, *p3, *p4, *p5, *d3, *d4, *d5;
	p1 = &a[0][0][0];
	p2 = &a[1][2][3];

	p3 = &a[0];
	p4 = &a[0][0];
	p5 = &a[0][0][0];

	d3 = &a[1];
	d4 = &a[0][1];
	d5 = &a[0][0][1];

	int r3, r4, r5;
	r3 = d3 - p3;
	r4 = d4 - p4;
	r5 = d5 - p5;

	printf("%p - %p = %p\n", d3, p3, d3 - p3);

	int sp3 = sizeof(*p3);
	int sp4 = sizeof(*p4);
	int sp5 = sizeof(*p5);
}
