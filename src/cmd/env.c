#include "cmd.h"

t_env	*create_env(char *txt)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->val = ft_strdup(txt);
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
		if (ft_strcmp(substr, name) == 0)
			return (free(substr), (head->val + j + 1));
		free(substr);
		head = head->next;
	}
	return (NULL);
}

// void    print_env_list(t_env *head)
// {
//     t_env *current = head;

//     while (current != NULL)
//     {
//         printf("NODE: %s\n\n\n", current->val);
//         current = current->next;
//     }
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_env   *env_clone;

//     // Enlist environment variables into a linked list
//     env_clone = enlist_env(envp);

//     // Print the environment variables to verify the list
//     print_env_list(env_clone);

//     // Free the linked list after use
//     free_env(&env_clone);

//     return 0;
// }