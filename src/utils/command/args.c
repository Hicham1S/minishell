#include "../../../includes/minishell.h"
#include "command.h"

static size_t	get_args_size(t_token *token, int limit[2])
{
	size_t	i;
	t_token	*current;

	i = -1;
	current = token;
	while (++i < (size_t)limit[0] && current)
		current = current->next;
	i = 0;
	while (current
		&& (size_t)limit[0] + i < (size_t)limit[1])
	{
		if ((current->txt[0] == '>' || current->txt[0] == '<')
			&& current->qtype == NO)
			current = current->next->next;
		else if (ft_strcmp(current->txt, "") == 0)
			current = current->next;
		else
		{
			i++;
			current = current->next;
		}
	}
	return (i);
}

static t_token	*filter_token(t_token *current, int *j)
{
	if ((current->txt[0] == '>'
			|| current->txt[0] == '<') && current->qtype == NO)
	{
		if (current->next)
			current = current->next->next;
		(*j)++;
	}
	else if (ft_strcmp(current->txt, "") == 0)
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
		current = filter_token(current, &j);
		if (!current || j >= limit[1])
			break ;
		arrstr[i++] = ft_strdup(current->txt);
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
