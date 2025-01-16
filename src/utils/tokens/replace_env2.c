#include "../../../includes/minishell.h"
#include "tokens.h"

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
		current = current->next;
	}
}

static void	print_tokens(t_token *token)
{
	if (!token)
	{
		printf("no tokens inserted");
		return;
	}
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
		if (!tokens)
			continue;
		replace_tokens_with_env(env, tokens);
		if (redir_check(tokens, env))
		{
			printf("Parsed Tokens with Replaced Variables:\n");
			print_tokens(tokens);
		}
		if (tokens)
			free_tokens(&tokens);
		free(input);
	}
	free(env);
	return (0);
}