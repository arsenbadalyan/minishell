/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:42:02 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/19 17:07:50 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;

	if (argc > 1)
		exit(1);
	shell = init_minishell();
	// print_header();
	env_controller(shell, envp);

	// _export(shell, ft_split("export  a+=1 a+=1 a+=12 adfa= adffasdflkj asdf=assdfa", ' '));
	// _export(shell, ft_split("export", ' '));
	// _unset(shell, ft_split("unset  a TMPDIR __CF_USER_TEXT_ENCODING HOME SHELL", ' '));
	// _env(shell, 0);
	read_shell(shell);
	// printf("%s\n", get_env(shell, "path"));
	// TODO DELETE IN END V
	// here_doc_controller("<< 'hello'\"");
	// exe_here_doc(NULL, 1);

	return (shell->exit_code);
}
