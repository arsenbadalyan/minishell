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
	// read_shell(shell);

	_export(shell, ft_split("export 1a=", ' '));
	
	// char *term_type = getenv("TERM");
	// printf("%s\n", term_type);
	// char buf[1024];
	// tgetent(buf, term_type);
	// printf("%s\n", );
	// char *tt = tgetstr("cl", NULL);
	// tputs(tt, 1, ft_putchar_fd);
	// if (tgetent(NULL, term_type) != 1)
	// {
	// 	fprintf(stderr, "failed to load terminal database\n");
	// 	return 1;
	// }
	
	// char *clear = tgetstr("cl", NULL);
	// char *move = tgoto(tgetstr("cm", NULL), 0, 0);
	// fputs(clear, stdout);
	// fputs(move, stdout);
	// // TODO DELETE IN END V
	// here_doc_controller("<< 'hello'\"");
	// exe_here_doc(NULL, 1);

	return (1);
}
