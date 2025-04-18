/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:52:32 by dawwad            #+#    #+#             */
/*   Updated: 2025/03/10 14:52:32 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		cmd = init_cmd(env, tokens);
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
	int				last_signal;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	init_signal();
	last_signal = 0;
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		if (g_signal > 0)
			last_signal = g_signal;
		g_signal = 0;
		input = readline("minishell> ");
		if (last_signal > 0)
		{
			set_stat(&env, (128 + last_signal));
			last_signal = 0;
		}
		process_input(input, env);
	}
}

int	get_stat(t_env *envs)
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
