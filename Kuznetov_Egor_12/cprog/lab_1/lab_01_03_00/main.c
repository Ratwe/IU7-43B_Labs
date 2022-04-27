/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Find normal math and BMI by enter heigth,
 * chest girth and mass
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double h, t, m;
    double m_normal, bmi;

    printf("Enter heigth: ");
    scanf("%lf", &h);
    printf("Enter chest girth: ");
    scanf("%lf", &t);
    printf("Enter mass: ");
    scanf("%lf", &m);

    m_normal = h * t / 240.;
    bmi = m * 10000. / (h * h);
    printf("Normal mass equal %.6lf\nBMI equal %.6lf\n", m_normal, bmi);
    return EXIT_SUCCESS;
}

