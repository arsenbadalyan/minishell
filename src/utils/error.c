#include "minishell.h"

void force_quit(int errno)
{
    char *error;

    error = strerror(errno);
    printf("minishell: %s\n", error);
    exit(errno);
}