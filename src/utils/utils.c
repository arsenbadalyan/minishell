#include "minishell.h"

int check_slice(char *line, char *SINGLE, char *DOUBLE)
{
	if (ft_strchr(DOUBLE, (*line)) && (*line) == *(line + 1))
		return (2);
	else if (ft_strchr(SINGLE, (*line)))
		return (1);
	return (0);
}