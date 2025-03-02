#include "../../includes/minishell.h"

int	g_signal = 0;

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

void	process_input(char *input, t_env *env)
{
	t_cmd	*cmd;

	if (g_signal > 0)
		set_stat(&env, (128 + g_signal));
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
		return ;
	}
	cmd = input_to_cmd(input, env);
	if (cmd)
	{
		exec_cmd(cmd, &env);
		free_cmd(cmd);
	}
	free(input);
}

void	readline_loop(t_env *env)
{
	char			*input;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	init_signal();
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		g_signal = 0;
		input = readline("minishell> ");
		process_input(input, env);
	}
}

static int	get_stat(t_env *envs)
{
	t_env	*curr;

	curr = get_env(envs, "?");
	return (ft_atoi(curr->value));
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	int			status;

	(void)argc;
	(void)argv;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!minishell)
		return (1);
	minishell->envs = init_env(envp);
	readline_loop(minishell->envs);
	status = get_stat(minishell->envs);
	free(minishell->envs);
	free(minishell);
	return (status);
}
