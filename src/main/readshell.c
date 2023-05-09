/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:25:57 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/23 03:09:47 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_shell(t_minishell *shell, char *user_input, char *input_cpy)
{
	struct termios	conf;

	shell->execute->heredoc_in = get_heredoc_count(shell);
	shell->execute->heredoc_out = shell->execute->heredoc_in;
	tcgetattr(shell->execute->std_in, &conf);
	rl_catch_signals = 0;
	while (1)
	{
		tcsetattr(shell->execute->std_in, TCSANOW, &conf);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		user_input = readline(SHELL_NAME);
		if (!user_input)
			return ;
		input_cpy = user_input;
		while (*input_cpy == ' ')
			input_cpy++;
		if (!ft_strlen(input_cpy) && !free_single((void *)(&user_input)))
			continue ;
		add_history(user_input);
		shell->execute->heredoc_skip = shell->execute->heredoc_in;
		shell->exit_code = controller(shell, user_input);
		g_exit_code = shell->exit_code;
		remove_heredoc(shell);
	}
}
