#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define EPS 1e-3
#define EXPECTED_INPUT 6
#define ACUTE 0
#define RECTANGULAR 1
#define OBTUSE 2
#define TRIANGLE_IS_A_LINE 3
#define FLT_MAXX FLT_MAX

// сравнение вещественных чисел
int is_equal(float a, float b)
{
    return fabs(a - b) < EPS;
}

int input(float *xa, float *ya, float *xb, float *yb, float *xc, float *yc)
{
    int rc = scanf("%f%f%f%f%f%f", &*xa, &*ya, &*xb, &*yb, &*xc, &*yc);

    if (rc != EXPECTED_INPUT)
        return EXIT_FAILURE;

    // ограничение на ввод
    float biggest_num = fmaxf(*xa, fmaxf(*ya, fmaxf(*xb, fmaxf(*yb, fmaxf(*xc, *yc)))));

    #ifdef DEBUG
    printf("biggest_num = %f\n", biggest_num);
    printf("abs(sqrtf(FLT_MAX / 24) - biggest_num) = %f\n", fabs(sqrt(FLT_MAX / 24) - biggest_num));
    #endif

    if (biggest_num > sqrt(FLT_MAXX / 24))
    {
        printf("Одно из чисел слишком большое!\n");
        return EXIT_FAILURE;
    }

    // если две точки совпадают
    if ((is_equal(*xa, *xb) && is_equal(*ya, *yb)) ||
        (is_equal(*xa, *xc) && is_equal(*ya, *yc)) ||
        (is_equal(*xb, *xc) && is_equal(*yb, *yc)))
        return EXIT_FAILURE;
	
    return EXIT_SUCCESS;
}

// подсчёт ответа
int calculate(float xa, float ya, float xb, float yb, float xc, float yc)
{
    float a, b, c, m, cos;

    // длины сторон
    a = sqrtf(powf(xb - xa, 2) + powf(yb - ya, 2));
    b = sqrtf(powf(xc - xb, 2) + powf(yc - yb, 2));
    c = sqrtf(powf(xa - xc, 2) + powf(ya - yc, 2));

    m = fmaxf(a, fmaxf(b, c)); // максимальная сторона
    // проверка на вырожденный треугольник
    if (is_equal(2 * m - a - b - c, 0))
        return TRIANGLE_IS_A_LINE;

    /*
     * Если sqrt(a) > sqrt(FLT_MAX) -> переполнение
     * Можно ли проверить, будет ли cos < 0 без квадратов?
     *
     * a = 3
     * b = 4
     * c = 7
     * cos = 9 + 16 - 49
     * cos < 0 если c^2 > a^2 + b^2
     *
     * a^2 + b^2 + 2ab = (a + b)^2 - 2ab
     * c^2 + 2ab = (a + b)^2
     *
     * Решение в лоб:
     * Завершать программу, если вводят большие числа
     *
     * Алгоритмическое решение:
     * Использовать длинную арифметику
     *
    */

    cos = a * a + b * b + c * c - 2 * m * m;

    if (is_equal(cos, 0))
        return RECTANGULAR;
    else if (cos < 0)
        return OBTUSE;
    else
        return ACUTE;
}

int main(void)
{
    float xa, ya, xb, yb, xc, yc;

    #ifdef DEBUG
    printf("FLT_MAX = %f\n", FLT_MAX);
    printf("xa <= %f\n", sqrt(FLT_MAX / 24));
    #endif

    if (input(&xa, &ya, &xb, &yb, &xc, &yc))
        return EXIT_FAILURE;

    if (calculate(xa, ya, xb, yb, xc, yc) == TRIANGLE_IS_A_LINE)
        return EXIT_FAILURE;

    printf("%d\n", calculate(xa, ya, xb, yb, xc, yc));

    return EXIT_SUCCESS;
}
