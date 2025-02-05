#include "../../includes/minishell.h"

int g_exit_status = 0;

t_cmd	*input_to_cmd(char *input, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmd;

	cmd = NULL;
	tokens = init_tokens(input);
	if (redir_check(tokens, env))
	{
		replace_tokens_with_env(env, tokens);
		merge_tokens(&tokens);
		cmd = init_cmd(tokens);
	}
	if (tokens)
		free_tokens(&tokens);
	return (cmd);
}

void	readline_loop(t_env *env)
{
	char	*input;
	t_cmd	*cmd;

	while (1)
	{
		// Read input with a terminal-like prompt
		input = readline("minishell> ");
		if (!input)
		{
			// If user exits (Ctrl-D), exit gracefully
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);

		// Check for unmatched quotes in the input
		if (unmatched_quotes(input))
		{
			printf("Error: Mismatched quotes\n");
			free(input);
			continue ;
		}

		// Tokenize and process the input to generate a command structure
		cmd = input_to_cmd(input, env);
		
		// Execute the command
		if (cmd)
		{
			exec_cmd(cmd, &env);
			free_cmd(cmd);  // Free after execution
		}

		// Free input after execution
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;

	// Initialize the minishell struct and environment variables
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!minishell)
		return (1);  // Memory allocation failure
	minishell->envs = init_env(envp);

	// Start the readline loop to handle user input
	readline_loop(minishell->envs);

	// Cleanup environment variables
	free(minishell->envs);

	// Free the minishell structure itself
	free(minishell);

	return (g_exit_status);  // Return the global exit status
}
