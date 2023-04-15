/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:04 by armartir          #+#    #+#             */
/*   Updated: 2023/04/15 21:17:44 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

// Main
# define SHELL_NAME "\033[32mmishell$ \033[0m"
# define SHELL_NAME_CONSOLE "minishell"
# define WHITE_SPACE " \t\n"
# define HERE_DOC ".here_doc"
# define METASYMBOLS_ALL "><|&)( \t\n"
# define SEPARATORS_ALL "(&<|>)"
# define SINGLE_SEPARATORS "<|>"
# define DOUBLE_SEPARATORS "<|>&"
# define STRICT_META "|&)"
# define PATH_MAX 1024 

// Custom Errors
# define ERROR_UNX "unexpected error"
# define ERROR_127 "command does not exit in the PATH or wrong command name"
# define ERROR_ARG "too many arguments"
# define ERROR_255 "numeric argument required"
# define ERROR_130 "syntax error near unexpected token"
# define ERROR_131 "not a valid identifier"
# define ERROR_132 "not enough arguments"
#endif