/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:54 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/02 15:32:37 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	force_quit(int errno)
{
	char	*error;

	error = strerror(errno);
	printf("minishell: %s\n", error);
	exit(errno);
}
