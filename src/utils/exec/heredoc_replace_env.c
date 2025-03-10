#include "../../../includes/minishell.h"

static char	*hd_get_next_key(char *str, int start)
{
	int	i;

	start++;
	if (str[start] == '?')
		return (ft_strdup(""));
	i = start;
	if (str[start] >= '0' && str[start] <= '9')
		i++;
	else
	{
		while (str[i] && is_alphanumu(str[i]))
			i++;
	}
	return (ft_substr(str, start, i - start));
}

static char	*hd_handle_env_var(t_env *env, char *string,
	size_t *i)
{
	char	*key;
	char	*value;
	char	*str;

	key = hd_get_next_key(string, *i);
	if (!key)
		return (NULL);
	value = get_next_value(env, key);
	str = ft_strdup(value);
	*i += ft_strlen(key) + 1;
	free(key);
	free(value);
	return (str);
}

static int	hd_is_env_var_start(char *str, size_t i)
{
	if (str[i] == '$' && str[i + 1]
		&& (is_alphanumu(str[i + 1])))
		return (1);
	return (0);
}

static char	*hd_process_env_string(t_env *env, char *str)
{
	char	*result;
	char	*temp;
	size_t	i;
	char	buff[2];

	result = NULL;
	i = 0;
	buff[1] = '\0';
	while (str[i])
	{
		if (hd_is_env_var_start(str, i))
		{
			temp = hd_handle_env_var(env, str, &i);
			result = append_str(result, temp);
			free(temp);
		}
		else
		{
			buff[0] = str[i++];
			result = append_str(result, buff);
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*hd_replace_env(t_env *env, char *str)
{
	char	*new_str;
	char	*old_str;

	if (!str)
		return (NULL);
	new_str = hd_process_env_string(env, str);
	if (!new_str)
		return (NULL);
	old_str = str;
	str = new_str;
	free(old_str);
	return (new_str);
}
