/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:17:03 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/20 22:11:05 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	count_allocate_size(const char *s, char c)
{
	size_t	allocated_size;
	size_t	i;

	i = 0;
	allocated_size = 1;
	while (s[i])
	{
		if (s[i] != c)
		{
			allocated_size++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (allocated_size);
}

void	free_mem(char **str, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		free (str[i]);
		i++;
	}
	free(str);
}

int	allc_or_free(const char *s, char **str, size_t s_i, int indexes[])
{
	size_t	current_index;
	size_t	meter;
	size_t	j;

	current_index = indexes[0];
	meter = indexes[1];
	j = 0;
	str[current_index] = (char *)malloc(sizeof(char) * (meter + 1));
	if (!str[current_index])
	{
		s_i = 0;
		free_mem(str, indexes[2]);
		return (-1);
	}
	while (j < meter)
	{
		str[current_index][j] = s[s_i++];
		j++;
	}
	str[current_index][j++] = '\0';
	return ((int)meter);
}

void	allocate_split(const char *s, char **str, char c, size_t allocated_size)
{
	size_t	i;
	int		counter_and_meter[3];

	i = 0;
	counter_and_meter[0] = 0;
	counter_and_meter[2] = allocated_size;
	while (s[i])
	{
		counter_and_meter[1] = 0;
		if (s[i] != c)
		{
			while (s[i + counter_and_meter[1]]
				&& s[i + counter_and_meter[1]] != c)
				counter_and_meter[1]++;
			counter_and_meter[1] = allc_or_free(s, str, i, counter_and_meter);
			counter_and_meter[0]++;
			i += counter_and_meter[1];
		}
		else
			i++;
	}
}

char	**ft_split(const char *s, char c)
{
	char	**splited_str;
	size_t	allocated_size;

	if (!s)
		return (NULL);
	allocated_size = count_allocate_size((char *)s, c);
	splited_str = (char **)malloc(sizeof(char *) * allocated_size);
	if (!splited_str)
		return (NULL);
	allocate_split(s, splited_str, c, allocated_size);
	splited_str[allocated_size - 1] = NULL;
	return (splited_str);
}
