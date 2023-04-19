#include "minishell.h"

void file_controller(t_minishell *shell, t_token *token)
{
	size_t i;
	char **redirects;

	i = 0;
	redirects = token->redirects;
	while(redirects[i])
	{
		stdio_mutate(shell, token, redirects[i]);
		if(token->status)
			return;
		i++;
	}
}

void stdio_mutate(t_minishell *shell, t_token *token, char *redirect)
{
	size_t i;
	int fd;
	int io;
	DIR *dir;
	
	i = 0;
	io = 0;
	while(redirect[i] && (ft_strchr(REDIRECTS, redirect[i]) || ft_strchr(WHITE_SPACE, redirect[i])))
		i++;
	fd = stdio_check(shell, redirect, i, &io);
	if(fd < 0)
	{
		token->status = errno;
		return;
	}
	if(redirect[0] == '>' && check_file(shell, redirect + i, F_OK) != EXIST)
	{
		token->status = E_ISDIR;
		return;
	}
	if(!io)
		token->stdin = fd;
	else
		token->stdout = fd;
}

int stdio_check(t_minishell *shell, char *redirect, size_t i, int *io)
{
	char *here_doc;
	int fd;

	fd = -1;
	here_doc = NULL;
	if (redirect[0] == '<' && redirect[0] != redirect[1])
		fd = open(redirect + i, O_RDONLY);
	else if (redirect[0] == '<' && redirect[0] == redirect[1])
		here_doc = open_here_doc_fd(shell, &fd);
	else if (redirect[0] == '>' && redirect[0] != redirect[1] && ++(*io))
		fd = open(redirect + i, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	else if (redirect[0] == '>' && redirect[0] == redirect[1] && ++(*io))
		fd = open(redirect + i, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
	if (fd < 0)
	{
		if(here_doc)
			print_error(shell, here_doc);
		else
			print_error(shell, redirect + i);
		free_single((void *)&here_doc);
	}
	return (fd);
}

char *open_here_doc_fd(t_minishell *shell, int *fd)
{
	char *here_doc;

	here_doc = concat_heredoc(shell->execute);
	if (!here_doc)
		force_quit(ERNOMEM);
	*fd = open(here_doc, O_RDONLY);
	return (here_doc);
}

int check_file(t_minishell *shell, char *file, int check_flags)
{
	DIR *dir;

	if(access(file, F_OK) == -1)
	{
		write_exception(shell, ENOSUCHFILE, 1, file);
		return (NOT_EXIST);
	}
	if(access(file, check_flags) == -1)
	{
		write_exception(shell, EPDEN, 1, file);
		return (PERMISSION_DENIED);
	}
	dir = opendir(file);
	if(dir)
	{
		write_exception(shell, E_ISDIR, 1, file);
		closedir(dir);
		return (IS_DIR);
	}
	return (EXIST);
}