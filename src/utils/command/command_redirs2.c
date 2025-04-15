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

static void	process_redir_loop(t_cmd *cmd, t_token **current, int *i, int limit)
{
	while (*current && *i < limit)
	{
		process_redir(cmd, current);
		if (!*current)
			return ;
		*current = (*current)->next;
		(*i)++;
	}
}

void	cmd_redirs(t_env *envs, t_cmd *cmd, t_token *token, int limit[2])
{
	int		i;
	t_token	*current;

	i = -1;
	current = token;
	while (++i < limit[0] && current)
		current = current->next;
	process_redir_loop(cmd, &current, &i, limit[1]);
	i = -1;
	current = token;
	while (++i < limit[0] && current)
		current = current->next;
	while (current && i < limit[1])
	{
		process_redir2(envs, cmd, &current);
		if (!current)
			return ;
		current = current->next;
		i++;
	}
}
