/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:07:24 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/30 19:20:05 by armartir         ###   ########.fr       */
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
# include <termios.h>
# include <curses.h>

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
void read_shell(t_minishell *shell, char *user_input, char *input_cpy);

// Parse Checkers
int		check_cmd_line(t_minishell *shell, char *line,
			int sg_quote, int db_quote);
int		check_before_ph(t_minishell *shell, char *line, int index, char c);
int		check_ph(t_minishell *shell, char *line, size_t index,
			int *parenthesis);
int		check_meta_s(t_minishell *shell, char *line,
			size_t *sym_counter, int *index);
size_t	check_syntax(char *line, int index);
void	fill_cmd_list(t_minishell *shell);

// Line parse
char	**start_parse_cmds(char *line, int sg_quote, int db_quote);
void	cut_part(char *line, char ***cmds, int *xyz);
int		get_cmds_size(char *line, int sg_quote, int db_quote);

// EXECUTION
void execution_management(t_minishell *shell, size_t cmd_index);
void continue_execution(t_minishell *shell, size_t *cmd_index);
void execution_controller(t_minishell *shell, size_t *cmd_index);
size_t command_execution(t_minishell *shell, size_t *cmd_index);
void start_execution(t_minishell *shell, size_t cmd_index);
void exe_md(t_minishell *shell, size_t *cmd_index, int *l_in, int *l_out);
void finish_execution(t_minishell *shell, size_t cmd_index);
int check_if_last_command(t_minishell *shell, t_token *token, int is_last);
void child_process_run(t_minishell *shell, t_token *token, int pipe_fd[2]);
void commands_skip_execution(t_minishell *shell, size_t *cmd_index);
void control_new_command_io(t_minishell *shell, t_token *token);
void control_command_input(t_minishell *shell, t_token *token);
void control_command_output(t_minishell *shell, t_token *token);
void pipe_command(t_minishell *shell, t_token *token, int is_last);
void mutate_tokens(t_minishell *shell, t_token *token, char ***tokens);
int tr_echo(char ***tokens);
char **mutate_wildcards(t_minishell *shell, char **new_tokens, char *mdf_token);

// Redirect mutation
void	mutate_redirects(t_minishell *shell, t_token *token, char ***redirects);
int		redirect_manipulation(t_minishell *shell, t_token *token,
			char **redirect);
size_t	get_redirect_type(char **redirect, int *type);
int		open_redirect_wildcards(t_minishell *shell, t_token *token,
			char **redirect, int skip);

// BUILT-IN EXECUTION
int		execute_token(t_minishell *shell, t_token *token);
void	check_builtin(t_token *token, char *program_name);
int		execute_builtin(t_minishell *shell, t_token *token);

// Split of commands
void	cmd_split(t_minishell *shell, t_token *cmd);
void	count_split_size(t_token *token, char *str);
void	skip_word(char *str, size_t *i, size_t *j);
void	fill_cmd_list_token(t_minishell *shell, t_token *cmd);
void	cut_quotes(char *line, char ***cmds, size_t *xyz, size_t *quote_size);

// Finding path of command
char	**find_path(t_minishell *shell);
char	*is_command_executable(t_minishell *shell, char *command, char **paths);
char	*exec_join_check(char *path, char *command);
char	*standard_command_check(t_minishell *shell, char *command);

// File Descriptors management
void	file_controller(t_minishell *shell, t_token *token, int type, int fd);
int		stdio_mutate(t_minishell *shell, t_token *token,
			char *redirect, int type);
int		stdio_check(t_minishell *shell, t_token *token,
			char *redirect, int type);
int		check_file(t_minishell *shell, char *file, int check_flags);
char	*open_here_doc_fd(t_minishell *shell, t_token *token, int *fd);

// Controllers
int		controller(t_minishell *shell, char *user_input);
void	here_doc_controller(t_minishell *shell, char *cmd_line);
int		quote_controller(t_minishell *shell, char *line);

// here_doc execution (<<)
int heredoc_process_control(t_minishell *shell, char *cmd_line);
int execute_heredoc(t_minishell *shell, char *cmd, size_t i);
void exe_here_doc(t_minishell *shell, char *limiter);
void	wait_limiter(t_minishell *shell, char *limiter, int fd);
void	remove_heredoc(t_minishell *shell);
char	*concat_heredoc(t_exc_line *exec, t_token *token);
void	write_variable(t_minishell *shell, char *tmp, int fd);
int		get_heredoc_count(t_minishell *shell);

// Memory free functions
void	*free_single(void **addr);
void	*free_double(void ***addr);
void	*free_token(t_minishell *shell, t_token *token);

// Utils
int		check_slice(char *line, char *SINGLE, char *DOUBLE);
size_t	get_2d_array_length(void **array);
int		get_line_type(char *line);
int		quote_check(int *sg_quote, int *db_quote, char c);
int		check_valid_export(t_minishell *shell, char *cmd, char *order);
char	**push_to_double_array(char **arr, char *new_line);
char	**concat_double_arrays(char **arr_1, char **arr_2);
size_t	get_heredoc_sum(t_minishell *shell, char *str);

// env controller
char	**env_dup(char **env);
void	env_controller(t_minishell *shell, char **envp);
char	*get_env(t_minishell *shell, char *var);
void	set_env(t_minishell *shell, char *var, char *value, int add);
void	set_new_env(t_minishell *shell, char *var, char *value, int add);

// Error management
void	force_quit(int errno_c);
int		write_exception(t_minishell *shell, int errno_c,
			int exit_code, char *txt);
char	*get_custom_error(int errno_c);
int		print_error(t_minishell *shell, char *error_txt);

// Wildcard
char	**wildcard(char *pattern);
int		match(char *str, char *pattern);
void	modify_wildcard_array(char ***wildcards, char *dirname);
int		match_utils(char *str, char *pattern, char *star, char *tmp);

// Signals
void	sigint_handler(int sig_num);
void	global_signal_handler(int action);

#endif