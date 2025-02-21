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

/* Close the necessary pipe ends based on the command index */
static void	close_pipes(int pipes[2][2], size_t i, t_cmd *cmd)
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

/* Set the initial state of the pipes (set them to 0) */
static void	set_pipes(int pipes[2][2])
{
	pipes[0][0] = 0;
	pipes[0][1] = 0;
	pipes[1][0] = 0;
	pipes[1][1] = 0;
}

/* Close all pipe ends in use */
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

/* Handle the execution of each child process */
static int	child_process(size_t index, int pipes[2][2],
		t_cmd *cmds, t_env **envs)
{
	int		builtin_exit;
	t_cmd	*cmd;
	size_t	i;
	int		result;

	i = 0;
	cmd = cmds;
	while (i < index)
	{
		cmd = cmd->next;
		i++;
	}
	if (index > 0)
		dup2(pipes[(index - 1) % 2][0], STDIN_FILENO);
	if (cmd->next)
		dup2(pipes[index % 2][1], STDOUT_FILENO);
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


int pipeline(t_cmd *cmds, t_env **envs)
{
    t_cmd   *cmd;
    size_t  i;
    int     pipes[2][2];
    int     status;

    i = 0;
    cmd = cmds;
    set_pipes(pipes);
    
    // Save parent's signal handlers
    void (*old_int)(int) = signal(SIGINT, SIG_IGN);
    void (*old_quit)(int) = signal(SIGQUIT, SIG_IGN);

    while (cmd)
    {
        if (cmd->next && pipe(pipes[i % 2]) == -1)
            return (EXIT_FAILURE);
        cmd->pid = fork();
        if (cmd->pid == -1)
            return (EXIT_FAILURE);
        if (cmd->pid == 0)
        {
            // Child process gets default signal handling
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            return (child_process(i, pipes, cmds, envs));
        }
        close_pipes(pipes, i, cmd);
        i++;
        cmd = cmd->next;
    }
    
    // Restore parent's signal handlers before waiting
    signal(SIGINT, old_int);
    signal(SIGQUIT, old_quit);
    
    status = wait_processes(cmds);
    return (status);
}