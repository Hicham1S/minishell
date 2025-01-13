#include "../../../includes/minishell.h"
#include "tokens.h"

char	*get_next_key(t_token *token, int start)
{
	int	i;

	start++;
	if (token->txt[start] == '?')
			return (ft_strdup("?"));
	i = start;
	while (token->txt[i] && is_alphanumu(token->txt[i]))
		i++;
	return (ft_substr(token->txt, start, i - start));
}

char	*get_next_value(t_env *env, char *str)
{
	t_env	*res;

	if (!str || !env)
		return (ft_strdup(""));
	res = get_env(env, str);
	if (!res || !res->value)
		return (ft_strdup(""));
	return (ft_strdup(res->value));
}

char	*handle_env_var(t_env *env, t_token *token,
		size_t *i)
{
	char	*key;
	char	*value;
	char	*str;

	key = get_next_key(token, *i);
	if (!key)
		return (NULL);
	value = get_next_value(env, key);
	str = ft_strdup(value);
	*i += ft_strlen(key) + 1;
	free(key);
	free(value);
	return (str);
}

static int is_env_var_start(t_token *token, size_t i)
{
	return (token->txt[i] == '$' && token->txt[i + 1] &&
			(is_alphanumu(token->txt[i + 1]) || token->txt[i + 1] == '?')
			&& token->qtype != SINGLE);
}

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
			result = ft_strjoin(result, temp);
			free(temp);
		}
		else
		{
			buff[0] = token->txt[i++];
			result = ft_strjoin(result, buff);
		}
		if (!result)
			return (NULL);
	}
	return (result);
}