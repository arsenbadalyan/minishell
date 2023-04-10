/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:42:02 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/10 19:42:04 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;

	if (argc > 1)
		exit(1);

	shell = init_minishell();
	print_header();
	env_controller(shell, envp);

	_export(shell, ft_split("export dsfasdfd qwe= a a=7 ", ' '));
	// _export(shell, ft_split("export", ' '));
	_env(shell, 1);

	// mini_exit(shell, ft_split("exit 255a", ' '));
	// read_shell(shell);
	// printf("%s\n", get_env(shell, "path"));
	// TODO DELETE IN END V
	// here_doc_controller("<< 'hello'\"");
	// exe_here_doc(NULL, 1);
	return (shell->exit_code);
}
