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

void	remove_heredoc(t_exc_line *execute)
{
	char	*real_name;
	char	*del_num;

	while (execute->HEREDOC_OUT > execute->HEREDOC_IN)
	{
		del_num = ft_itoa(execute->HEREDOC_OUT - 1);
		if (!del_num)
			force_quit(12);
		real_name = ft_strjoin(HERE_DOC, del_num);
		if (!real_name)
			force_quit(12);
		if (access(real_name, X_OK) == -1)
			break ;
		unlink(real_name);
		execute->HEREDOC_OUT--;
		free_single((void *)&real_name);
	}
}
