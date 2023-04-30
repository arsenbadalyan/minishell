/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsen <arsen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:07:32 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 19:00:04 by arsen            ###   ########.fr       */
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
	if (!dir)
		exit(print_error(shell, "Cannot create temp file for heredoc"));
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!ft_strcmp(entry->d_name, ".minishell_here_doc_"))
			here_doc_count++;
		entry = readdir(dir);
	}
	closedir(dir);
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

void	remove_heredoc(t_minishell *shell)
{
	char	*real_name;
	char	*del_num;

	while (shell->execute->HEREDOC_OUT > shell->execute->HEREDOC_IN)
	{
		shell->execute->HEREDOC_OUT--;
		del_num = ft_itoa(shell->execute->HEREDOC_OUT);
		if (!del_num)
			force_quit(ENOMEM);
		real_name = ft_strjoin(HERE_DOC, del_num);
		free_single((void *)&del_num);
		if (!real_name)
			force_quit(ENOMEM);
		unlink(real_name);
		free_single((void *)&real_name);
	}
}
