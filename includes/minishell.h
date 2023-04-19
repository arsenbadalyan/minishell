/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:07:24 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/19 16:37:51 by armartir         ###   ########.fr       */
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
# include <dirent.h>
# include <signal.h>

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
void	print_header(void);

// Work with readline
void	read_shell(t_minishell *shell);

// Parse Checkers
int		check_cmd_line(char *line, int sg_quote, int db_quote);
int		check_ph(char *line, size_t index, int *parenthesis);
int		check_before_ph(char *line, int index, char c);
int		check_meta_s(char *line, size_t *sym_counter, int *index);
size_t	check_syntax(char *line, int index);

// Line parse
void	start_parse_cmds(char *line, int sg_quote, int db_quote);
void	cut_part(char *line, char **cmds, int *xyz);
int		get_cmds_size(char *line, int sg_quote, int db_quote);

// Controllers
int		controller(t_minishell *shell, char *user_input);
int		here_doc_controller(char *cmd_line);
int		quote_controller(char *line);

// here_doc execution (<<)
int		exe_here_doc(char *limiter, int clean);
void	wait_limiter(char *limiter, int fd);
int		here_doc_unlink(int here_doc_num);
int		here_doc_params(char *cmd_line, size_t index, int sg_quote, int db_quote);
int		check_parse_error(char *cmd_line, int index);

// Utils
int		check_slice(char *line, char *SINGLE, char *DOUBLE);
void	*free_single(void **addr);
void	*free_double(void ***addr);
size_t	get_2d_array_length(void **array);
int		check_valid(char *cmd);

// Local ENV management
char			**is_valid_variable(char *exec_line);
void			add_new_local(t_minishell *shell, char **exec_line);
t_local_env		*fd_md_lvar(t_local_env *head, char *key, char *value, int is_find);
// env controller
char			**env_dup(char **env);
void            env_controller(t_minishell *shell, char **envp);
char			*get_env(t_minishell *shell, char *var);
void			set_env(t_minishell *shell, char *var, char *value, int add);
void			set_new_env(t_minishell *shell, char *var, char *value, int add);

// Error management
void	force_quit(int errno);
int	write_exception(int errno, char *addn, char *addn2, int is_exit);
char *get_custom_error(int errno);

// Wildcard
char	*wildcard(char *pattern);
int		match(char *str, char *pattern);
char	*get_suitable(char *suit, char *d_name);
int		match_utils(char *str, char *pattern, char *star, char *tmp);

#endif