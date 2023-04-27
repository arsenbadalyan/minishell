#include "minishell.h"

size_t get_heredoc_sum(t_minishell *shell, char *str)
{
    size_t i;
    size_t sum;
    int quotes[2];

    ft_bzero((void *)quotes, sizeof(int) * 2);
    i = 0;
    sum = 0;
    while (str[i])
    {
        quote_check(&quotes[0], &quotes[1], str[i]);
        if ((quotes[0] || quotes[1]) && ++i)
            continue;
        if (str[i] == '<' && str[i] == str[i + 1])
            sum++;
        i++;
    }
    if(sum)
    {
        i = sum;
        sum = shell->execute->HEREDOC_SKIP;
        shell->execute->HEREDOC_SKIP += i;
    }
    return (sum);
}