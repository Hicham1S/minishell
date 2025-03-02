/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:39:25 by hsarraj           #+#    #+#             */
/*   Updated: 2025/02/08 14:39:25 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "command.h"

void	handle_output_redirs(t_cmd *cmd, t_token *current)
{
	if (cmd->outfile > 2)
		close(cmd->outfile);
	if (is_redir_token(current, ">>"))
		cmd->outfile = open(current->next->txt,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (is_redir_token(current, ">"))
		cmd->outfile = open(current->next->txt,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile < 0)
	{
		perror("minishell");
		cmd->outfile = -2;
	}
}

void	handle_input_redirs(t_cmd *cmd, t_token *current)
{
	if (cmd->infile > 2)
		close(cmd->infile);
	cmd->infile = open(current->next->txt, O_RDONLY);
	if (cmd->infile < 0)
	{
		perror("minishell");
		cmd->infile = -2;
	}
}

t_token	*handle_heredoc_redir(t_cmd *cmd, t_token *current)
{
	while (current && current->next && ft_strcmp(current->txt, "<<") == 0)
	{
		if (!redir_heredoc(current->next->txt, cmd))
			return (NULL);
		current = current->next->next;
	}
	return (current);
}

void	process_redir(t_cmd *cmd, t_token **current)
{
	if (is_redir_token(*current, ">>") || is_redir_token(*current, ">"))
	{
		if ((*current)->next)
			handle_output_redirs(cmd, *current);
	}
	else if (is_redir_token(*current, "<"))
	{
		if ((*current)->next)
			handle_input_redirs(cmd, *current);
	}
	else if (is_redir_token(*current, "<<"))
	{
		*current = handle_heredoc_redir(cmd, *current);
		if (!*current)
			return ;
	}
}

void	cmd_redirs(t_cmd *cmd, t_token *token, int limit[2])
{
	int		i;
	t_token	*current;

	i = -1;
	current = token;
	while (++i < limit[0] && current)
		current = current->next;
	while (current && i < limit[1])
	{
		process_redir(cmd, &current);
		if (!current)
			return ;
		current = current->next;
		i++;
	}
}
