#include "../../../includes/minishell.h"
#include "tokens.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	old_size;

	if (!ptr)
		return (malloc(size));
	if (!size)
		return (free(ptr), NULL);
	old_size = ft_strlen(ptr) + 1;
	new_ptr = malloc(size);
	if (!new_ptr)
		return (free(ptr), NULL);
	ft_memcpy(new_ptr, ptr, old_size < size ? old_size : size);
	free(ptr);
	return (new_ptr);
}

static size_t	calc_new_len(char *str, t_env *env)
{
	size_t	len;

	if (!str || !env)
		return (0);
	len = ft_strlen(str);
	if (!env->value)
		return (len - ft_strlen(env->key) - 1);
	return (len - ft_strlen(env->key) - 1 + ft_strlen(env->value));
}

static char	*get_next_key(t_token *token, int start)
{
	int	i;

	start++;
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

static char	*append_str(char *str, const char *append)
{
	char	*new_str;
	size_t	str_len;
	size_t	append_len;

	if (!append)
		return (str);
	str_len = str ? ft_strlen(str) : 0;
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

static char	*handle_env_var(t_env *env, t_token *token,
		size_t *i)
{
	char	*key;
	char	*value;
	char	*str;

	key = get_next_key(token, *i);
	if (!key)
		return (NULL);
	value = get_next_value(env, key);
	str = append_str(NULL, value);
	*i += ft_strlen(key) + 1;
	free(key);
	free(value);
	return (str);
}

static int is_env_var_start(t_token *token, size_t i)
{
	return (token->txt[i] == '$' && token->txt[i + 1] &&
		   is_alphanumu(token->txt[i + 1]) && token->qtype != SINGLE);
}

static char	*process_env_string(t_env *env, t_token *token)
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
		current = current->next;
	}
}

static void	print_tokens(t_token *token)
{
	while (token)
	{
		if (token->txt)
			printf("Token: '%s', Type: %d\n", token->txt, token->qtype);
		token = token->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = init_tokens(input);
		replace_tokens_with_env(env, tokens);
		printf("Parsed Tokens with Replaced Variables:\n");
		print_tokens(tokens);
		free_tokens(&tokens);
		free(input);
	}
	free(env);
	return (0);
}