#include "../../../includes/minishell.h"
#include "tokens.h"

int	print_unexpected(t_env *env, char *token, int new_status)
{
	char	*temp;

	temp = ft_itoa(new_status);
	printf("-bash: syntax error near unexpected token `%s'\n", token);
	set_env(&env, "?", temp);
	free(temp);
	return (0);
}

static int	is_redir_token(char *str)
{
	return (ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "|") == 0);
}

int redir_check(t_token *token, t_env *env)
{
    t_token *current;
    
    current = token;
    if (!ft_strcmp(current->txt, "|"))
        return print_unexpected(env, "|", 2);
        
    while (current && current->next)
    {
        if (is_redir_token(current->txt) && is_redir_token(current->next->txt))
        {
            if (!ft_strcmp(current->txt, "|") || !ft_strcmp(current->next->txt, "|"))
                return (print_unexpected(env, "|", 2));
            else
                return (print_unexpected(env, current->next->txt, 2));
        }
        current = current->next;
    }
    if (current && is_redir_token(current->txt) && ft_strcmp(current->txt, "|"))
        return (print_unexpected(env, "newline", 2));
        
    return (1);
}