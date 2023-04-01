/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:07:24 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/01 18:21:01 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libs
#include "libft.h"
#include "get_next_line.h"
#include "shell.h"

// Readline
// #include <readline/readline.h>
// #include <readline/history.h>

// C Libs
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Defines
#define SHELL_NAME "\033[32mmishell> \033[0m"
#define 

// Took input from user
void read_shell(t_minishell *shell);

// Utils
void *free_single(void **addr);
void *free_double(void ***addr);
void force_quit(int errno);

#endif