#include "minishell.h"

void	file_controller(t_minishell *shell, t_token *token, int type, int fd)
{
	if (type == RDR_INPUT || type == RDR_HERE_DOC)
	{
		if (token->stdout != -1)
			close(token->stdout);
		token->stdin = fd;
	}
	else
	{
		if (token->stdout != -1)
			close(token->stdout);
		token->stdout = fd;
	}
}

int	stdio_mutate(t_minishell *shell, t_token *token, char *redirect, int type)
{
	int	fd;
	int	io;
	DIR	*dir;

	io = 0;
	fd = stdio_check(shell, token, redirect, type);
	if (fd < 0)
	{
		shell->status = errno;
		return (1);
	}
	if (redirect[0] == '>' && check_file(shell, redirect, F_OK) != EXIST)
	{
		shell->status = E_ISDIR;
		return (1);
	}
	file_controller(shell, token, type, fd);
	return (1);
}

int	stdio_check(t_minishell *shell, t_token *token, char *redirect, int type)
{
	char	*here_doc;
	int		fd;

	fd = -1;
	here_doc = NULL;
	if (type == RDR_INPUT)
		fd = open(redirect, O_RDONLY);
	else if (type == RDR_HERE_DOC)
		here_doc = open_here_doc_fd(shell, token, &fd);
	else if (type == RDR_OUTPUT)
		fd = open(redirect, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	else if (type == RDR_APPEND)
		fd = open(redirect, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
	if (fd < 0)
	{
		if (here_doc)
			print_error(shell, here_doc);
		else
			print_error(shell, redirect);
	}
	free_single((void *)&here_doc);
	return (fd);
}

char	*open_here_doc_fd(t_minishell *shell, t_token *token, int *fd)
{
	char	*here_doc;

	here_doc = concat_heredoc(shell->execute, token);
	if (!here_doc)
		force_quit(ERNOMEM);
	*fd = open(here_doc, O_RDONLY);
	return (here_doc);
}

int	check_file(t_minishell *shell, char *file, int check_flags)
{
	DIR	*dir;

	if (access(file, F_OK) == -1)
	{
		write_exception(shell, ENOSUCHFILE, 1, file);
		return (NOT_EXIST);
	}
	if (access(file, check_flags) == -1)
	{
		write_exception(shell, EPDEN, 1, file);
		return (PERMISSION_DENIED);
	}
	dir = opendir(file);
	if (dir)
	{
		write_exception(shell, E_ISDIR, 1, file);
		closedir(dir);
		return (IS_DIR);
	}
	return (EXIST);
}
