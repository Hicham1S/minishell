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

#include "minishell.h"

int wait_processes(t_cmd *cmds)
{
	int		status;

	status = 0;
	while (cmds)
	{
		if (waitpid(cmds->pid, &status, 0) == -1)
			return (perror("waitpid"), WEXITSTATUS(status));
		cmds = cmds->next;
	}
	retrun (WEXITSTATUS(status));
}

bool    is_child_process(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->pid == 0)
			return (true);
		cmds = cmds->next;
	}
	return (false);
}