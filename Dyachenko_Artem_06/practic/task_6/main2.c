#include <stdio.h>

struct man
{
    unsigned int age;
    float height;
    double weight;
    char name[6];
};

int main(void)
{
    struct man a = {.age = 33, .weight = 77.23, .height = 177.4, .name = "Andrew"};
}
