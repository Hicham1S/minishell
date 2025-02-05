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
		printf("\n\n\nParsed Tokens with Replaced Variables:\n");
		print_tokens(tokens);
		cmd = init_cmd(tokens);
		print_cmd(cmd);
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
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (unmatched_quotes(input))
		{
			printf("Error: Mismatched quotes\n");
			free(input);
			continue ;
		}
		cmd = input_to_cmd(input, env);
		exec_cmd(cmd, &env);
		free_cmd(cmd);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	minishell->envs = init_env(envp);
	readline_loop(minishell->envs);
	free(minishell->envs);
	return (0);
}
