#include "../../../includes/minishell.h"
#include "command.h"

void	handle_output_redirs(t_cmd *cmd, t_token *current)
{
	if (cmd->outfile > 2)
		close(cmd->outfile);
	if (is_redir_token(current, ">>"))
		cmd->outfile = open(current->next->txt, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	else if (is_redir_token(current, ">"))
		cmd->outfile = open(current->next->txt, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
}

void	handle_input_redirs(t_cmd *cmd, t_token *current)
{
	if (cmd->infile > 2)
		close(cmd->infile);
	if (is_redir_token(current, "<"))
		cmd->infile = open(current->next->txt, O_RDONLY);
}

t_token	*handle_heredoc_redir(t_cmd *cmd, t_token *current)
{
	cmd->has_heredoc = 1;
	if (current->next)
		current = current->next;
	return (current);
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
		if (is_redir_token(current, ">>") || is_redir_token(current, ">"))
		{
			if (current->next)
				handle_output_redirs(cmd, current);
		}
		else if (is_redir_token(current, "<"))
		{
			if (current->next)
				handle_input_redirs(cmd, current);
		}
		else if (is_redir_token(current, "<<"))
			current = handle_heredoc_redir(cmd, current);
		current = current->next;
		i++;
	}
}
