/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:55:39 by armartir          #+#    #+#             */
/*   Updated: 2023/04/10 16:57:15 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

// echo
char	*_echo(char *line, int here_doc_mode);
char	*modify_line(char *line, int here_doc_mode, int sg_quote, int db_quote);
int		quote_check(int *sg_quote, int *db_quote, char c);
// pwd
int		_pwd(void);
// cd
int		_cd(t_minishell *shell, char **cmd_line);
char	*join_tilde(t_minishell *shell, char *dir);
int		_cd_utils(t_minishell *shell, char *cmd, char **cmd_line);
// exit
void	mini_exit(t_minishell *shell, char **cmd);
// env
void	_env(t_minishell *shell, int add);
// export
void	_export(t_minishell *shell, char **cmd);

#endif