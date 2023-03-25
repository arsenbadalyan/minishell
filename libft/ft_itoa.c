/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:06:22 by arsbadal          #+#    #+#             */
/*   Updated: 2023/01/20 22:06:24 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_num_length(int n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n >= 1 || n <= -1)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*allocate_memory_for_number(int n, int num_length)
{
	char	*str;

	if (n < 0)
		num_length++;
	str = (char *)malloc((sizeof(char) * num_length + 1));
	if (!str)
		return (NULL);
	return (str);
}

int	get_power(int num, int power)
{
	int	answer;

	answer = 1;
	while (--power)
		answer *= num;
	return (answer);
}

char	*ft_itoa(int n)
{
	char			*str_number;
	int				num_length;
	int				number_index;
	unsigned int	num;
	unsigned int	answer;

	number_index = -1;
	num_length = get_num_length(n);
	str_number = allocate_memory_for_number(n, num_length);
	if (!str_number)
		return (NULL);
	num = (unsigned int)n;
	if (n < 0)
	{
		num = (unsigned int)n * -1;
		str_number[++number_index] = '-';
	}
	while (num_length)
	{
		answer = num / get_power(10, num_length);
		str_number[++number_index] = answer + 48;
		num -= answer * get_power(10, num_length--);
	}
	str_number[++number_index] = '\0';
	return (str_number);
}
