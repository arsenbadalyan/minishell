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

// Libs
# include "libft.h"
# include "get_next_line.h"
# include "shell.h"

// Readline
// #include <readline/readline.h>
// #include <readline/history.h>

// C Libs
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

// Here_Doc
int		exe_here_doc(char *limiter, int clean);
void	wait_limiter(char *limiter, int fd);
int		here_doc_unlink(int here_doc_num);
int		here_doc_controller(char *cmd_line);
int		here_doc_params(char *cmd_line, size_t index, int sg_quote, int db_quote);
int		check_parse_error(char *cmd_line, int index);
int		check_par_utils(char* str);

// Defines
# define SHELL_NAME "\033[32mmishell> \033[0m"
# define HERE_DOC ".here_doc"
# define METASYMBOLS_ALL "><|&)( "
# define METASYMBOLS_SPECIAL "><|&)("

// Took input from user
void	read_shell(t_minishell *shell);

// Utils
void	*free_single(void **addr);
void	*free_double(void ***addr);
void	force_quit(int errno);

void quote_controller(char *line);

// ECHO 
char *_echo(char *line, int here_doc_mode);
char *modify_line(char *line, int here_doc_mode, int sg_quote, int db_quote);
int quote_check(int *sg_quote, int *db_quote, char c);

#endif