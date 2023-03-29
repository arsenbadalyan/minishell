#ifndef SHELL_H
#define SHELL_H

typedef struct s_minishell {
    struct s_exc_line *execute;
} t_minishell;

typedef struct s_exc_line {
    struct s_cmd *cmd_list;
    char *cmd_line;
    char **cmd_parts;
} t_exc_line;

typedef struct s_cmd {
    char *cmd_line;
    char **cmd;
} t_cmd;

typedef struct s_error {
    int line_status;
    int part_status;
} t_error;

// Initialize
t_minishell *init_minishell();

#endif