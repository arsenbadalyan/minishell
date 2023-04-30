#include "minishell.h"

int	execute_token(t_minishell *shell, t_token *token)
{
	int	exit_status;

	signal(SIGINT, sigint_handler_in_process);
	signal(SIGQUIT, sigquit_handler_in_process);
	if (token->is_built_in != -1)
		exit_status = execute_builtin(shell, token);
	else
		exit_status = execve(token->path, token->tokens, shell->envp);
	exit_status = WEXITSTATUS(exit_status);
	return (exit_status);
}

void	check_builtin(t_token *token, char *program_name)
{
	if (!ft_strcmp(BUILT_IN_ECHO, program_name))
		token->is_built_in = BIN_ECHO;
	if (!ft_strcmp(BUILT_IN_CD, program_name))
		token->is_built_in = BIN_CD;
	if (!ft_strcmp(BUILT_IN_PWD, program_name))
		token->is_built_in = BIN_PWD;
	if (!ft_strcmp(BUILT_IN_EXPORT, program_name))
		token->is_built_in = BIN_EXPORT;
	if (!ft_strcmp(BUILT_IN_UNSET, program_name))
		token->is_built_in = BIN_UNSET;
	if (!ft_strcmp(BUILT_IN_ENV, program_name))
		token->is_built_in = BIN_ENV;
	if (!ft_strcmp(BUILT_IN_EXIT, program_name))
		token->is_built_in = BIN_EXIT;
}

int	execute_builtin(t_minishell *shell, t_token *token)
{
	char	*result;

	if (token->is_built_in == BIN_ECHO)
	{
		result = _echo(shell, token->tokens);
		ft_putstr_fd(result, token->stdout);
		free_single((void *)&result);
	}
	if (token->is_built_in == BIN_PWD)
		_pwd(token);
	if (token->is_built_in == BIN_CD)
		_cd(shell, token->tokens);
	if (token->is_built_in == BIN_ENV)
		_env(shell, 0);
	if (token->is_built_in == BIN_EXPORT)
		_export(shell, token->tokens);
	if (token->is_built_in == BIN_UNSET)
		_unset(shell, token->tokens);
	if (token->is_built_in == BIN_EXIT)
		mini_exit(shell, token->tokens);
	return (0);
}
