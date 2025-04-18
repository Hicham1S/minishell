/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:54:34 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/28 17:54:34 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	redirs(t_cmd *cmd)
{
	if (cmd->infile >= 0)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile >= 0)
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

void	handle_heredoc_line(t_env *envs, char *line, int write_fd)
{
	char	*expanded_line;

	expanded_line = hd_replace_env(envs, line);
	if (!expanded_line)
		return ;
	write(write_fd, expanded_line, ft_strlen(expanded_line));
	write(write_fd, "\n", 1);
	free(expanded_line);
}
