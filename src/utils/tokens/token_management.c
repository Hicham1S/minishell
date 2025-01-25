#include "../../../includes/minishell.h"
#include "tokens.h"

void    add_token(t_token **token, char *txt, t_qtype qtype, int flag)
{
	t_token *new;
	t_token *current;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return;
	new->txt = ft_strdup(txt);
	if (!new->txt)
	{
		free(new);
		return;
	}
	new->qtype = qtype;
	new->merge_next = flag;
	new->next = NULL;
	if (!(*token))
	{
		*token = new;
		return;
	}
	current = *token;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		temp = current->next;
		free(current->txt); 
		free(current);
		current = temp;
	}
	*tokens = NULL;
}

void	free_one_token(t_token *token)
{
	free(token->txt);
	token->next = NULL;
	free(token);
}

