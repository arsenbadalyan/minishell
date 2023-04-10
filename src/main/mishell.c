/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:42:02 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/08 19:48:35 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
int main(int argc, char **argv, char **envp)
{
	t_minishell *shell;

	if(argc > 1)
		exit(1);		
	shell = init_minishell();
	print_header();
	env_controller(shell, envp);
	read_shell(shell);
	// TODO DELETE IN END V
	// here_doc_controller("<< 'hello'\"");
	// exe_here_doc(NULL, 1);
	return (0);
}
