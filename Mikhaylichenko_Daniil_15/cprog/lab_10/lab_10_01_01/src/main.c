#include "../inc/main.h"

int main(int argc, char **argv)
{
    if (argc < MIN_ARGS || argc > MAX_ARGS)
    {
        ERROR_LOG("WRONG NUMBER OF ARGS");
        return WRONG_ARGS;
    }

    int rc = process(argv[1], argv[2]);

    return rc;
}
