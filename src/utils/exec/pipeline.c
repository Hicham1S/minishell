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

#include "../../../includes/minishell.h"

void	close_pipes(int pipes[2][2], size_t i, t_cmd *cmd)
{
	if (i > 0)
	{
		close(pipes[(i - 1) % 2][0]);
	}
	if (cmd->next)
	{
		close(pipes[i % 2][1]);
	}
}

static void	set_pipes(int pipes[2][2])
{
	pipes[0][0] = 0;
	pipes[0][1] = 0;
	pipes[1][0] = 0;
	pipes[1][1] = 0;
}

static void	close_all_pipes(int pipes[2][2])
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

int	child_processpipe(size_t index, int pipes[2][2],
		t_cmd *cmds, t_env **envs)
{
	int		builtin_exit;
	t_cmd	*cmd;
	size_t	i;
	int		result;

	i = -1;
	cmd = cmds;
	while (++i < index)
		cmd = cmd->next;
	if (index > 0 && dup2(pipes[(index - 1) % 2][0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (cmd->next && dup2(pipes[index % 2][1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_all_pipes(pipes);
	redirs(cmd);
	close_redirs(cmd);
	builtin_exit = exec_builtin(cmd, envs);
	if (builtin_exit == BUILTIN_NOT_FOUND)
	{
		result = exec_relative(cmd, envs);
		exit(result);
	}
	exit(builtin_exit);
}

int	pipeline(t_cmd *cmds, t_env **envs)
{
	int		pipes[2][2];
	int		status;
	void	(*old_int)(int);
	void	(*old_quit)(int);
	t_exec	exec;

	exec.cmds = cmds;
	exec.envs = envs;
	set_pipes(pipes);
	setup_signals(&old_int, &old_quit);
	if (execute_pipeline(&exec, pipes) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	signal(SIGINT, old_int);
	signal(SIGQUIT, old_quit);
	status = wait_processes(cmds);
	set_stat(envs, status);
	return (status);
}
