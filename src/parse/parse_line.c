#include "minishell.h"

void start_parse_cmds(char *line, int sg_quote, int db_quote)
{
	int xyz[3];
	char **cmds;
	
	xyz[0] = 0;
	xyz[1] = 0;
	xyz[2] = 0;
	cmds = malloc(sizeof(char *) * get_cmds_size(line, 0, 0) + 1);
	while(line[xyz[0]])
	{
		quote_check(&sg_quote, &db_quote, line[xyz[0]]);
		if((sg_quote || db_quote) && ++xyz[0])
			continue;
		cut_part(line, cmds, xyz);
		xyz[0]++;
	}
	cmds[xyz[2]] = NULL;
	printf("%d\n", xyz[2]);
	int i = 0;
	while(cmds[i])
	{
		printf("%s\n", cmds[i]);
		i++;
	}
}

void cut_part(char *line, char **cmds, int *xyz)
{
	int slice_size;

	if(!line[xyz[0] + 1])
	{
		cmds[xyz[2]] = ft_substr(line, xyz[1], xyz[0] - xyz[1] + 1);
		xyz[2] += 1;
		return;
	}
	slice_size = check_slice(line, SINGLE_SEPARATORS, DOUBLE_SEPARATORS);
	if (!slice_size)
		return ;
	cmds[xyz[2]] = ft_substr(line, xyz[1], xyz[0] - xyz[1]);
	xyz[1] = xyz[0];
	xyz[0] += slice_size;
	cmds[xyz[2] + 1] = ft_substr(line, xyz[1], xyz[0] - xyz[1]);
	xyz[1] = xyz[0];
	xyz[2] += 2;
}

int get_cmds_size(char *line, int sg_quote, int db_quote)
{
	size_t i;
	size_t size;
	int slice_size;

	size = 1;
	i = 0;
	while (line[i])
	{
		quote_check(&sg_quote, &db_quote, line[i]);
		if ((sg_quote || db_quote) && i++)
			continue;
		slice_size = check_slice(line, SINGLE_SEPARATORS, DOUBLE_SEPARATORS);
		if(slice_size)
		{
			size++;
			i += slice_size;
		} else
			i++;
	}
	return (size);
}