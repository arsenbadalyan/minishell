/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:11:48 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/20 22:11:50 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		str_index;

	i = -1;
	str_index = -1;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * ft_strlen(s1) + sizeof(char) * ft_strlen(s2)
			+ sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[++str_index] = s1[i];
	i = -1;
	while (s2[++i])
		str[++str_index] = s2[i];
	str[++str_index] = '\0';
	return (str);
}
