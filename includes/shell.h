/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:25:46 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/01 12:35:04 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
#define SHELL_H

// main for one check global
// parent to go deeper in one line
// child to get how many childs have one parent

typedef struct s_minishell {
	struct s_exc_line *execute;
	struct s_local_env *local_env;
	char *user_input;
	char **envp;
	int status;
} t_minishell;

typedef struct s_exc_line {
	struct s_token *cmd_list;
	size_t clist_len;
	char **tokens;
	int STDIN;
	int STDOUT;
	int	HEREDOC_IN;
	int	HEREDOC_OUT;
	int PIPE_IN;
	int RDR_OUT;
	size_t command_wait_list;
	int skip_phs;
	int skip_mode;
	int is_single_cmd;
} t_exc_line;

typedef struct s_token {
	size_t token_mode;
	char *cmd;
	char *path;
	char **tokens;
	char **redirects;
	int stdin;
	int stdout;
	size_t size_cmd;
	size_t size_rdr;
	int status;
	int is_built_in;
} t_token;

// Initialize
t_minishell *init_minishell();
t_exc_line *init_exc_line();
t_token *init_tokens(size_t size);

enum token_modes {
	CMD,
	PIPE,
	OR,
	AND,
	PH_OPEN,
	PH_CLOSE
};

enum file_state {
	NOT_EXIST,
	PERMISSION_DENIED,
	IS_DIR,
	EXIST
};

// TRUE and FALSE
enum boolean {
    TRUE = 1,
    FALSE = 0
};

enum errors {
    ENOSUCHFILE = 2,
    ERNOMEM = 12,
    EPDEN = 13,
	E_ISDIR = 126,
    ECMDNF = 127,
};

enum builtin {
	BIN_ECHO,
	BIN_CD,
	BIN_PWD,
	BIN_EXPORT,
	BIN_UNSET,
	BIN_ENV,
	BIN_EXIT
};

#endif