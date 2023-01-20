#include "../inc/main.h"

int main(void)
{
    int rc;

    char command[MAX_STR_LEN + 1];
    rc = enter_string(command, MAX_STR_LEN + 1);
    if (rc != EXIT_SUCCESS)
        return rc;

    int mode;

    if (!strncmp(command, "out", 3))
        mode = OUT_MODE;
    else if (!strncmp(command, "mul", 3))
        mode = MUL_MODE;
    else if (!strncmp(command, "sqr", 3))
        mode = SQR_MODE;
    else if (!strncmp(command, "div", 3))
        mode = DIV_MODE;
    else
    {
        ERROR_LOG("WRONG MODE");
        return WRONG_MODE;
    }

    rc = process(mode);

    return rc;
}
