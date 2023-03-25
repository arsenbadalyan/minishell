/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:09:39 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/20 22:09:40 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdst;
	char	*csrc;
	int		i;

	if (!dst && !src)
		return (NULL);
	cdst = (char *)dst;
	csrc = (char *)src;
	i = (int)len - 1;
	if (dst > src)
	{
		while (i >= 0)
		{
			*(cdst + i) = *(csrc + i);
			i--;
		}
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
