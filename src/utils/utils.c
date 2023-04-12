/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:13:01 by armartir          #+#    #+#             */
/*   Updated: 2023/04/12 16:33:08 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_2d_array_length(void **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

int	check_slice(char *line, char *SINGLE, char *DOUBLE)
{
	if (ft_strchr(DOUBLE, (*line)) && (*line) == *(line + 1))
		return (2);
	else if (ft_strchr(SINGLE, (*line)))
		return (1);
	return (0);
}

int	check_valid(char *cmd)
{
	if (ft_strchr(cmd, '+') || ft_strchr(cmd, '-')
		|| ft_strchr(cmd, '/') || ft_strchr(cmd, '*'))
	{
		write_exception(131, cmd, 0, 0);
		return (1);
	}
	return (0);
}
