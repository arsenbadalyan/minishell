/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutate-helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:08:18 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 19:08:59 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_2d_array(void)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *));
	if (!arr)
		force_quit(ENOMEM);
	arr[0] = NULL;
	return (arr);
}

char	**mutate_wildcards(t_minishell *shell,
	char **new_tokens, char *mdf_token)
{
	char	**temp;
	char	**wildcards;

	wildcards = wildcard(mdf_token);
	if (!wildcards || (!wildcards[0] && !free_double((void *)&wildcards)))
	{
		new_tokens = push_to_double_array(new_tokens, mdf_token);
		return (new_tokens);
	}
	if (!new_tokens)
	{
		new_tokens = (char **)malloc(sizeof(char *));
		if (!new_tokens)
			force_quit(ENOMEM);
		new_tokens[0] = NULL;
	}
	new_tokens = concat_double_arrays(new_tokens, wildcards);
	return (new_tokens);
}

char	**push_to_double_array(char **arr, char *new_line)
{
	char	**new_arr;
	size_t	size;

	if (!arr)
		arr = init_2d_array();
	size = get_2d_array_length((void **)arr) + 2;
	new_arr = (char **)malloc(sizeof(char *) * size);
	if (!new_arr)
		force_quit(ENOMEM);
	new_arr[size - 2] = new_line;
	new_arr[size - 1] = NULL;
	size = 0;
	while (arr[size])
	{
		new_arr[size] = arr[size];
		size++;
	}
	free(arr);
	return (new_arr);
}

char	**concat_double_arrays(char **arr_1, char **arr_2)
{
	size_t	size_1;
	size_t	size_2;
	char	**new_arr;

	if (!arr_1)
		arr_1 = init_2d_array();
	size_1 = get_2d_array_length((void **)arr_1);
	size_2 = get_2d_array_length((void **)arr_2);
	new_arr = (char **)malloc(sizeof(char *) * (size_1 + size_2 + 1));
	if (!new_arr)
		force_quit(ENOMEM);
	size_1 = 0;
	size_2 = 0;
	while (arr_1[size_1++])
		new_arr[size_2++] = arr_1[size_1 - 1];
	size_1 = 0;
	while (arr_2[size_1++])
		new_arr[size_2++] = arr_2[size_1 - 1];
	new_arr[size_2] = NULL;
	free(arr_1);
	free(arr_2);
	return (new_arr);
}
