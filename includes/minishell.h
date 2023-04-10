/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:07:24 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/07 23:20:04 by arsbadal         ###   ########.fr       */
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

// Parse Checkers
int check_cmd_line(char *line, int sg_quote, int db_quote);
int check_ph(char *line, size_t index, int *parenthesis);
int check_before_ph(char *line, int index, char c);
int check_meta_s(char *line, size_t *sym_counter, int *index);
size_t check_syntax(char *line, int index);

// Line parse
void start_parse_cmds(char *line, int sg_quote, int db_quote);
void cut_part(char *line, char ***cmds, int *xyz);
int get_cmds_size(char *line, int sg_quote, int db_quote);

// Controllers
int controller(t_minishell *shell, char *user_input);
void	here_doc_controller(t_minishell *shell, char *cmd_line);
int	quote_controller(char *line);

// here_doc execution (<<)
int	execute_heredoc(t_minishell *shell, char *cmd_line, size_t index);
void exe_here_doc(t_minishell *shell, char *limiter);
void	wait_limiter(char *limiter, int fd);
void  remove_heredoc(int here_doc_num);

// Utils
int check_slice(char *line, char *SINGLE, char *DOUBLE);
void	*free_single(void **addr);
void	*free_double(void ***addr);
size_t	get_2d_array_length(void **array);

// Local ENV management
char			**is_valid_variable(char *exec_line);
void			add_new_local(t_minishell *shell, char **exec_line);
t_local_env		*fd_md_lvar(t_local_env *head, char *key, char *value, int is_find);
// env controller
void            env_controller(t_minishell *shell, char **envp);
char			**env_dup(char **env);
char			*get_env(t_minishell *shell, char *var);
void			set_env(t_minishell *shell, char *var, char *value);
void			set_new_env(t_minishell *shell, char *var, char *value);

// Error management
void	force_quit(int errno);
int	write_exception(int errno, char *addn, char *addn2, int is_exit);
char *get_custom_error(int errno);

// TRUE and FALSE
enum boolean {
    TRUE = 1,
    FALSE = 0
};

enum errors {
    ENOMEM = 12,
    EPDEN = 13,
    ECMDNF = 127,
};

#endif