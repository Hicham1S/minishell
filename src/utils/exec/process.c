/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:58:56 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/21 11:58:56 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count_cmds(t_cmd *cmds)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	tmp = cmds;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	wait_for_cmd(t_cmd *cmds, int *exit_statuses, int *count)
{
	int	status;

	if (waitpid(cmds->pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit_statuses[*count] = 1;
	}
	else
	{
		if ((status & 0x7F) == 0)
			exit_statuses[*count] = (status >> 8) & 0xFF;
		else
			exit_statuses[*count] = 128 + (status & 0x7F);
	}
	(*count)++;
}

int	wait_processes(t_cmd *cmds)
{
	int	*exit_statuses;
	int	count;

	count = count_cmds(cmds);
	exit_statuses = malloc(sizeof(int) * count);
	if (!exit_statuses)
		return (1);
	count = 0;
	while (cmds)
	{
		wait_for_cmd(cmds, exit_statuses, &count);
		cmds = cmds->next;
	}
	count = exit_statuses[0];
	free(exit_statuses);
	return (count);
}
