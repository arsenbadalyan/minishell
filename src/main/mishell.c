/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mishell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:42:02 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/15 21:50:16 by armartir         ###   ########.fr       */
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

	mini_exit(shell, ft_split("exit -12030", ' '));

	// _export(shell, ft_split("export  a+= a+= adfa= adffasdflkj asdf=assdfa", ' '));
	// _export(shell, ft_split("export", ' '));
	// _unset(shell, ft_split("unset  a TMPDIR __CF_USER_TEXT_ENCODING HOME SHELL", ' '));
	// _env(shell, 0);
	// read_shell(shell);
	// printf("%s\n", get_env(shell, "path"));
	// TODO DELETE IN END V
	// here_doc_controller("<< 'hello'\"");
	// exe_here_doc(NULL, 1);
	// printf ("*rc: %s\n",wildcard("*rc"));
	// printf ("mi*: %s\n",wildcard("mi*"));
	// printf ("i*: %s\n",wildcard("i*"));
	// printf ("*: %s\n",wildcard("*"));
	// printf ("ba*b*: %s\n",wildcard("ba*b*"));
	// printf ("****: %s\n",wildcard("*****"));
	// printf (".*: %s\n",wildcard(".*"));
	return (shell->exit_code);
}
