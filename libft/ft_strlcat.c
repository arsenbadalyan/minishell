/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:12:03 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/20 22:12:15 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i1;
	size_t	i2;
	size_t	j;
	size_t	g;

	i1 = 0;
	i2 = 0;
	g = 0;
	if (!dest && size == 0)
		return (0);
	while (dest[i1] != '\0')
		++i1;
	while (src[i2] != '\0')
		++i2;
	if (size == 0 || size <= i1)
		return (i2 + size);
	j = i1;
	while (g < size - i1 - 1 && src[g] != '\0')
	{
		dest[j] = src[g];
		++j;
		++g;
	}
	dest[j] = '\0';
	return (i1 + i2);
}
