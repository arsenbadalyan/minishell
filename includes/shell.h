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
	struct s_status *status;
	struct s_local_env *local_env;
	char *user_input;
	char **envp;
} t_minishell;

typedef struct s_exc_line {
	struct s_token *cmd_list;
	size_t clist_len;
	int heredoc_sum;
	char **tokens;
	int input_fd;
	int output_fd;
	int skip_phs;
	int skip_mode;
} t_exc_line;

typedef struct s_token {
	size_t token_mode;
	char *cmd;
	char **tokens;
	char **redirects;
	int stdin;
	int stdout;
	size_t size_cmd;
	size_t size_rdr;
} t_token;

typedef struct s_status {
	int exit_code;
} t_status;

// Initialize
t_minishell *init_minishell();
t_exc_line *init_exc_line();
t_token *init_tokens(size_t size);
t_status *init_status();

enum token_modes {
	CMD,
	PIPE,
	OR,
	AND,
	PH_OPEN,
	PH_CLOSE
};

#endif