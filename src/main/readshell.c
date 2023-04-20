/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:25:57 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/12 14:45:30 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
void	read_shell(t_minishell *shell)
{
	char	*user_input;
	char	*input_cpy;

	user_input = NULL;
	while (1)
	{
		user_input = readline(SHELL_NAME);
		// printf("%s\n", user_input);
		if(!user_input)
		{
			// sleep(100);
			return;
		}
		input_cpy = user_input;
		while (*input_cpy == ' ')
			input_cpy++;
		if (!ft_strlen(input_cpy) && !free_single((void *)(&user_input)))
			continue ;
		add_history(user_input);
		controller(shell, user_input);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}
