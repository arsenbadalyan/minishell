/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:17:22 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/02 15:31:43 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	wait_limiter(char *limiter, int fd)
{
	char	*buf;

	while (1)
	{
		buf = readline(">");
		if (!buf)
			force_quit(12);
		if (!(ft_strncmp(buf, limiter, ft_strlen(limiter) + 1)))
		{
			free_single((void *)&buf);
			return ;
		}
		else
			write(fd, buf, ft_strlen(buf));
		free_single((void *)&buf);
		write(fd, "\n", 1);
	}
}

int	here_doc_unlink(int here_doc_num)
{
	char	*real_name;

	while (here_doc_num != -1)
	{
		real_name = ft_strjoin(HERE_DOC, ft_itoa(here_doc_num));
		if (!real_name)
			force_quit(12);
		unlink(real_name);
		here_doc_num -= 1;
	}
	return (here_doc_num);
}

int	exe_here_doc(char *limiter, int clean)
{
	static int	here_doc_num;
	int			fd;
	char		*real_name;
	char		*tmp;

	if (clean)
		return (here_doc_unlink(here_doc_num));
	else
	{
		tmp = ft_itoa(here_doc_num);
		real_name = ft_strjoin(HERE_DOC, tmp);
		free_single((void *)&tmp);
		if (!real_name)
			force_quit(12);
		fd = open(real_name, O_WRONLY | O_CREAT | O_TRUNC, 0755);
		wait_limiter(limiter, fd);
		close(fd);
		fd = open(real_name, O_RDONLY);
		free_single((void *)&real_name);
		here_doc_num++;
		return (fd);
	}
}

int	check_parse_error(char *cmd_line, int index)
{
	if ((cmd_line[index] == '<') || (cmd_line[index] == '>')
		|| (cmd_line[index] == '|') || (cmd_line[index] == '&'))
	{
		write (1, "zsh: parse error near `", 23);
		write (1, &cmd_line[index], 1);
		if ((cmd_line[index] == '<' && cmd_line[index + 1] == '<')
			|| (cmd_line[index] == '>' && cmd_line[index + 1] == '>')
			|| (cmd_line[index] == '|' && cmd_line[index + 1] == '|')
			|| (cmd_line[index] == '&' && cmd_line[index + 1] == '&'))
			write (1, &cmd_line[index], 1);
		write (1, "'\n", 2);
		return (1);
	}
	return (0);
}

int	here_doc_params(char *cmd_line, int index)
{
	int		tmp;
	int		i;
	char	*limiter;

	i = 0;
	while (cmd_line[index] == ' ')
		index++;
	tmp = index;
	if (check_parse_error(cmd_line, index))
		return (1);
	while (!(cmd_line[tmp] == ' ' || cmd_line[tmp] == '|'
			|| cmd_line[tmp] == '&' || cmd_line[tmp] == '<'
			|| cmd_line[tmp] == '>' || cmd_line[tmp] == '\0'))
		tmp++;
	limiter = (char *)malloc(sizeof(char) * (tmp - index + 1));
	if (!limiter)
		force_quit(12);
	while (!(cmd_line[index] == ' ' || cmd_line[index] == '|'
			|| cmd_line[index] == '&' || cmd_line[index] == '<'
			|| cmd_line[index] == '>' || cmd_line[index] == '\0'))
		limiter[i++] = cmd_line[index++];
	limiter[i] = '\0';
	printf ("limiter: %s\n", limiter);
	exe_here_doc(limiter, 0);
	free_single((void *)&limiter);
	return (0);
}

int	here_doc_controller(char *cmd_line)
{
	int	par_num;
	int	i;

	i = 0;
	par_num = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '(')
			par_num++;
		else if (cmd_line[i] == ')')
			par_num--;
		if (par_num < 0)
		// TODO: add parentheses error
			write(1, "parentheses error\n", 18);
		if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
			if (here_doc_params(cmd_line, i + 2))
				return (1);
		i++;
	}
	if (par_num != 0)
		write(1, "parentheses error\n", 18);
	return (0);
}
