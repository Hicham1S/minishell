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

#include "../../../includes/minishell.h"

static void	reopen_heredoc(t_cmd *cmd)
{
    if (cmd->infile >= 0)
        close(cmd->infile);
    cmd->infile = open(HEREDOC_FILE, O_RDONLY);
    if (cmd->infile < 0)
        perror("Error reopening heredoc");
}

bool	redir_heredoc(char *delimiter, t_cmd *cmd)
{
	char	*line;

	cmd->infile = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->infile < 0)
		return (error("heredoc", strerror(errno)), false);
	cmd->has_heredoc = true;
	while (1)
	{
		signal(SIGINT, &heredoc_signal);
		signal(SIGQUIT, SIG_IGN);
		rl_getc_function = getc;
		line = readline("> ");
		if (!line && g_exit_status == 130)
			break ;
		else if (!line)
			return (reopen_heredoc(cmd), error_heredoc(delimiter), true);
		if (ft_strcmp(line, delimiter) == 0)
			return (reopen_heredoc(cmd), free(line), true);
		ft_putendl_fd(line, cmd->infile);
		free(line);
	}
	redir_heredoc2(cmd);
	return (true);
}

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
