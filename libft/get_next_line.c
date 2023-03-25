/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:10:29 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/29 16:28:45 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_me(char **addr)
{
	if (*addr)
	{
		free(*addr);
		*addr = 0;
	}
}

char	*free_substr(char *str, unsigned int start, size_t len)
{
	char	*tmp;

	tmp = str;
	str = ft_substr(str, start, len);
	if (tmp)
	{
		free_me(&tmp);
	}
	return (str);
}

char	*alloc_space(char **cache)
{
	char	*n_l;

	if ((*cache))
	{
		n_l = ft_strjoin_gnl(ft_strdup(""), (*cache));
		free_me(cache);
	}
	else
		n_l = ft_strdup("");
	return (n_l);
}

char	*start_read(int fd, char **cache)
{
	char	tmp[BUFFER_SIZE + 1];
	int		readed_res;
	char	*n_l;

	n_l = alloc_space(cache);
	while (1 && n_l)
	{
		readed_res = read(fd, tmp, BUFFER_SIZE);
		if (readed_res <= 0)
			break ;
		tmp[readed_res] = '\0';
		n_l = ft_strjoin_gnl(n_l, tmp);
		if (!n_l)
			return (NULL);
		if (ft_strchr_gnl(n_l, '\n') != -1)
		{
			(*cache) = ft_substr(n_l, ft_strchr_gnl(n_l, '\n') + 1,
					ft_strlen(n_l) + 1);
			n_l = free_substr(n_l, 0, ft_strchr_gnl(n_l, '\n') + 1);
			if (!(*cache) || !n_l)
				return (NULL);
			return (n_l);
		}
	}
	return (n_l);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*next_line;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd < 0)
		return (NULL);
	if (cache && ft_strlen(cache) && ft_strchr_gnl(cache, '\n') != -1)
	{
		next_line = ft_substr(cache, 0, ft_strchr_gnl(cache, '\n') + 1);
		cache = free_substr(cache, ft_strchr_gnl(cache, '\n')
				+ 1, ft_strlen(cache) + 1);
		return (next_line);
	}
	next_line = start_read(fd, &cache);
	if (cache && *cache == '\0')
		free_me(&cache);
	if (next_line && *next_line == '\0')
		free_me(&next_line);
	if (!next_line)
		return (NULL);
	return (next_line);
}
