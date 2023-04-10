#include "minishell.h"

char **is_valid_variable(char *exec_line)
{
    char *exc_line;
    char **new_line;
    size_t i;

    exc_line = ft_strtrim(exec_line, " ");
    if(!exc_line)
        force_quit(12);
    new_line = ft_split(exc_line, '=');
    if(!new_line)
        force_quit(12);
    // TODO: unset comment below
    // free_single((void *)&exec_line);
    free_single((void *)&exc_line);
    exc_line = new_line[1];
    // new_line[1] = _echo(new_line[1], 0);
    return (new_line);
}

void add_new_local(t_minishell *shell, char **exec_line)
{
    t_local_env *local_envp;
    t_local_env *new_local;

    local_envp = shell->local_env;
    if (local_envp && fd_md_lvar(local_envp, exec_line[0], exec_line[1], 0))
        return ;
    new_local = (t_local_env *)malloc(sizeof(t_local_env));
    new_local->key = exec_line[0];
    new_local->value = exec_line[1];
    if(local_envp)
    {
        while(local_envp->next)
            local_envp = local_envp->next;
        local_envp->next = new_local;
    }
    else
        shell->local_env = new_local;
    new_local->next = NULL;
}

t_local_env *fd_md_lvar(t_local_env *head, char *key, char *value, int is_find)
{
    char *temp_value;

    while(head)
    {
        if(!ft_strcmp(key, head->key))
        {
            if(is_find)
                return (head);
            temp_value = head->value;
            head->value = value;
            free_single((void *)&temp_value);
            return (head);
        }
        head = head->next;
    }
    return (NULL);
}