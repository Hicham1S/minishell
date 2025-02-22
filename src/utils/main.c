#include "../../includes/minishell.h"

int	g_sginal = 0;

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
	char			*input;
	t_cmd			*cmd;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		init_signal();
		g_sginal = 0;
		input = readline("minishell> ");
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(0);
		}
		if (*input)
			add_history(input);
		if (unmatched_quotes(input))
		{
			ft_putendl_fd("Error: Mismatched quotes", STDERR_FILENO);
			free(input);
			continue ;
		}
		cmd = input_to_cmd(input, env);
		if (cmd)
		{
			exec_cmd(cmd, &env);
			free_cmd(cmd);
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!minishell)
		return (1);
	minishell->envs = init_env(envp);
	readline_loop(minishell->envs);
	free(minishell->envs);
	free(minishell);
	return (g_sginal);
}
