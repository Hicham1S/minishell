/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:18:40 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/17 13:18:40 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_processes(t_cmd *cmds)
{
	int		status;

	status = 0;
	while (cmds)
	{
		if (waitpid(cmds->pid, &status, 0) == -1)
			return (perror("waitpid"), WEXITSTATUS(status));
		cmds = cmds->next;
	}
	return (WEXITSTATUS(status));
}

static void set_pipes(int pipes[2][2])
{
	pipes[0][0] = 0;
	pipes[0][1] = 0;
	pipes[1][0] = 0;
	pipes[1][1] = 0;
}

static void	close_pipes(int pipes[2][2])
{
	if (pipes[0][0] > 0)
		close(pipes[0][0]);
	if (pipes[0][1] > 0)
		close(pipes[0][1]);
	if (pipes[1][0] > 0)
		close(pipes[1][0]);
	if (pipes[1][1] > 0)
		close(pipes[1][1]);
}

static int	child_process(size_t index, int pipes[2][2],
		t_cmd *cmds, t_env **envs)
{
	int     builtin_exit;
	t_cmd   *cmd;
	size_t  i;

	i = 0;
	cmd = cmds;
	while (i < index)
	{
		cmd = cmd->next;
		i++;
	}
	if (index > 0)
		dup2(pipes[(index-1) % 2][0], STDIN_FILENO);
	if (cmd->next)
		dup2(pipes[index % 2][1], STDOUT_FILENO);
	close_pipes(pipes);
	redirs(cmd);
	close_redirs(cmds);
	builtin_exit = exec_builtin(cmd, envs);
	if (builtin_exit == BUILTIN_NOT_FOUND)
		return (exec_relative(cmd, envs));
	return (builtin_exit);
}

int pipeline(t_cmd *cmds, t_env **envs)
{
	t_cmd   *cmd;
	size_t  i;
	int     pipes[2][2];

	i = 0;
	cmd = cmds;
	set_pipes(pipes);
	while(cmd)
	{
		if (cmd->next && pipe(pipes[i % 2]) == -1)
			return (EXIT_FAILURE);
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (EXIT_FAILURE);
		if (cmd->pid == 0)
			return (child_process(i, pipes, cmds, envs));
		cursor_close(pipes, i, cmd);
		i++;
		cmd = cmd->next;
	}
	return (wait_processes(cmds));
}