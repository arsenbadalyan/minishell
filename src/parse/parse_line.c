/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:23:49 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 21:23:49 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**start_parse_cmds(char *line, int sg_quote, int db_quote)
{
	int		xyz[3];
	char	**cmds;

	ft_bzero((void *)xyz, sizeof(int) * 3);
	cmds = malloc(sizeof(char *) * get_cmds_size(line, 0, 0) + 1);
	while (line[xyz[0]])
	{
		quote_check(&sg_quote, &db_quote, line[xyz[0]]);
		if ((sg_quote || db_quote) && ++xyz[0])
			continue ;
		cut_part(line, &cmds, xyz);
	}
	cmds[xyz[2]] = NULL;
	return (cmds);
}

void	cut_part(char *line, char ***cmds, int *xyz)
{
	int	slice_size;

	slice_size = check_slice((line + xyz[0]), PARSE_SEP_SINGLE,
			PARSE_SEP_DOUBLE);
	if (slice_size)
	{
		if (xyz[0] != xyz[1])
			(*cmds)[xyz[2]++] = ft_substr(line, xyz[1], xyz[0] - xyz[1]);
		(*cmds)[xyz[2]++] = ft_substr(line, xyz[0], slice_size);
		xyz[0] += slice_size;
		xyz[1] = xyz[0];
		while (line[xyz[0]] && ft_strchr(WHITE_SPACE, line[xyz[0]]))
		{
			xyz[0]++;
			xyz[1]++;
		}
	}
	else if (!line[xyz[0] + 1])
		(*cmds)[xyz[2]++] = ft_substr(line, xyz[1], (xyz[0]++) + 1);
	else
		xyz[0]++;
}

int	get_cmds_size(char *line, int sg_quote, int db_quote)
{
	size_t	i;
	size_t	size;
	int		slice_size;
	int		temp_slice_size;

	size = 0;
	i = 0;
	slice_size = 0;
	while (line[i])
	{
		quote_check(&sg_quote, &db_quote, line[i]);
		if ((sg_quote || db_quote || ft_strchr(WHITE_SPACE, line[i])) && ++i)
			continue ;
		temp_slice_size = slice_size;
		slice_size = check_slice((line + i), PARSE_SEP_SINGLE,
				PARSE_SEP_DOUBLE);
		if (temp_slice_size && !slice_size)
			size++;
		if (slice_size && size++)
			i += slice_size;
		else
			i++;
	}
	return (size);
}
