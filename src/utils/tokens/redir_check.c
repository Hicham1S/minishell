#include "../../../includes/minishell.h"
#include "tokens.h"

int	print_unexpected(t_env *env, char *token, int new_status)
{
	char	*temp;

	temp = ft_itoa(new_status);
	printf("-bash: syntax error near unexpected token `%s'\n", token);
	set_env(&env, "?", temp);
	free(temp);
	return (0);
}

int	is_redir_token(t_token *token, char *to_compare)
{
	if (!token || token->qtype != NO)
		return (0);
	if (to_compare && ft_strcmp(to_compare, "") != 0)
		return (ft_strcmp(token->txt, to_compare) == 0);
	return (ft_strcmp(token->txt, "<") == 0
		|| ft_strcmp(token->txt, "<<") == 0
		|| ft_strcmp(token->txt, ">") == 0
		|| ft_strcmp(token->txt, ">>") == 0
		|| ft_strcmp(token->txt, "|") == 0);
}

static int	check_and(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (ft_strcmp(current->txt, "||") == 0
			&& current->qtype == NO)
			return (0);
		current = current->next;
	}
	return (1);
}

int	redir_check(t_token *token, t_env *env)
{
	t_token	*current;

	current = token;
	if (is_redir_token(current, "|") || !check_and(token))
		return (print_unexpected(env, "|", 2));
	while (current && current->next)
	{
		if (is_redir_token(current, "")
			&& is_redir_token(current->next, ""))
		{
			if (is_redir_token(current, "|")
				&& is_redir_token(current->next, "<<"))
				;
			else if (is_redir_token(current, "|")
				|| is_redir_token(current->next, "|"))
				return (print_unexpected(env, "|", 2));
			else
				return (print_unexpected(env, current->next->txt, 2));
		}
		current = current->next;
	}
	if (current && is_redir_token(current, "")
		&& !is_redir_token(current, "|"))
		return (print_unexpected(env, "newline", 2));
	return (1);
}
