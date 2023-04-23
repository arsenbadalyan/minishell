/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:55:39 by armartir          #+#    #+#             */
/*   Updated: 2023/04/19 14:14:16 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

// echo
char *_echo(t_minishell *shell, char **cmd_line, int hd_mode, char *hd_lim);
char *join_lines(char **cmd_line, size_t i, int has_new_line, char *temp_line);
char *modify_line(t_minishell *shell, char *line, int hd_mode, int *quotes);
void get_variable(t_minishell *shell, char **line, char **new_line);
void get_env_for_echo(t_minishell *shell, char *var, char **new_line);
// pwd
int	_pwd(t_token *token);
// cd
int		_cd(t_minishell *shell, char **cmd_line);
char	*join_tilde(t_minishell *shell, char *dir);
int		_cd_utils(t_minishell *shell, char *cmd, char **cmd_line);
// exit
void	mini_exit(t_minishell *shell, char **cmd);
void	check_num(t_minishell *shell, char *str);
// env
void	_env(t_minishell *shell, int add);
void	print_env(char *env);
// export
void	_export(t_minishell *shell, char **cmd);
void	_export_exe(t_minishell *shell, char *var, char *val, int add);
char	*get_value(t_minishell *shell, char *var, char *cmd);
int		check_equal(char *cmd);
// unset
int		_unset(t_minishell *shell, char **cmd_line);
void	env_pop(t_minishell *shell, char *cmd);

#endif