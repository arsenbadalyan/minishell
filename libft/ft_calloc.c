/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:04:21 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/20 22:04:24 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memptr;

	if (size == SIZE_MAX || count == SIZE_MAX)
		return (NULL);
	memptr = (void *)malloc(count * size);
	if (!memptr)
		return ((void *)0);
	ft_bzero(memptr, count * size);
	return (memptr);
}
