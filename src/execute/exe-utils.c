#include "minishell.h"

char *exec_join_check(char *path, char *command)
{
	char *temp_path;
	char *check_path;

	temp_path = ft_strjoin(path, "/");
	if (!temp_path)
		force_quit(ENOMEM);
	check_path = ft_strjoin(temp_path, command);
	if (!check_path)
		force_quit(ENOMEM);
	free_single((void *)&temp_path);
	if (!access(check_path, X_OK))
		return (check_path);
	free_single((void *)&check_path);
	return (0);
}

char *is_command_executable(char *command, char **paths)
{
	size_t i;
	char *check_path;

	i = 0;
	if (!access(command, X_OK))
	{
		check_path = ft_strdup(command);
		if (!check_path)
			force_quit(ENOMEM);
		return (check_path);
	}
	// if file not sush file or directore give error
	if(ft_strchr(command, '/'))
	{
		printf("chkaaaaa\n");
		return (NULL);
	}
	while (paths[i])
	{
		check_path = exec_join_check(paths[i], command);
		if (check_path)
			return (check_path);
		free_single((void *)&check_path);
		i++;
	}
	return (NULL);
}

char **find_path(t_minishell *shell)
{
	char *path;
	char **paths;

	path = get_env(shell, PATH);
	if (path)
	{
		// envp[i][3] = '.';
		// envp[i][4] = ':';
		// envp[i] += 5;
		paths = ft_split(path, ':');
		if(!paths)
			force_quit(ENOMEM);
		return (paths);
	}
	return (NULL);
}