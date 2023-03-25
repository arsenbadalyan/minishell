/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:16:58 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/20 22:17:00 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int ch)
{
	int	i;
	int	pos;

	i = -1;
	pos = -1;
	while (str[++i])
		if ((unsigned char)str[i] == (unsigned char)ch)
			pos = i;
	if (ch == 0)
		pos = i;
	if (pos != -1)
		return ((char *)(str + pos));
	return (0);
}
