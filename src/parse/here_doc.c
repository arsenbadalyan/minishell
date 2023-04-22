/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:17:22 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/02 21:52:36 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int execute_heredoc(t_minishell *shell, char *cmd_line, size_t index)
{
	size_t temp_index;
	char *limiter;
	char *temp_limiter;
	int quotes[2];

	temp_index = index;
	quotes[0] = 0;
	quotes[1] = 0;
	while (cmd_line[index])
	{
		quote_check(&quotes[0], &quotes[1], cmd_line[index]);
		if ((quotes[0] || quotes[1]) && ++index)
			continue;
		if ((cmd_line[index] == '&' && cmd_line[index] == cmd_line[index + 1])
			|| (ft_strchr(METASYMBOLS_ALL, cmd_line[index]) && cmd_line[index] != '&')
			|| !(++index))
			break;
	}
	limiter = ft_substr(cmd_line, temp_index, index - temp_index);
	if (!limiter)
		force_quit(ERNOMEM);
	temp_limiter = limiter;
	limiter = _echo(shell, NULL, TRUE, limiter);
	free_single((void *)&temp_limiter);
	exe_here_doc(shell, limiter);
	free_single((void *)&limiter);
	return (0);
}

void exe_here_doc(t_minishell *shell, char *limiter)
{
	int fd;
	char *real_name;
	char *tmp;

	tmp = ft_itoa(shell->execute->heredoc_sum++);
	if (!tmp)
		force_quit(ERNOMEM);
	real_name = ft_strjoin(HERE_DOC, tmp);
	free_single((void *)&tmp);
	if (!real_name)
		force_quit(ERNOMEM);
	fd = open(real_name, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	free_single((void *)&real_name);
	wait_limiter(shell, limiter, fd);
	close(fd);
}

void	wait_limiter(t_minishell *shell, char *limiter, int fd)
{
	char	*buf;
	char	*tmp;
	int		i;

	i = 0;
	while (1)
	{
		buf = readline(">");
		if (!buf)
			force_quit(12);
		tmp = ft_strdup(buf);
		if (!tmp)
			force_quit(ERNOMEM);
		if (!ft_strcmp(buf, limiter))
		{
			free_single((void *)&buf);
			return ;
		}
		write_variable(shell, tmp, fd);
		free_single((void *)&buf);
		free_single((void *)&tmp);
		write(fd, "\n", 1);
	}
}

void remove_heredoc(int here_doc_num)
{
	char	*real_name;
	char	*del_num;

	while (here_doc_num >= 0)
	{
		del_num = ft_itoa(here_doc_num);
		if(!del_num)
			force_quit(12);
		real_name = ft_strjoin(HERE_DOC, del_num);
		if (!real_name)
			force_quit(12);
		unlink(real_name);
		here_doc_num--;
	}
}

char *concat_heredoc(t_exc_line *exec)
{
	int current_state;
	char *str_cur_state;
	char *concat;

	current_state = exec->current_hd_state;
	str_cur_state = ft_itoa(current_state);
	if(!str_cur_state)
		force_quit(ERNOMEM);
	concat = ft_strjoin(HERE_DOC, str_cur_state);
	if(!free_single((void *)&str_cur_state) && !concat)
		force_quit(ERNOMEM);
	return (concat);
}