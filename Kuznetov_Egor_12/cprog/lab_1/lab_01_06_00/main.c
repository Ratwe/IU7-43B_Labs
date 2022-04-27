/**
 * @file
 * @author Kuznetsov Egor IU7-23B
 * @brief Defines the type of triangle
 */
#include <stdio.h>
#include <math.h>

#define ERROR_RATE 0.000001f
#define EXIT_SUCCESS 0
#define INCORRECT_INPUT 1
#define DEGENERATE_TREANGLE -1
#define OBTUSE_TREANGLE 2
#define ACUTE_TREANGLE 0
#define RIGHT_TREANGLE 1

/**
 * @param[in] point_1_x,point_1_y Coordinates point 1
 * @param[in] point_2_x,point_2_y Coordinates point 2
 * @return Distance from 1 to 2
 * @brief Calculate distance from point 1 to point 2
 */
float calc_distance(float point_1_x, float point_1_y, 
float point_2_x, float point_2_y)
{
    float delta_x, delta_y;
    delta_x = point_1_x - point_2_x;
    delta_y = point_1_y - point_2_y;
    return sqrtf(delta_x * delta_x + delta_y * delta_y);
}

/**
 * @param[in] point_a_x,point_a_y Coordinates point a
 * @param[in] point_b_x,point_b_y Coordinates point b
 * @param[in] point_c_x,point_c_y Coordinates point c
 * @return Treangle type
 * @brief Find type of treangle
 */
int find_treangle_type(float point_a_x, float point_a_y, float point_b_x, 
float point_b_y, float point_c_x, float point_c_y)
{
    float length_a_b, length_b_c, length_a_c;
    float max_length; 
    float dif_length;

    length_a_b = calc_distance(point_a_x, point_a_y, point_b_x, point_b_y);
    length_b_c = calc_distance(point_b_x, point_b_y, point_c_x, point_c_y);
    length_a_c = calc_distance(point_a_x, point_a_y, point_c_x, point_c_y);
    if (length_a_b > length_b_c)
    {
        if (length_a_b > length_a_c)
        {
            max_length = length_a_b;
        }
        else
        {
            max_length = length_a_c;
        }
    }
    else if (length_b_c > length_a_c)
    {
        max_length = length_b_c;
    }
    else
    {
        max_length = length_a_c;
    }
    
    if (fabsf(2 * max_length - length_a_b - length_b_c - length_a_c) < ERROR_RATE)
    {
        return DEGENERATE_TREANGLE;
    }
    dif_length = 2 * powf(max_length, 2) - powf(length_a_b, 2) - 
        powf(length_b_c, 2) - powf(length_a_c, 2);
    if (fabsf(dif_length) < ERROR_RATE)
    {
        return RIGHT_TREANGLE;
    }
    else if (dif_length > ERROR_RATE)
    {
        return OBTUSE_TREANGLE;
    }
    else
    {
        return ACUTE_TREANGLE;
    }
}

int main(void)
{
    float point_a_x, point_a_y;
    float point_b_x, point_b_y;
    float point_c_x, point_c_y;
    int treangle_type;

    printf("Enter coordinate a: ");
    if (scanf("%f %f", &point_a_x, &point_a_y) < 2)
    {
        printf("Wrong coordinate a\n");
        return INCORRECT_INPUT;
    }
    printf("Enter coordinate b: ");
    if (scanf("%f %f", &point_b_x, &point_b_y) < 2)
    {
        printf("Wrong coordinate b\n");
        return INCORRECT_INPUT;
    }
    printf("Enter coordinate c: ");
    if (scanf("%f %f", &point_c_x, &point_c_y) < 2)
    {
        printf("Wrong coordinate c\n");
        return INCORRECT_INPUT;
    }

    treangle_type = find_treangle_type(point_a_x, point_a_y,
    point_b_x, point_b_y, point_c_x, point_c_y);
    if (treangle_type == DEGENERATE_TREANGLE)
    {
        printf("Wrong coordinate a\n");
        return DEGENERATE_TREANGLE;
    }
    printf("Type %d\n", treangle_type);
    return EXIT_SUCCESS;
}

