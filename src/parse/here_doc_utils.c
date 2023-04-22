/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:07:32 by armartir          #+#    #+#             */
/*   Updated: 2023/04/22 18:07:33 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_heredoc_count(t_minishell *shell)
{
	DIR				*dir;
	struct dirent	*entry;
	int				here_doc_count;

	here_doc_count = 0;
	dir = opendir("/tmp");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, ".minishell_here_doc_", 20) == 0)
			here_doc_count++;
		entry = readdir(dir);
	}
	return (here_doc_count);
}

void	write_variable(t_minishell *shell, char *tmp, int fd)
{
	char	*var;

	while (*tmp)
	{
		if (*tmp == '$' && *(tmp + 1) && tmp++)
		{
			var = ft_strdup("");
			if (!var)
				force_quit(ERNOMEM);
			get_variable(shell, &tmp, &var);
			write(fd, var, ft_strlen(var));
			free_single((void *)&var);
		}
		else
		{
			write(fd, tmp, 1);
			tmp++;
		}
	}
}