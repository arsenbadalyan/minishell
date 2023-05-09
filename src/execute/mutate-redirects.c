/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutate-redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:24:05 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 21:31:36 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mutate_redirects(t_minishell *shell, t_token *token, char ***redirects)
{
	size_t	i;
	char	*temp;

	i = 0;
	while ((*redirects)[i])
	{
		temp = (*redirects)[i];
		(*redirects)[i] = ft_strtrim((*redirects)[i], WHITE_SPACE);
		if (!free_single((void *)&temp) && !(*redirects)[i])
			force_quit(ENOMEM);
		if (redirect_manipulation(shell, token, &(*redirects)[i]))
		{
			if (token->stdin != -1)
				close(token->stdin);
			if (token->stdout != -1)
				close(token->stdout);
			return ;
		}
		i++;
	}
}

int	redirect_manipulation(t_minishell *shell, t_token *token, char **redirect)
{
	size_t	skip;
	int		type;
	int		quotes[2];
	char	*temp;

	ft_bzero((void *)quotes, sizeof(int) * 2);
	skip = get_redirect_type(&(*redirect), &type);
	temp = (*redirect);
	if (type == RDR_HERE_DOC)
		(*redirect) = modify_line(shell, (*redirect), TRUE, quotes);
	else
		(*redirect) = modify_line(shell, (*redirect), FALSE, quotes);
	free_single((void *)&temp);
	if (type == RDR_HERE_DOC
		&& stdio_mutate(shell, token, (*redirect) + skip, type))
		return (shell->status);
	if (open_redirect_wildcards(shell, redirect, skip))
		return (shell->status);
	if (ft_strchr(REDIRECTS, (*redirect)[0]))
		stdio_mutate(shell, token, (*redirect) + skip, type);
	else
		stdio_mutate(shell, token, (*redirect), type);
	return (shell->status);
}

size_t	get_redirect_type(char **redirect, int *type)
{
	size_t	i;

	i = 0;
	if ((*redirect)[0] == '<' && (*redirect)[0] == (*redirect)[1] && ++i && ++i)
		*type = RDR_HERE_DOC;
	else if ((*redirect)[0] == '<' && ++i)
		*type = RDR_INPUT;
	else if ((*redirect)[0] == '>' && (*redirect)[0] == (*redirect)[1]
		&& ++i && ++i)
		*type = RDR_APPEND;
	else if ((*redirect)[0] == '>' && ++i)
		*type = RDR_OUTPUT;
	while ((*redirect)[i] && ft_strchr(WHITE_SPACE, (*redirect)[i]))
		i++;
	return (i);
}

int	open_redirect_wildcards(t_minishell *shell, char **redirect, int skip)
{
	char	**wildcards;
	size_t	wildcard_size;
	char	*pattern;

	pattern = (*redirect + skip);
	wildcards = wildcard(pattern);
	if (!wildcards)
		return (0);
	wildcard_size = get_2d_array_length((void **)wildcards);
	if (!wildcard_size && !free_double((void *)&wildcards))
		return (0);
	if (wildcard_size > 1 && !free_double((void *)&wildcards))
		return (write_exception(shell, EAMBGRDR, EXIT_FAILURE, pattern));
	free_single((void *)&(*redirect));
	(*redirect) = wildcards[0];
	free(wildcards);
	return (0);
}
