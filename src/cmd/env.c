#include "cmd.h"

t_env	*create_env(char *txt)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->val = ft_strdup(txt);
	//update parte to make sure there aren't any leaks from Hicham
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

t_env	*enlist_env(char **envp)
{
	t_env	*env_clone;
	int		i;

	i = 0;
	env_clone = NULL;
	while (envp[i])
	{
		//update parte to make sure there aren't any leaks from Hicham
		t_env *new = create_env(envp[i]);
		if(!new)
		{
			free_env(&env_clone);
			return (NULL);
		}
		add_env(&env_clone, create_env(envp[i]));
		i++;
	}
	return (env_clone);
}

char *get_env_clone(char *name, t_env *head)
{
	int j;
	char *substr;

	while (head)
	{
		j = 0;
		while (head->val[j] && head->val[j] != '=')
			j++;
		substr = ft_substr(head->val, 0, j);
		if(!substr) //Memory allocation failure by Hicham
			return (NULL);
		if (ft_strcmp(substr, name) == 0)
			return (free(substr), (head->val + j + 1));
		free(substr);
		head = head->next;
	}
	return (NULL);
}

int env_exists(char *name, t_env *head)
{
	if (get_env_clone(name, head) != NULL)
		return 1;
	return 0;
}

int modify_env_clone(char *name, t_env *head, char *new)
{
	char *entry;
	char *new_val;
	char *temp_val;

	entry = get_env_clone(name, head);
	if (!entry)
		return (-1);

	temp_val = ft_strjoin("=", new);
	if (!temp_val || !(new_val = ft_strjoin(name, temp_val)))
		return (-1);

	free(temp_val);
	free(entry);
	entry = new_val;
	return (0);
}
