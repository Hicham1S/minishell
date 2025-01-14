/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:48:09 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/12 10:48:09 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirs(t_cmd *cmd)
{
	if (cmd->infile > 0)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile > 0)
		dup2(cmd->outfile, STDOUT_FILENO);
}

void	close_redirs(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->infile > 2)
			close(cmds->infile);
		if (cmds->outfile > 2)
			close(cmds->outfile);
		if (cmds->has_heredoc)
			unlink(HEREDOC_FILE);
		cmds = cmds->next;
	}
}
