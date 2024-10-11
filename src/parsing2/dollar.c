#include "parsing.h"

char	*get_next_dollar(char *str, t_env *my_env, int start)
{
	int		i;
	int		j;
	char	*substr;

	i = start;
	substr = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			j = i;
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			substr = get_env_clone(ft_substr(str, j, i - j), my_env);
			return (substr);
		}
		i++;
	}
	return (substr);
}

char	*append_text_before_dollar(char *res, char *txt, int *i)
{
	int		j;
	char	*temp;
	char	*new_res;

	j = *i;
	while (txt[*i] && txt[*i] != '$')
		(*i)++;
	if (*i > j)
	{
		temp = ft_substr(txt, j, *i - j);
		new_res = ft_strjoin(res, temp);
		free(res);
		free(temp);
		return (new_res);
	}
	return (res);
}

char	*expand_env_var(char *res, char *txt, int *i, t_env *env)
{
	int		j;
	char	*temp;
	char	*env_value;
	char	*new_res;

	j = *i;
	(*i)++;
	while (ft_isalnum(txt[*i]) || txt[*i] == '_')
		(*i)++;
	if (*i > j + 1)
	{
		temp = ft_substr(txt, j + 1, *i - j - 1);
		env_value = get_env_clone(temp, env);
		free(temp);
		if (env_value)
		{
			new_res = ft_strjoin(res, env_value);
			free(res);
			// if (txt[*i] == ' ')
			// {
			// 	char *temp_res = ft_strjoin(new_res, " ");
			// 	free(new_res);
			// 	return temp_res;
			// }
			return new_res;
		}
	}
	return res;
}


void	handle_dollar(t_token *original, t_env *env)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (original->txt[i])
	{
		// Append text before the next dollar sign
		res = append_text_before_dollar(res, original->txt, &i);

		// Handle dollar expansion
		if (original->txt[i] == '$')
			res = expand_env_var(res, original->txt, &i, env);
	}
	free(original->txt);
	original->txt = res;
}

void	do_handle_dollar(t_token *tokens, t_env *env)
{
	t_token *current_token;

	current_token = tokens;
	while (current_token)
	{
		if (current_token->qtype != SINGLE)
			handle_dollar(current_token, env);
		current_token = current_token->next;
	}
}

//doing by hicham
char *dollar_dollar(t_token *token, int i)
{
    char *new_str;
    char *temp;
    char *pid_str;
    pid_t pid;
    int dollar_count = 0;

    pid = getpid();
    pid_str = ft_itoa(pid);
    while (token->txt[i + dollar_count] == '$')
        dollar_count++;
    if (dollar_count > 1)
    {
        new_str = ft_strjoin(ft_substr(token->txt, 0, i), pid_str);
        while (dollar_count-- > 2)
        {
            temp = ft_strjoin(new_str, pid_str);
            free(new_str);
            new_str = temp;
        }
        temp = ft_strjoin(new_str, &token->txt[i + dollar_count]);
        free(new_str);
        free(token->txt);
        token->txt = temp;
    }
    free(pid_str);
    return (token->tx)t;
}

char *dollar_exit_status(t_token *token, int i, int last_exit_status)
{
    char *new_str;
    char *status_str;
    char *temp;
	char *sub_str;

    status_str = ft_itoa(last_exit_status);
	*sub_str = ft_substr(token->txt, 0, i);
    new_str = ft_strjoin(sub_str, status_str);
    free(sub_str);
    temp = ft_strjoin(new_str, &token->txt[i + 2]);
    free(new_str);
    free(status_str);
    free(token->txt);
    token->txt = temp;
    return (token->txt);
}




// int	main(int argc, char **argv, char **envp)
// {
// 	t_env *my_env = enlist_env(envp);
// 	t_token *tokens;
// 	add_token(&tokens, create_token("$hhello $USER--- $HOME $HOME", NO))	;
// 	handle_dollar(tokens, my_env);
// 	if (tokens->txt)
// 		printf("Found: %s\n", tokens->txt);
// 	else
// 		printf("Environment variable not found.\n");
// 		free_tokens(&tokens);
// 		free_env(&my_env);
// 	return 0;
// }
