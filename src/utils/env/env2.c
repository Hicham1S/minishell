#include "../../../includes/minishell.h"
#include "env.h"

void	del_env(t_env **env, char *key)
{
	t_env	*temp;
	t_env	*current;

	if (*env && ft_strcmp((*env)->key, key) == 0)
	{
		temp = *env;
		*env = (*env)->next;
		free_one_env(temp);
		return ;
	}
	current = *env;
	while (current && current->next)
	{
		if (ft_strcmp(current->next->key, key) == 0)
		{
			temp = current->next;
			current->next = current->next->next;
			free_one_env(temp);
			return ;
		}
		current = current->next;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	while (*envp)
	{
		i = 0;
		while ((*envp)[i] != '=' && (*envp)[i])
			i++;
		key = ft_substr(*envp, 0, i);
		value = ft_substr(*envp, i + 1, ft_strlen(*envp) - (i + 1));
		set_env(&env, key, value);
		free(key);
		free(value);
		envp++;
	}
	set_env(&env, "?", "0");
	return (env);
}
