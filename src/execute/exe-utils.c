#include "minishell.h"

char *exec_join_check(char *path, char *command)
{
	char *temp_path;
	char *check_path;

	temp_path = ft_strjoin(path, "/");
	if (!temp_path)
		force_quit(ERNOMEM);
	check_path = ft_strjoin(temp_path, command);
	if (!check_path)
		force_quit(ERNOMEM);
	free_single((void *)&temp_path);
	if (!access(check_path, X_OK))
		return (check_path);
	free_single((void *)&check_path);
	return (0);
}

char *is_command_executable(t_minishell *shell, char *command, char **paths)
{
	size_t i;
	char *check_path;

	i = 0;
	check_path = standard_command_check(shell, command);
	if(check_path)
		return (check_path);
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

char *standard_command_check(t_minishell *shell, char *command)
{
	char *result;

	result = NULL;
	if (ft_strchr(command, '/') && access(command, X_OK))
	{
		check_file(shell, command, X_OK);
		result = ft_strdup("");
		if(!result)
			force_quit(ERNOMEM);
		return (result);
	}
	if (!access(command, X_OK))
	{
		result = ft_strdup(command);
		if (!result)
			force_quit(ERNOMEM);
		return (result);
	}
	return (result);
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
			force_quit(ERNOMEM);
		return (paths);
	}
	return (NULL);
}