/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:52:29 by dawwad            #+#    #+#             */
/*   Updated: 2025/03/10 14:52:29 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_token *token)
{
	if (!token)
	{
		printf("no tokens inserted");
		return ;
	}
	while (token)
	{
		if (token->txt)
			printf("Token: '%s', Type: %d, Flag: %d\n", token->txt,
				token->qtype, token->merge_next);
		token = token->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;

	current = cmd;
	while (current)
	{
		printf("Command: \n");
		printf("Infile: %d\n", current->infile);
		printf("Outfile: %d\n", current->outfile);
		printf("Has Pipe: %d\n", current->has_pipe);
		printf("Has Heredoc: %d\n", current->has_heredoc);
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				printf("Arg[%d]: %s\n", i, current->args[i]);
				i++;
			}
		}
		current = current->next;
	}
}
