/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:42:02 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/02 22:00:16 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_minishell *shell;

	if(argc > 1)
		exit(1);
	// shell = init_minishell();
	// print_header();
	// shell->envp = envp;
	// read_shell(shell);
	_pwd();
	// TODO DELETE IN END V
	// quote_controller("<< 'hello'\"");
	// here_doc_controller("<< 'hello'\"");
	// exe_here_doc(NULL, 1);
	return (0);
}
