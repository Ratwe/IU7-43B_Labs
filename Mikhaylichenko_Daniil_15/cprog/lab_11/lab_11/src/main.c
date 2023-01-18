#include "../inc/main.h"

int main(void)
{
    char str[100 + 1], my_str[100 + 1];

    short int data = SHRT_MAX;

    int len = snprintf(str, 100 + 1, "%hd", data);
    int my_len = my_snprintf(my_str, 100 + 1, "%hd", data);

    printf("snprintf <%s>: %d\n", str, len);
    printf("my_snprintf <%s>: %d\n", my_str, my_len);

    return EXIT_SUCCESS;
}
