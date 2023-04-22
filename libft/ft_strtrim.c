/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:17:06 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/20 22:24:54 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	search_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1)
		return (NULL);
	end = ft_strlen(s1) - 1;
	start = 0;
	while (s1[start] && search_set(s1[start], set))
	{
		start++;
	}
	while (s1[end] && search_set(s1[end], set))
	{
		end--;
	}
	
	str = ft_substr(s1, (unsigned int)start, (end - start + 1));
	if (!str)
		return (NULL);
	return (str);
}
