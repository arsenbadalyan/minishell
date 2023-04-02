/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:42:02 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/02 15:26:36 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_minishell *shell;

	if(argc > 1)
		exit(1);
		// force_quit(12);
	// here_doc_controller("<< 1<<| 2 3<<4<< 5<<6<< 7<<8   ");
	// exe_here_doc(NULL, 1);
	shell = init_minishell();
	shell->envp = envp;
	read_shell(shell);
	return (0);
}
