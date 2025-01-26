#include "../../../includes/minishell.h"
#include "tokens.h"
#include "../command/command.h"

char	*process_env_string(t_env *env, t_token *token)
{
	char	*result;
	char	*temp;
	size_t	i;
	char	buff[2];
	result = NULL;
	i = 0;
	buff[1] = '\0';
	while (token->txt[i])
	{
		if (is_env_var_start(token, i))
		{
			temp = handle_env_var(env, token, &i);
			result = append_str(result, temp);
			free(temp);
		}
		else
		{
			buff[0] = token->txt[i++];
			result = append_str(result, buff);
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*replace_env(t_env *env, t_token *token)
{
	char	*new_str;
	char	*old_str;

	if (!token || !token->txt)
		return (NULL);
	new_str = process_env_string(env, token);
	if (!new_str)
		return (NULL);
	old_str = token->txt;
	token->txt = new_str;
	free(old_str);
	return (new_str);
}

void	replace_tokens_with_env(t_env *env, t_token *token)
{
	t_token	*current;

	if (!env || !token)
		return ;
	current = token;
	while (current)
	{
		if (current->txt && ft_strchr(current->txt, '$'))
			replace_env(env, current);
		if (is_redir_token(current, "<<"))
		{
			if (current->next->next)
				current = current->next->next;
			else
				break ;
		}
		else
			current = current->next;
	}
}