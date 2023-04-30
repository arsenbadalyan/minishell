/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:42:43 by armartir          #+#    #+#             */
/*   Updated: 2023/04/02 21:49:36 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void handle_heredoc_exit_code()
{
	write(1, "\n", 1);
	exit(1);
}

int heredoc_process_control(t_minishell *shell, char *cmd_line)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		here_doc_controller(shell, shell->user_input);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &shell->status, 0);
	}
	shell->status = WEXITSTATUS(shell->status);
	return (shell->status);
}

void	here_doc_controller(t_minishell *shell, char *cmd_line)
{
	size_t	i;
	int		quotes[2];

	i = 0;
	signal(SIGINT, handle_heredoc_exit_code);
	signal(SIGQUIT, SIG_IGN);
	quotes[0] = 0;
	quotes[1] = 0;
	while (cmd_line[i])
	{
		quote_check(&quotes[0], &quotes[1], cmd_line[i]);
		if ((quotes[0] || quotes[1]) && ++i)
			continue ;
		if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
		{
			i += 2;
			while (cmd_line[i] == ' ')
				i++;
			execute_heredoc(shell, cmd_line, i);
		}
		else
			i++;
	}
	exit (0);
}

int	quote_controller(t_minishell *shell, char *line)
{
	size_t	i;
	int		db_quote;
	int		sg_quote;

	i = 0;
	db_quote = 0;
	sg_quote = 0;
	while (line[i])
	{
		if (!quote_check(&sg_quote, &db_quote, line[i]))
			return (write_exception(shell, 130, 130, "(\') or (\")"));
		i++;
	}
	if (db_quote || sg_quote)
		return (write_exception(shell, 130, 130, "(\') or (\")"));
	return (0);
}
