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
	while (1)
	{
		// printf("PID:%d\n",getpid());
		// tcgetattr(shell->execute->STDIN, &conf);
		rl_catch_signals = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		// tcsetattr(shell->execute->STDIN, TCSANOW, &conf);
		user_input = readline(SHELL_NAME);
		// printf("User_input: %s\n", user_input);
		if (!user_input)
			return ;
		input_cpy = user_input;
		while (*input_cpy == ' ')
			input_cpy++;
		if (!ft_strlen(input_cpy) && !free_single((void *)(&user_input)))
			continue ;
		add_history(user_input);
		controller(shell, user_input);
	}
}
