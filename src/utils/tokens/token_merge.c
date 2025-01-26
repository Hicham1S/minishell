#include "../../../includes/minishell.h"
#include "tokens.h"

static int	needs_merging(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->merge_next == 1)
			return (1);
		current = current->next;
	}
	return (0);
}

void	merge_tokens(t_token **token)
{
	t_token	*current;
	t_token	*temp;
	char	*new_txt;

	while (needs_merging(*token))
	{
		current = *token;
		while (current && current->next)
		{
			if (current->merge_next == 1)
			{
				new_txt = ft_strjoin(current->txt,
						current->next->txt);
				free(current->txt);
				current->txt = new_txt;
				current->merge_next = current->next->merge_next;
				temp = current->next;
				current->next = temp->next;
				free_one_token(temp);
			}
			else
				current = current->next;
		}
	}
}
