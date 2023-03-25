/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:10:43 by arsbadal          #+#    #+#             */
/*   Updated: 2023/03/08 13:54:37 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || (s && !*s))
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		str_index;

	i = -1;
	str_index = -1;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[++str_index] = s1[i];
	i = -1;
	while (s2[++i])
		str[++str_index] = s2[i];
	str[++str_index] = '\0';
	if (s1)
		free(s1);
	return (str);
}

int	ft_strchr_gnl(const char *str, int ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)ch)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr_str;

	i = -1;
	ptr_str = (char *)malloc((sizeof(char) * (ft_strlen(s1) + 1)));
	if (!ptr_str)
		return ((void *)0);
	while (s1[++i])
		ptr_str[i] = s1[i];
	ptr_str[i] = '\0';
	return (ptr_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	size_t	real_len;
	char	*str;

	if (!s)
		return (NULL);
	real_len = ft_strlen(s);
	if (start >= real_len)
		return (ft_strdup(""));
	if (len > real_len)
		len = real_len;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	index = 0;
	while (index < len)
	{
		str[index] = s[start + index];
		index++;
	}
	str[index] = '\0';
	return (str);
}
