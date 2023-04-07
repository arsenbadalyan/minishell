#ifndef DEFINES_H
#define DEFINES_H

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
# define ERROR_130 "syntax error near unexpected token"

#endif