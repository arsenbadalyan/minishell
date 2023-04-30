/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:45:14 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 19:00:50 by armartir         ###   ########.fr       */
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

void	modify_wildcard_array(char ***wildcards, char *dirname)
{
	size_t	size;
	char	**new_arr;

	size = 0;
	while ((*wildcards)[size])
		size++;
	new_arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_arr)
		force_quit(ENOMEM);
	new_arr[size] = NULL;
	new_arr[size - 1] = ft_strdup(dirname);
	if (!new_arr[size - 1])
		force_quit(ENOMEM);
	size = 0;
	while ((*wildcards)[size])
	{
		new_arr[size] = (*wildcards)[size];
		size++;
	}
	*wildcards = new_arr;
}

char	**wildcard(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**wildcards;
	char			*dirname;

	dir = opendir(".");
	entry = readdir(dir);
	wildcards = NULL;
	while (entry != NULL)
	{
		if (match(entry->d_name, pattern))
		{
			dirname = ft_strdup(entry->d_name);
			if (!dirname)
				force_quit(ENOMEM);
			wildcards = push_to_double_array(wildcards, dirname);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (wildcards);
}
