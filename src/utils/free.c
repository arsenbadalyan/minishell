#include "minishell.h"

char *free_single(char **addr)
{
    if (*addr)
    {
        free(*addr);
        *addr = 0;
    }
    return (0);
}

char *free_double(char ***addr)
{
    int i;

    i = 0;
    if (*addr)
    {
        while ((*addr)[i])
        {
            free((*addr)[i]);
            i++;
        }
        free(*addr);
    }
    return (0);
}
