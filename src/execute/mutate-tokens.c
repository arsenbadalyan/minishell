#include "minishell.h"

void mutate_tokens(t_minishell *shell, t_token *token, char ***tokens)
{
    size_t i;
    char *temp;
    char **new_tokens;
    int quotes[2];

    i = 0;
    new_tokens = NULL;
    while ((*tokens)[i])
    {
        temp = (*tokens)[i];
        (*tokens)[i] = ft_strtrim((*tokens)[i], WHITE_SPACE);
        if (!free_single((void *)&temp) && !(*tokens)[i])
            force_quit(ERNOMEM);
        temp = (*tokens)[i];
        ft_bzero((void *)quotes, sizeof(int) * 2);
        (*tokens)[i] = modify_line(shell, (*tokens)[i], 0, quotes);
        if (!free_single((void *)&temp) && !(*tokens)[i])
            force_quit(ERNOMEM);
        if (!i && !ft_strcmp((*tokens)[i], BUILT_IN_ECHO) && tr_echo(tokens))
            return;
        if (i)
            new_tokens = mutate_wildcards(shell, new_tokens, (*tokens)[i]);
        else
            new_tokens = push_to_double_array(new_tokens, (*tokens)[i]);
        i++;
    }
    if (!new_tokens)
        return;
    *tokens = new_tokens;
}

int tr_echo(char ***tokens)
{
    size_t i;
    char *temp;

    i = 1;
    while((*tokens)[i])
    {
        temp = (*tokens)[i];
        (*tokens)[i] = ft_strtrim(temp, WHITE_SPACE);
        if (!(*tokens)[i])
            force_quit(ENOMEM);
        free_single((void *)&temp);
        i++;
    }
    return (1);
}