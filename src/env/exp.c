#include "env.h"

void	new_exp(t_exp **head, char *txt)
{
	t_exp	*new_node;
	t_exp	*current;

	if (!head || !txt)
		return ;
	new_node = create_exp(txt);
	if (!new_node)
		return ;
	add_double_quotes(new_node);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

char *get_exp_clone(char *name, t_exp *head)
{
	int j;
	char *substr;

	while (head)
	{
		j = 0;
		while (head->val[j] && head->val[j] != '=')
			j++;
		substr = ft_substr(head->val, 0, j);
		if(!substr)
			return (NULL);
		if (ft_strcmp(substr, name) == 0)
			return (free(substr), (head->val + j + 1));
		free(substr);
		head = head->next;
	}
	return (NULL);
}

int exp_exists(char *name, t_exp *head)
{
	if (get_exp_clone(name, head) != NULL)
		return (1);
	return 0;
}

int modify_exp_clone(char *name, t_exp *head, char *new)
{
	t_exp	*current;
	char	*target_name;

	current = head;
	while (current)
	{
		target_name = get_env_name(current->val);
		if (ft_strcmp(name, target_name) == 0)
		{
			free(target_name);
			free(current->val);
			current->val = add_double_quotes_to_str(new);
			return (0);
		}
		free(target_name);
		current = current->next;
	}
	free(target_name);
	return (0);
}
