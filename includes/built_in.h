#ifndef BUILT_IN__H
#define BUILT_IN__H

// echo
char	*_echo(char *line, int here_doc_mode);
char	*modify_line(char *line, int here_doc_mode, int sg_quote, int db_quote);
int		quote_check(int *sg_quote, int *db_quote, char c);
// pwd
int		_pwd(void);
// cd
int 	_cd(t_minishell *shell, char **cmd_line);
char	*get_tilde(char **cmd_line, char **env);
void	change_pwd(t_minishell *shell, char *cmd, int add);

#endif