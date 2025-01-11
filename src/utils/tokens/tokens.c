#include "../../../includes/minishell.h"
#include "tokens.h"

void    add_token(t_token **token, char *txt, t_qtype qtype)
{
	t_token *new;
	t_token *current;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return;
	new->txt = ft_strdup(txt);
	if (!new->txt)
	{
		free(new);
		return;
	}
	new->qtype = qtype;
	new->next = NULL;
	if (!(*token))
	{
		*token = new;
		return;
	}
	current = *token;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		temp = current->next;
		free(current->txt); 
		free(current);
		current = temp;
	}
	*tokens = NULL;
}

int double_quotes(t_token **token, char *str, int *i)
{
	int     j;
	char    *sub;
	
	if (str[*i] == '\"')
	{
		(*i)++;
		j = *i;
		while (str[j] != '\"' && str[j] != '\0')
			j++;
		if (str[j] == '\0')
			return (0);
		sub = ft_substr(str, *i, j - *i);
		if (!sub)
			return (0);
		add_token(token, sub, DOUBLE);
		free(sub);
		*i = j + 1;
		return (1);
	}
	return (0);
}

int single_quotes(t_token **token, char *str, int *i)
{
	int     j;
	char    *sub;
	
	if (str[*i] == '\'')
	{
		(*i)++;
		j = *i;
		while (str[j] != '\'' && str[j] != '\0')
			j++;
		if (str[j] == '\0')
			return (0);
		sub = ft_substr(str, *i, j - *i);
		if (!sub)
			return (0);
		add_token(token, sub, SINGLE);
		free(sub);
		*i = j + 1;
		return (1);
	}
	return (0);
}

int no_quotes(t_token **token, char *str, int *i)
{
	int     j;
	char    *sub;

	while (is_space(str[*i]))
		(*i)++;
	j = *i;
	while (str[*i] && !is_quote(str[*i])
		&& !is_space(str[*i]) && !is_redir(str[*i]))
		(*i)++;
	if (*i > j)
	{
		sub = ft_substr(str, j, *i - j);
		if (sub)
		{
			add_token(token, sub, NO);
			free(sub);
		}
	}
	return (1);
}

int	redir_token(t_token **token, char *str, int *i)
{
	char	*sub;

	if (is_redir(str[*i]))
	{
		if (str[*i] == str[*i + 1])
		{
			sub = ft_substr(str, *i, 2);
			add_token(token, sub, NO);
			free(sub);
			*i += 2;
		}
		else
		{
			sub = ft_substr(str, *i, 1);
			add_token(token, sub, NO);
			free(sub);
			(*i)++;
		}
		return (1);
	}
	return (0);
}

void parse_token(t_token **token, char *str, int *i)
{
	if (is_quote(str[*i]) == 1) // Single quote
	{
		if (!single_quotes(token, str, i))
			return;
	}
	else if (is_quote(str[*i]) == 2) // Double quote
	{
		if (!double_quotes(token, str, i))
			return;
	}
	else if (is_redir(str[*i])) // Redirection
	{
		if (!redir_token(token, str, i))
			return;
	}
	else if (!is_space(str[*i])) // No quotes and not a space
	{
		if (!no_quotes(token, str, i))
			return;
	}
	else
		(*i)++; // Skip spaces
}

t_token *init_tokens(char *str)
{
	int     i;
	t_token *token;

	i = 0;
	token = NULL;
	while (str[i] != '\0')
		parse_token(&token, str, &i);
	return (token);
}

static void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("Token: '%s', Type: %d\n", token->txt, token->qtype);
		token = token->next;
	}
}

// #include <readline/readline.h>
// #include <readline/history.h>

// int main(void)
// {
// 	char *input;
// 	t_token *tokens;

// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input) // Exit on EOF (Ctrl+D)
// 		{
// 			printf("exit\n");
// 			break;
// 		}

// 		if (*input) // Add non-empty input to history
// 			add_history(input);

// 		tokens = init_tokens(input);

// 		printf("Parsed Tokens:\n");
// 		print_tokens(tokens);

// 		free_tokens(&tokens);
// 		free(input);
// 	}

// 	return 0;
// }