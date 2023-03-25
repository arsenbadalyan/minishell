/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:25:04 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/20 22:25:06 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	size_t	real_len;
	char	*str;

	if (!s)
		return (NULL);
	real_len = ft_strlen(s);
	if (start > real_len)
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
