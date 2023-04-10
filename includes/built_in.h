#ifndef BUILT_IN__H
#define BUILT_IN__H

// echo
char *_echo(t_minishell *shell, char **cmd_line, int hd_mode, char *hd_lim);
char *join_lines(char **cmd_line, size_t i, int has_new_line, char *temp_line);
char *modify_line(t_minishell *shell, char *line, int hd_mode, int *quotes);
void get_variable(t_minishell *shell, char **line, char **new_line);
int		quote_check(int *sg_quote, int *db_quote, char c);
// pwd
int		_pwd(void);
// cd
int 	_cd(t_minishell *shell, char **cmd_line);
void	change_pwd(t_minishell *shell, char *cmd, int add);

#endif