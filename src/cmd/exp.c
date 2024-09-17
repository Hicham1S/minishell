#include "cmd.h"

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

void	swap_env(t_env *env1, t_env *env2)
{
	char *temp;

	temp = env1->val;
	env1->val = env2->val;
	env2->val = temp;
}

t_env	*sort_env(t_env *env_clone)
{
	t_env	*current;
	t_env	*min;
	t_env	*temp;	

	if (env_clone == NULL)
		return (NULL);
	current = env_clone;
	while (current != NULL)
	{
		min = current;
		temp = current->next;
		while (temp != NULL)
		{
			if (ft_strcmp(temp->val, min->val) < 0)
				min = temp;
			temp = temp->next;
		}
		if(min != current)
			swap_env(min, current); // to swap if smaller element if found by Hicham
		current = current->next;
	}
	return (env_clone);
}

t_exp	*env_to_exp(t_env *env_clone)
{
	t_exp	*exp_clone;
	t_env	*sorted_env;
	char	*joined;

	exp_clone = NULL;
	sorted_env = sort_env(env_clone);
	while (sorted_env)
	{
		joined = ft_strjoin("declare -x ", sorted_env->val);
		if (!joined)
		{
			free_exp(&exp_clone); //free the previously alloc on memory error by Hicham
			return (NULL);
		add_exp(&exp_clone, create_exp(joined));
		free(joined);
		sorted_env = sorted_env->next;
	}
	return (exp_clone);
}

void    new_exp(t_exp **head, char *txt)
{

	t_exp *current;

	if (!head || !txt)
		return ;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = create_exp(txt);
	}
}

