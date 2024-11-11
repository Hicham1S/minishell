#include "parsing.h"

int	is_redirection(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	has_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_redirection(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*before_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_redirection(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

char	*the_redirection(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && !is_redirection(str[i]))
		i++;
	j = i;
	while (str[j] && is_redirection(str[j]))
	{
		j++;
		len++;
	}
	return (ft_substr(str, i, len));
}

char	*after_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_redirection(str[i]))
		i++;
	while (str[i] && is_redirection(str[i]))
		i++;
	return (ft_substr(str, i, ft_strlen(str) - i));
}

void	process_redirection(t_token *current)
{
	char	*temp;
	char	*before;
	char	*redir;
	char	*after;
	t_token	*next;

	temp = current->txt;
	before = before_redirection(temp);
	redir = the_redirection(temp);
	after = after_redirection(temp);
	current->txt = before;
	next = current->next;
	current->next = create_token(redir, NO);
	if (after[0] != '\0')
		current->next->next = create_token(after, NO);
	else
		current->next->next = NULL;
	current->next->next->next = next;
	free(temp);
	free(redir);
	free(after);
}

void	separate_redirections(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (has_redirection(current->txt) && current->qtype == NO)
		{
			process_redirection(current);
			current = current->next->next;
		}
		else
			current = current->next;
	}
}
