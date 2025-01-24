#include "../../../includes/minishell.h"
#include "command.h"

t_cmd	*new_cmd(t_token *token, int limit[2])
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
	return (new);
}

void	setup_cmd(t_cmd *cmd, t_token *token, int limit[2])
{
	t_token	*current;
	int		j;

	current = token;
	j = 0;
	while (j < limit[0] && current)
	{
		current = current->next;
		j++;
	}
	while (current && j < limit[1])
	{
		if (ft_strcmp(current->txt, "<<") == 0)
			cmd->has_heredoc = 1;
		j++;
		current = current->next;
	}
	if (current && current->txt[0] == '|' && current->qtype == NO)
		cmd->has_pipe = 1;
}

t_cmd	*init_cmd(t_token *token)
{
	int	limit[2];

	limit[0] = 0;
	limit[1] = 0;
	while (token)
	{
		while (token && token->txt)
	}
}