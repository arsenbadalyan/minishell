/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:28:26 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/02 21:53:40 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// TODO change function names and few things
char *_echo(char *line, int here_doc_mode)
{
	size_t i;
	size_t length;
	char *temp_new_line;
	char *new_line;
	
	i = 0;
	length = ft_strlen(line);
	temp_new_line = modify_line(line, length, 0, 0);
	if(!temp_new_line)
		return (NULL);
	new_line = ft_strdup(temp_new_line);
	free_single((void *)&temp_new_line);
	return (new_line);
}

char *modify_line(char *line, int here_doc_mode, int sg_quote, int db_quote)
{
	char	*new_line;
	char	*temp_line;
	char	current[2];

	new_line = ft_strdup("");
	current[1] = '\0';
	while(*line)
	{
		quote_check(&sg_quote, &db_quote, *line);
		if(!ft_strchr("\'\"$", *line) || ((sg_quote && *line == '\"') || (db_quote && *line == '\'')))
		{
			temp_line = new_line;
			current[0] = *line;
			new_line = ft_strjoin(new_line, current);
			free_single((void *)&temp_line);
		}
		line++;
	}
	return (new_line);
}

int quote_check(int *sg_quote, int *db_quote, char c)
{
	int *status;

	if(!ft_strchr("\'\"", c) || (*sg_quote && c == '\"') || (*db_quote && c == '\''))
		return (1);
	if(c == '\'')
		status = sg_quote;
	else
		status = db_quote;
	if(*status)
		*status -= 1;
	else
		*status += 1;
	if(*status < 0)
		return (0);
	return (1);
}
