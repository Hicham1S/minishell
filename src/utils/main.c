#include "../../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_env	*env;
	t_cmd	*cmd;
	
	(void)argc;
	(void)argv;
	env = init_env(envp);

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		if (unmatched_quotes(input))
		{
			printf("Error: Unmatched quotes\n");
			free(input);
			continue;
		}
		tokens = init_tokens(input);
		if (redir_check(tokens, env))
		{
			replace_tokens_with_env(env, tokens);
			merge_tokens(&tokens);
			printf("\n\n\nParsed Tokens with Replaced Variables:\n");
			print_tokens(tokens);
			cmd = init_cmd(tokens);
			print_cmd(cmd);
			free_cmd(cmd);
		}
		if (tokens)
			free_tokens(&tokens);
		free(input);
	}
	free(env);
	return (0);
}