/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:45:30 by hsarraj           #+#    #+#             */
/*   Updated: 2025/02/21 14:45:30 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	setup_signals(void (**old_int)(int), void (**old_quit)(int))
{
	*old_int = signal(SIGINT, SIG_IGN);
	*old_quit = signal(SIGQUIT, SIG_IGN);
}

int	fork_child(t_exec *exec, size_t i, int pipes[2][2])
{
	t_cmd	*cmd;
	t_env	**envs;

	cmd = exec->cmds;
	envs = exec->envs;
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (EXIT_FAILURE);
	if (cmd->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit(child_process(i, pipes, cmd, envs));
	}
	return (EXIT_SUCCESS);
}

int	execute_pipeline(t_exec *exec, int pipes[2][2])
{
	t_cmd	*cmd;
	size_t	i;
	int		status;

	cmd = exec->cmds;
	i = 0;
	while (cmd)
	{
		if (cmd->next && pipe(pipes[i % 2]) == -1)
			return (EXIT_FAILURE);
		status = fork_child(exec, i, pipes);
		if (status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		close_pipes(pipes, i, cmd);
		i++;
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
