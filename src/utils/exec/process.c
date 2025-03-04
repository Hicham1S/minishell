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

int	wait_processes(t_cmd *cmds)
{
	int	status;
	int	last_status = 0;

	while (cmds)
	{
		if (waitpid(cmds->pid, &status, 0) == -1)
		{
			perror("waitpid");
			last_status = 1;
			printf("wait2: %d\n", last_status);
		}
		else
		{
			last_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
			printf("wait4: %d\n", last_status);
		}
		cmds = cmds->next;
	}
	return (last_status);
}
