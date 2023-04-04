/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:42:43 by armartir          #+#    #+#             */
/*   Updated: 2023/04/02 21:49:36 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	here_doc_controller(char *cmd_line)
{
	size_t	i;
	int		par_err_index;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
		{
			i += 2;
			while (cmd_line[i] == ' ')
				i++;
			if (here_doc_params(cmd_line, i, 0, 0))
				return (1);
		}
		i++;
	}
	return (0);
}

void quote_controller(char *line)
{
	size_t i;
	int db_quote;
	int sg_quote;

	i = 0;
	db_quote = 0;
	sg_quote = 0;
	while(line[i])
	{
		if(!quote_check(&sg_quote, &db_quote, line[i]))
		{
			// TODO make one function for exeptions
			printf("parse error: unexpeted token \' or \"\n");
			exit(1);
		}
		i++;
	}
	if(db_quote || sg_quote)
	{
		// TODO make one function for exeptions
			printf("parse error: unexpeted token \' or \"\n");
			exit(1);
	}
		
}