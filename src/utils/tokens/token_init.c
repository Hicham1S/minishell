#include "../../../includes/minishell.h"
#include "tokens.h"

int	unmatched_quotes(char *str)
{
	int	i;
	int	c;
	
	i = 0;
	c = 0;
	while (str[i])
	{
		if (c == 0 && is_quote(str[i]))
			c = str[i];
		else if (is_quote(c) && str[i] == c)
			c = 0;
		i++;
	}
	return (c);
}

t_token *init_tokens(char *str)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	if (unmatched_quotes(str))
	{
		printf("Unmatched Quotes.\n");
		return (NULL);
	}
	while (str[i] != '\0')
		parse_token(&token, str, &i);
	return (token);
}

// static void	print_tokens(t_token *token)
// {
// 	while (token)
// 	{
// 		printf("Token: '%s', Type: %d\n", token->txt, token->qtype);
// 		token = token->next;
// 	}
// }

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