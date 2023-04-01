/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:25:57 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/01 12:36:44 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void read_shell(t_minishell *shell)
{
	char *user_input;

	while(1)
	{
		user_input = readline(SHELL_NAME);
		if(!ft_strlen(user_input))
			continue;
		add_history(user_input);
		
		free_single((void *)(&user_input));
	}
}