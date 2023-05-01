/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:58:21 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 19:09:11 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_heredoc_sum(t_minishell *shell, char *str)
{
	size_t	i;
	size_t	sum;
	int		quotes[2];

	ft_bzero((void *)quotes, sizeof(int) * 2);
	i = 0;
	sum = 0;
	while (str[i])
	{
		quote_check(&quotes[0], &quotes[1], str[i]);
		if ((quotes[0] || quotes[1]) && ++i)
			continue ;
		if (str[i] == '<' && str[i] == str[i + 1])
			sum++;
		i++;
	}
	if (sum)
	{
		i = sum;
		sum = shell->execute->heredoc_skip;
		shell->execute->heredoc_skip += i;
	}
	return (sum);
}

int	one_char_exception(t_minishell *shell, int errno_c, int exit_code, char c)
{
	char	str[2];

	ft_bzero((void *)str, sizeof(char) * 2);
	str[0] = c;
	return (write_exception(shell, errno_c, exit_code, str));
}
