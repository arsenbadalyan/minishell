/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:16:48 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/20 22:16:50 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		length;
	char		*large;
	char		*small;

	if (!haystack && len == 0)
		return (NULL);
	if (haystack == needle)
		return ((char *)haystack);
	large = (char *)haystack;
	small = (char *)needle;
	i = 0;
	length = ft_strlen(small);
	while (large[i] && (i + length) <= len)
	{
		if (ft_strncmp((large + i), small, length) == 0)
		{
			return (large + i);
		}
		i++;
	}
	return (NULL);
}
