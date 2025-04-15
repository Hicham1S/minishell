/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:51:07 by dawwad            #+#    #+#             */
/*   Updated: 2025/03/10 14:51:07 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "command.h"

t_cmd	*new_cmd(t_env *envs, t_token *token, int limit[2])
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->infile = -1;
	new->outfile = -1;
	new->pid = -1;
	new->has_pipe = 0;
	new->has_heredoc = 0;
	new->next = NULL;
	new->args = init_args(token, limit);
	cmd_redirs(envs, new, token, limit);
	return (new);
}

void	add_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*current;

	if (!new)
		return ;
	if (!*cmd)
		*cmd = new;
	else
	{
		current = *cmd;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static void	skip_non_pipe_tokens(t_token **current, int *limit)
{
	while (*current && !is_redir_token(*current, "|"))
	{
		(*limit)++;
		*current = (*current)->next;
	}
}

t_cmd	*init_cmd(t_env *envs, t_token *token)
{
	int		limit[2];
	t_token	*current;
	t_cmd	*cmd;
	t_cmd	*new;

	cmd = NULL;
	limit[0] = 0;
	limit[1] = 0;
	current = token;
	while (current)
	{
		skip_non_pipe_tokens(&current, &limit[1]);
		new = new_cmd(envs, token, limit);
		if (!new)
			return (NULL);
		if (current && is_redir_token(current, "|"))
			new->has_pipe = 1;
		add_cmd(&cmd, new);
		if (current && is_redir_token(current, "|"))
			current = current->next;
		limit[0] = limit[1] + 1;
		limit[1]++;
	}
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	while (cmd)
	{
		temp = cmd->next;
		if (cmd->args)
		{
			i = -1;
			while (cmd->args[++i] != NULL)
				free(cmd->args[i]);
			free(cmd->args);
			cmd->args = NULL;
		}
		if (cmd->infile > 2)
			close(cmd->infile);
		cmd->infile = -1;
		if (cmd->outfile > 2)
			close(cmd->outfile);
		cmd->outfile = -1;
		free(cmd);
		cmd = temp;
	}
}
