#include "env.h"

t_env	*create_env(char *txt)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->val = ft_strdup(txt);
	//update part to make sure there aren't any leaks from Hicham
	if(!new->val)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	add_env(t_env **head, t_env *new)
{
	t_env	*current;

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
	}
}

void	free_env(t_env **head)
{
	t_env	*current;
	t_env	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free (current->val);
		free(current);
		current = next;
	}
	*head = NULL;
}