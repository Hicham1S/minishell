#include "env.h"

t_exp *create_exp(char *txt)
{
	t_exp *new;

	new = (t_exp *)malloc(sizeof(t_exp));
	if (!new)
		return (NULL);
	new->val = ft_strdup(txt);
	if(!new->val) //check if strdup work by Hicham
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void add_exp(t_exp **head, t_exp *new)
{
	t_exp *current;

	if (!head || !new)
		return;
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void free_exp(t_exp **head)
{
	t_exp *current;
	t_exp *next;

	if (!head || !*head)
		return;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->val);
		free(current);
		current = next;
	}
	*head = NULL;
}