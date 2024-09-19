#include "env.h"

t_env	*enlist_env(char **envp)
{
	t_env	*env_clone;
	int		i;

	i = 0;
	env_clone = NULL;
	while (envp[i])
	{
		// fixed leaks here
		t_env *new = create_env(envp[i]);
		if(!new)
		{
			free_env(&env_clone);
			return (NULL);
		}
		add_env(&env_clone, new);
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
	t_env	*current;
	char	*target_name;

	current = head;
	while (current)
	{
		target_name = get_env_name(current->val);
		if (ft_strcmp(name, target_name) == 0)
		{
			free(target_name);
			free(current->val);
			current->val = ft_strdup(new);
			return (0);
		}
		free(target_name);
		current = current->next;
	}
	return (0);
}

