#include "minishell.h"

void change_input_file(t_minishell *shell, int fd)
{
	int temp_fd;

	temp_fd = shell->execute->input_fd;
	shell->execute->input_fd = fd;
	if (temp_fd != 0)
		close(temp_fd);
}

void change_output_file(t_minishell *shell, int fd)
{
	int temp_fd;

	temp_fd = shell->execute->output_fd;
	shell->execute->output_fd = fd;
	if(temp_fd != 1)
		close(temp_fd);
}