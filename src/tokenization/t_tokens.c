#include "tokens.h"

t_token	*create_token(char *txt, t_qtype qtype)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->txt = ft_strdup(txt);
	if (!new->txt)
		return (free(new), NULL);
	new->qtype = qtype;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*current;

	if (!head || !new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
}

void	free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->txt);
		free(current);
		current = next;
	}
	*head = NULL;
}
