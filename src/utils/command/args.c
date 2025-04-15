/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:50:59 by dawwad            #+#    #+#             */
/*   Updated: 2025/03/10 14:50:59 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "command.h"

static t_token	*process_token(t_token *current, int *j,
	size_t *i)
{
	if ((current->txt[0] == '>' || current->txt[0] == '<')
		&& current->qtype == NO)
	{
		if (current->next)
		{
			current = current->next->next;
			*j += 2;
		}
	}
	else if (ft_strcmp(current->txt, "") == 0)
	{
		current = current->next;
		(*j)++;
	}
	else
	{
		(*i)++;
		current = current->next;
		(*j)++;
	}
	return (current);
}

size_t	get_args_size(t_token *token, int limit[2])
{
	size_t	i;
	t_token	*current;
	int		j;

	i = 0;
	current = token;
	j = 0;
	while (j < limit[0] && current)
	{
		current = current->next;
		j++;
	}
	while (current && j < limit[1])
		current = process_token(current, &j, &i);
	return (i);
}

static t_token	*skip_unwanted_tokens(t_token *current, int *j)
{
	while (current
		&& ((current->txt[0] == '>' || current->txt[0] == '<')
			&& current->qtype == NO))
	{
		if (current->next)
		{
			current = current->next->next;
			*j += 2;
		}
		else
			break ;
	}
	while (current && ft_strcmp(current->txt, "") == 0)
	{
		current = current->next;
		(*j)++;
	}
	return (current);
}

static char	**fill_args(t_token *token, int limit[2], char **arrstr)
{
	t_token	*current;
	int		i;
	int		j;

	current = token;
	i = 0;
	j = 0;
	while (j < limit[0] && current)
	{
		current = current->next;
		j++;
	}
	while (current && j < limit[1])
	{
		current = skip_unwanted_tokens(current, &j);
		if (!current || j >= limit[1])
			break ;
		arrstr[i] = ft_strdup(current->txt);
		i++;
		current = current->next;
		j++;
	}
	arrstr[i] = NULL;
	return (arrstr);
}

char	**init_args(t_token *token, int limit[2])
{
	char	**arrstr;
	size_t	size;

	size = get_args_size(token, limit);
	arrstr = (char **)malloc((size + 1) * sizeof(char *));
	if (!arrstr)
		return (NULL);
	return (fill_args(token, limit, arrstr));
}
