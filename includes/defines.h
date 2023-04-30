/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:04 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 20:13:11 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

// Main
# define SHELL_NAME "mishell$ "
# define SHELL_NAME_CONSOLE "minishell"
# define WHITE_SPACE " \t\n"
# define HERE_DOC "/tmp/.minishell_here_doc_"
# define ECHO_BRAKEPOINT "@#%^$*}]{+=? \n\t.,-[|/>'<;:~\\\""
# define METASYMBOLS_ALL "><|&)( \t\n"
# define SEPARATORS_ALL "(&<|>)"
# define SINGLE_SEPARATORS "<|>"
# define DOUBLE_SEPARATORS "<|>&"
# define STRICT_META "|&)"
# define PATH_MAX 1024 
# define REDIRECTS "<>"
# define SHLMSG "minishell: warning: shell level (%d) too high, resetting to 1\n"

// Parse Separators
# define PARSE_SEP_SINGLE "(|)"
# define PARSE_SEP_DOUBLE "&|"

// Env Constants
# define PATH "PATH"

// Custom Errors
# define ERROR_UNX "unexpected error"
# define ERROR_127 "command does not exist in the PATH or wrong command name"
# define ERROR_126 "is a directory"
# define ERROR_ARG "too many arguments"
# define ERROR_NUM "numeric argument required"
# define ERROR_130 "syntax error near unexpected token"
# define ERROR_VID "not a valid identifier"
# define ERROR_132 "not enough arguments"
# define ERROR_OLDPWD "cd: OLDPWD not set"
# define ERROR_299 "ambiguous redirect"

// Built-in program names
# define BUILT_IN_ECHO "echo"
# define BUILT_IN_CD "cd"
# define BUILT_IN_PWD "pwd"
# define BUILT_IN_EXPORT "export"
# define BUILT_IN_UNSET "unset"
# define BUILT_IN_ENV "env"
# define BUILT_IN_EXIT "exit"

#endif