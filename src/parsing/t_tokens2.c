#include "parsing.h"

t_token2	*create_token2(char *txt, t_type type)
{
	t_token2	*new;

	new = (t_token2 *)malloc(sizeof(t_token2));
	if (!new)
		return (NULL);
	new->txt = ft_strdup(txt);
	if (!new->txt)
		return (free(new), NULL);
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_token(t_token2 **head, t_token2 *new)
{
	t_token2	*current;

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

void	free_tokens(t_token2 **head)
{
	t_token2	*current;
	t_token2	*next;

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
