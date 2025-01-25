#include "../../../includes/minishell.h"
#include "command.h"

void	cmd_redirs(t_cmd *cmd, t_token *token, int limit[2])
{
	int		i;
	t_token	*current;

	i = 0;
	current = token;
	while (i < limit[0] && current)
	{
		current = current->next;
		i++;
	}
	while (current && i < limit[1])
	{
		if (is_redir_token(current, "") && current->txt[0] == '>')
		{
			if (cmd->outfile > 2)
				close(cmd->outfile);
			if (current->next && is_redir_token(current, ">>"))
				cmd->outfile = open(current->next->txt, O_WRONLY
						| O_CREAT | O_APPEND, 0644);
			else if (current->next && is_redir_token(current, ">"))
				cmd->outfile = open(current->next->txt, O_WRONLY
						| O_CREAT | O_TRUNC, 0644);
		}
		if (is_redir_token(current, "") && current->txt[0] == '<')
		{
			if (cmd->infile > 2)
				close(cmd->infile);
			if (current->next && is_redir_token(current, "<"))
				cmd->infile = open(current->next->txt, O_RDONLY);
		}
		if (is_redir_token(current, "<<"))
		{
			cmd->has_heredoc = 1;
			if (current->next)
				current = current->next;
		}
		current = current->next;
		i++;
	}
}

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
	cmd_redirs(new, token, limit);
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

t_cmd	*init_cmd(t_token *token)
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
		while (current && !is_redir_token(current, "|"))
		{
			limit[1]++;
			current = current->next;
		}
		new = new_cmd(token, limit);
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
