#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token		*current_token;
	t_minishell	shell;

	(void)argc;
	(void)argv;
	
	// Initialize environment and export lists
	shell.our_env = enlist_env(envp);
	if (!shell.our_env)
	{
		printf("Error initializing environment.\n");
		return 1;
	}

	shell.our_exp = env_to_exp(shell.our_env);
	if (!shell.our_exp)
	{
		printf("Error initializing export list.\n");
		free_env(&shell.our_env);
		return 1;
	}

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
		if (!shell.tokens) // Tokenization error handling
		{
			free(input);
			continue;
		}

		// Finalize tokens (variable substitution, etc.)
		finalize_tokens(shell.tokens, shell.our_env);

		// Debug: Print tokens
		current_token = shell.tokens;
		while (current_token)
		{
			printf("Token: '%s', Quote Type: '%s', Space: %d\n", current_token->txt, qtype_to_string(current_token->qtype), current_token->space);
			current_token = current_token->next;
		}

		// Handle 'env' command
		if (ft_strcmp(shell.tokens->txt, "env") == 0)
		{
			t_env *env_current = shell.our_env;
			while (env_current)
			{
				printf("NODE: %s\n", env_current->val);
				env_current = env_current->next;
			}
		}

		// Handle 'exp' command
		else if (ft_strcmp(shell.tokens->txt, "exp") == 0)
		{
			t_exp *exp_current = shell.our_exp;
			while (exp_current)
			{
				printf("NODE: %s\n", exp_current->val);
				exp_current = exp_current->next;
			}
		}

		// Handle 'export' command
		else if (ft_strcmp(shell.tokens->txt, "export") == 0)
		{
			if (shell.tokens->next)
			{
				// Debug print to check what is after 'export'
				printf("Registering export for: '%s'\n", shell.tokens->next->txt);

				// Call register_env_exp with the rest of the command
				register_env_exp(shell.tokens->next->txt, shell.our_env, shell.our_exp);
			}
			else // If 'export' is standalone, print current export list
			{
				t_exp *exp_current = shell.our_exp;
				while (exp_current)
				{
					printf("NODE: %s\n", exp_current->val);
					exp_current = exp_current->next;
				}
			}
		}

		// Handle 'unset' command
		else if (ft_strcmp(shell.tokens->txt, "unset") == 0)
		{
			if (shell.tokens->next)
			{
				// Call ft_unset with the variable to unset
				ft_unset(shell.our_env, shell.our_exp, shell.tokens->next->txt);
			}
			else
			{
				printf("unset: not enough arguments\n");
			}
		}

		// Free tokens and input
		free_tokens(&shell.tokens);
		free(input);
	}

	// Free environment and export lists
	free_env(&shell.our_env);
	free_exp(&shell.our_exp);

	return 0;
}
