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

void	read_shell(t_minishell *shell)
{
	char			*user_input;
	char			*input_cpy;
	struct termios	conf;

	user_input = NULL;
	shell->execute->HEREDOC_IN = get_heredoc_count(shell);
	shell->execute->HEREDOC_OUT = shell->execute->HEREDOC_IN;
	tcgetattr(shell->execute->STDIN, &conf);
	rl_catch_signals = 0;
	while (1)
	{
		tcsetattr(shell->execute->STDIN, TCSANOW, &conf);
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
		shell->execute->HEREDOC_SKIP = shell->execute->HEREDOC_IN;
		controller(shell, user_input);
		remove_heredoc(shell);
	}
}
