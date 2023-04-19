#include "minishell.h"

int check_cmd_line(t_minishell *shell, char *line, int sg_quote, int db_quote)
{
	size_t sym_counter;
	int i;
	int ph;

	i = 0;
	ph = 0;
	sym_counter = 0;
	while (line[i])
	{
		quote_check(&sg_quote, &db_quote, line[i]);
		if ((sg_quote || db_quote) && ++sym_counter && ++i)
			continue ;
		if (check_before_ph(shell, line, i, line[i]) || check_ph(shell, line, i, &ph) 
			|| check_meta_s(shell, line, &sym_counter, &i))
			return (130);
		if (!ft_strchr(METASYMBOLS_ALL, line[i]))
			sym_counter++;
		i++;
	}
	if ((ph && write_exception(shell, 130, 130, ")")))
		return (130);
	return (0);
}

int check_before_ph(t_minishell *shell, char *line, int index, char c)
{
	if((((c == '(' && --index) || (c == ')' && ++index)) && index > 0 && line[index]))
	{
		while(1)
		{
			if(ft_strchr(WHITE_SPACE, line[index]))
			{
				if(c == '(')
					--index;
				else
					++index;
			}
			else if(index < 0 || c == line[index] || (c == ')' && !line[index])
				|| ((line[index] == '&' || line[index] == '|')
				&& (((line[index - 1] == line[index] && c == '(')
					|| (line[index + 1] == line[index] && c == ')')))))
				return (0);
			else
				return (write_exception(shell, 130, 130, &c));
			if(index < 0 || !line[index])
				break;
		}
	}
	return (0);
}

int check_ph(t_minishell *shell, char *line, size_t index, int *parenthesis)
{
	size_t is_empty;

	is_empty = 0;
	if (line[index] == '(')
	{
		*parenthesis += 1;
		while(line[index])
		{
			if (!ft_strchr(METASYMBOLS_ALL, line[index]))
				is_empty++;
			if (line[index] == ')' && !is_empty)
					return (write_exception(shell, 130, 130, ")"));
			else if (line[index] == ')')
				return (0);
			index++;
		}
		return (write_exception(shell, 130, 130, "("));
	}
	else if (line[index] == ')')
		*parenthesis -= 1;
	if (*parenthesis < 0)
		return (write_exception(shell, 130, 130, ")"));
	return (0);
}

int check_meta_s(t_minishell *shell, char *line, size_t *sym_counter, int *index)
{
	char last_meta[3];
	int slice_size;

	ft_bzero(last_meta, 3);
	slice_size = check_slice((line + (*index)), SINGLE_SEPARATORS, DOUBLE_SEPARATORS);
	if (slice_size)
	{
		if (!ft_strlen(last_meta) && !(*sym_counter)
			&& ft_strchr(STRICT_META, *(line + (*index))))
		{
			ft_memcpy(last_meta, (line + (*index)), (size_t)slice_size);
			return (write_exception(shell, 130, 130, last_meta));
		}
		ft_memcpy(last_meta, (line + (*index)), (size_t)slice_size);
		*index += slice_size;
		*sym_counter = 0;
		if (!check_syntax(line, *index))
			return (write_exception(shell, 130, 130, last_meta));
		*index -= 1;
	}
	return (0);
}

size_t check_syntax(char *line, int index)
{
	size_t sym_counter;
	char *strict_mode;

	sym_counter = 0;
	strict_mode = ft_strchr(STRICT_META, line[index - 1]);
	while(line[index])
	{
		if (((ft_strchr(STRICT_META, line[index]) && strict_mode
			&& (line[index] != '&' || (line[index] == '&' && line[index] == line[index + 1]))))
			|| (ft_strchr(SEPARATORS_ALL, line[index]) && !strict_mode))
			return (sym_counter);
		else if (!ft_strchr(WHITE_SPACE, line[index]))
			sym_counter++;
		index++;
	}
	return (sym_counter);
}
