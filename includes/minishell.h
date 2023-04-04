/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:07:24 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/02 21:58:18 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// C Libs
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

// Custom Libs
# include "libft.h"
# include "get_next_line.h"
# include "shell.h"
# include "defines.h"
# include "built_in.h"

// Readline
// #include <readline/readline.h>
// #include <readline/history.h>

// Printf Minishell header on start
void print_header();

// Work with readline
void	read_shell(t_minishell *shell);

// Controllers
int		here_doc_controller(char *cmd_line);
void	quote_controller(char *line);

// here_doc execution (<<)
int		exe_here_doc(char *limiter, int clean);
void	wait_limiter(char *limiter, int fd);
int		here_doc_unlink(int here_doc_num);
int		here_doc_params(char *cmd_line, size_t index, int sg_quote, int db_quote);
int		check_parse_error(char *cmd_line, int index);

// Utils
void	*free_single(void **addr);
void	*free_double(void ***addr);

// Local ENV management
char **is_valid_variable(char *exec_line);
void add_new_local(t_minishell *shell, char **exec_line);
t_local_env *fd_md_lvar(t_local_env *head, char *key, char *value, int is_find);

// Error management
void	force_quit(int errno);
void	write_exception(int errno, char *addn, char *addn2, int is_exit);
char *get_custom_error(int errno);

#endif