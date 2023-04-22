/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:07:24 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/23 03:12:16 by armartir         ###   ########.fr       */
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
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

// Custom Libs
# include "libft.h"
# include "get_next_line.h"
# include "shell.h"
# include "defines.h"
# include "built_in.h"

// Readline
# include <readline/readline.h>
# include <readline/history.h>

// Printf Minishell header on start
void	print_header(void);

// Work with readline
void	read_shell(t_minishell *shell);

// Parse Checkers
int check_cmd_line(t_minishell *shell, char *line, int sg_quote, int db_quote);
int check_before_ph(t_minishell *shell, char *line, int index, char c);
int check_ph(t_minishell *shell, char *line, size_t index, int *parenthesis);
int check_meta_s(t_minishell *shell, char *line, size_t *sym_counter, int *index);
size_t check_syntax(char *line, int index);
void fill_cmd_list(t_minishell *shell);

// Line parse
char **start_parse_cmds(char *line, int sg_quote, int db_quote);
void cut_part(char *line, char ***cmds, int *xyz);
int get_cmds_size(char *line, int sg_quote, int db_quote);

// EXECUTION
void execution_management(t_minishell *shell, size_t cmd_index);
void execution_controller(t_minishell *shell, size_t cmd_index);
size_t command_execution(t_minishell *shell, size_t *cmd_index);
void control_new_command_io(t_minishell *shell, t_token *token);
void pipe_command(t_minishell *shell, t_token *token, int is_last);
void mutate_tokens(t_minishell *shell, char ***tokens);

// BUILT-IN EXECUTION
int execute_token(t_minishell *shell, t_token *token);
void check_builtin(t_token *token, char *program_name);
int execute_builtin(t_minishell *shell, t_token *token);

// Split of commands
void cmd_split(t_minishell *shell, t_token *cmd);
void count_split_size(t_token *token, char *str);
void skip_word(char *str, size_t *i, size_t *j);
void fill_cmd_list_token(t_minishell *shell, t_token *cmd);
void cut_quotes(char *line, char ***cmds, size_t *xyz, size_t *quote_size);

// Finding path of command
char **find_path(t_minishell *shell);
char *is_command_executable(t_minishell *shell, char *command, char **paths);
char *exec_join_check(char *path, char *command);
char *standard_command_check(t_minishell *shell, char *command);

// File Descriptors management
void file_controller(t_minishell *shell, t_token *token);
void stdio_mutate(t_minishell *shell, t_token *token, char *redirect);
int stdio_check(t_minishell *shell, char *redirect, size_t i, int *io);
int check_file(t_minishell *shell, char *file, int check_flags);
char *open_here_doc_fd(t_minishell *shell, int *fd);

// Controllers
int controller(t_minishell *shell, char *user_input);
void	here_doc_controller(t_minishell *shell, char *cmd_line);
int	quote_controller(t_minishell *shell, char *line);

// here_doc execution (<<)
int	execute_heredoc(t_minishell *shell, char *cmd_line, size_t index);
void exe_here_doc(t_minishell *shell, char *limiter);
void	wait_limiter(t_minishell *shell, char *limiter, int fd);
void  remove_heredoc(int here_doc_num);
char *concat_heredoc(t_exc_line *exec);
void	write_variable(t_minishell *shell, char *tmp, int fd);
int		get_heredoc_count(t_minishell *shell);

// Utils
int		check_slice(char *line, char *SINGLE, char *DOUBLE);
void	*free_single(void **addr);
void	*free_double(void ***addr);
size_t	get_2d_array_length(void **array);
int get_line_type(char *line);
int quote_check(int *sg_quote, int *db_quote, char c);
int	check_valid_export(t_minishell *shell, char *cmd);
int	check_variable(char *buff);

// env controller
char			**env_dup(char **env);
void            env_controller(t_minishell *shell, char **envp);
char			*get_env(t_minishell *shell, char *var);
void			set_env(t_minishell *shell, char *var, char *value, int add);
void			set_new_env(t_minishell *shell, char *var, char *value, int add);

// Error management
void	force_quit(int errno_c);
int write_exception(t_minishell *shell, int errno_c, int exit_code, char *txt);
char *get_custom_error(int errno_c);
int print_error(t_minishell *shell, char *error_txt);

// Wildcard
char	*wildcard(char *pattern);
int		match(char *str, char *pattern);
char	*get_suitable(char *suit, char *d_name);
int		match_utils(char *str, char *pattern, char *star, char *tmp);

// Signals
void	signal_handler(int action);
void	sigint_handler(int sig_num);
void	sigint_handler_in_process(int sig);
void	sigquit_handler_in_process(int sig);

#endif