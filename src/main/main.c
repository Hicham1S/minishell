#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token		*current_token;
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.our_env = enlist_env(envp);
	shell.our_exp = env_to_exp(shell.our_env);

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
		if (ft_strncmp(shell.tokens->txt, "exp", 3) == 0)
		{
			t_exp *exp_current = shell.our_exp;
			while (exp_current)
			{
				printf("NODE: %s\n\n\n", exp_current->val);
				exp_current = exp_current->next;
			}
		}
		if (ft_strncmp(shell.tokens->txt, "pwd", 3) == 0)
		{
			pwd(shell.our_env);
		}
		if (ft_strncmp(shell.tokens->txt, "$HOME", 5) == 0)
			ft_printf("%s\n", get_env_clone("HOME", shell.our_env));
		// Free tokens and input
		free_tokens(&shell.tokens);
		free(input);
	}

	// Free the environment list
	free_env(&shell.our_env);
	free_exp(&shell.our_exp);

	return 0;
}
