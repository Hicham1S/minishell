#include "parsing.h"

void	merge_tokens(t_token *tokens)
{
	t_token	*prev;
	t_token *current;
	char	*new_txt;

	prev = tokens;
	while (prev && prev->next)
	{
		current = prev->next;
		if (!prev->space)
		{
			new_txt = ft_strjoin(prev->txt, current->txt);
			free(prev->txt);
			prev->txt = new_txt;
			prev->space = current->space;
			prev->next = current->next;
			if (current->next) 
				current->next->prev = prev;
			free(current->txt);
			free(current);
		}
		else
			prev = current;
	}
}

void	finalize_tokens(t_token *tokens, t_env *env_clone)
{
	do_handle_dollar(tokens, env_clone);
	merge_tokens(tokens);
}