#include "../../../includes/minishell.h"
#include "tokens.h"

char	*get_next_key(t_token *token, int start)
{
	int	i;

	start++;
	if (token->txt[start] == '?')
		return (ft_strdup("?"));
	i = start;
	if (token->txt[start] >= '0' && token->txt[start] <= '9')
		i++;
	else
	{
		while (token->txt[i] && is_alphanumu(token->txt[i]))
			i++;
	}
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

char	*append_str(char *str, const char *append)
{
	char	*new_str;
	size_t	str_len;
	size_t	append_len;

	if (!append)
		return (str);
	if (str)
		str_len = ft_strlen(str);
	else
		str_len = 0;
	append_len = ft_strlen(append);
	new_str = malloc(str_len + append_len + 1);
	if (!new_str)
		return (free(str), NULL);
	if (str)
		ft_strlcpy(new_str, str, str_len + 1);
	else
		new_str[0] = '\0';
	ft_strlcat(new_str, append, str_len + append_len + 1);
	free(str);
	return (new_str);
}

int	is_env_var_start(t_token *token, size_t i)
{
	if (token->txt[i] == '$' && token->txt[i + 1]
		&& (is_alphanumu(token->txt[i + 1]) || token->txt[i + 1] == '?')
		&& token->qtype != SINGLE)
		return (1);
	if (token->txt[i] == '$' && token->txt[i + 1] == '\0'
		&& token->next && token->next->qtype != NO
		&& token->merge_next == 1 && token->qtype == NO)
		return (1);
	return (0);
}
