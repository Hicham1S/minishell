#include "tokens.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*trim_str(char *mainstr, int i, int j)
{
	char	*val;
	int		k;

	k = 0;
	val = (char *)malloc((j - i + 1) * sizeof(char));
	if (!val)
		return (NULL);
	while (i < j)
		val[k++] = mainstr[i++];
	val[k] = '\0';
	return (val);
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	handle_single_quote(char *str, int *i, t_token **tokens)
{
	int		j;
	t_qtype	qtype;
	char	*substr;

	qtype = SINGLE;
	(*i)++;
	j = *i;
	while (str[j] && str[j] != '\'')
		j++;
	substr = trim_str(str, *i, j);
	add_token(tokens, create_token(substr, qtype));
	free(substr);
	*i = j + 1;
}

void	handle_double_quote(char *str, int *i, t_token **tokens)
{
	int		j;
	t_qtype	qtype;
	char	*substr;

	qtype = DOUBLE;
	(*i)++;
	j = *i;
	while (str[j] && str[j] != '\"')
		j++;
	substr = trim_str(str, *i, j);
	add_token(tokens, create_token(substr, qtype));
	free(substr);
	*i = j + 1;
}

void	handle_no_quote(char *str, int *i, t_token **tokens)
{
	int		j;
	char	*substr;

	j = *i;
	while (str[j] && !is_space(str[j]) && str[j] != '\'' && str[j] != '\"')
		j++;
	substr = trim_str(str, *i, j);
	add_token(tokens, create_token(substr, NO));
	free(substr);
	*i = j;
}

t_token	*tokenize(char *str)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (str[i] == '\'')
			handle_single_quote(str, &i, &tokens);
		else if (str[i] == '\"')
			handle_double_quote(str, &i, &tokens);
		else
			handle_no_quote(str, &i, &tokens);
	}
	return (tokens);
}

const char *qtype_to_string(t_qtype qtype)
{
	switch (qtype)
	{
		case NO:
			return "NO";
		case SINGLE:
			return "SINGLE";
		case DOUBLE:
			return "DOUBLE";
		default:
			return "UNKNOWN";
	}
}

// int	main(int argc, char *argv[])
// {
// 	char	*input;
// 	t_token	*tokens;
// 	t_token	*current;

// 	if (argc != 2)
// 	{
// 		ft_printf("Usage: %s \"string\"\n", argv[0]);
// 		return (1);
// 	}
// 	input = argv[1];
// 	if (!check_quotation(input))
// 	{
// 		ft_printf("Error: Mismatched quotations\n");
// 		return (1);
// 	}
// 	tokens = enlist_tokens(input);
// 	current = tokens;
// 	while (current)
// 	{
// 		ft_printf("Token: %s, Quote Type: %s\n", current->txt, qtype_to_string(current->qtype));
// 		current = current->next;
// 	}
// 	free_tokens(&tokens);
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token		*current_token;
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.our_env = enlist_env(envp);

	while (1)
	{
		// Get user input
		input = readline("minishell> ");
		if (!input)
			break;

		// Add input to history
		add_history(input);

		// Check for empty input
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}

		// Check for mismatched quotes
		if (!check_quotation(input))
		{
			printf("Error: Mismatched quotations\n");
			free(input);
			continue;
		}

		// Tokenize the input
		shell.tokens = tokenize(input);
		current_token = shell.tokens;

		// Print tokens
		while (current_token)
		{
			printf("Token: %s, Quote Type: %s\n", current_token->txt, qtype_to_string(current_token->qtype));
			current_token = current_token->next;
		}

		// Print environment variables (when using 'env' command)
		if (ft_strncmp(shell.tokens->txt, "env", 3) == 0)
		{
			t_env *env_current = shell.our_env;
			while (env_current)
			{
				printf("NODE: %s\n\n\n", env_current->val);
				env_current = env_current->next;
			}
		}

		// Free tokens and input
		free_tokens(&shell.tokens);
		free(input);
	}

	// Free the environment list
	free_env(&shell.our_env);

	return 0;
}
