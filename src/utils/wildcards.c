/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:45:14 by armartir          #+#    #+#             */
/*   Updated: 2023/04/15 20:41:29 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_utils(char *str, char *pattern, char *star, char *tmp)
{
	while (*str)
	{
		if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else if (*pattern == '*')
		{
			star = pattern++;
			tmp = str;
		}
		else if (star)
		{
			pattern = star + 1;
			str = ++tmp;
		}
		else
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

int	match(char *str, char *pattern)
{
	char	*star;
	char	*tmp;

	star = NULL;
	tmp = NULL;
	if ((str[0] == '.' && pattern[0] != '.'))
		return (0);
	return (match_utils(str, pattern, star, tmp));
}

char	*get_suitable(char *suit, char *d_name)
{
	char	*tmp;
	char	*tmp_1;

	if (!suit)
		return (ft_strdup(d_name));
	tmp = ft_strjoin(suit, " ");
	if (!tmp)
		force_quit(12);
	tmp_1 = ft_strjoin(tmp, d_name);
	if (!tmp_1)
		force_quit(12);
	free_single((void *)&tmp);
	return (tmp_1);
}

char	*wildcard(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*suitable;
	char			*tmp;

	dir = opendir(".");
	entry = readdir(dir);
	suitable = 0;
	while (entry != NULL)
	{
		if (match(entry->d_name, pattern))
		{
			tmp = get_suitable(suitable, entry->d_name);
			if (!tmp)
				force_quit(12);
			if (suitable)
				free_single((void *)&suitable);
			suitable = ft_strdup(tmp);
			free_single((void *)&tmp);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (suitable);
}
