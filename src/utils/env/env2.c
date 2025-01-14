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
		return;
	}
	current = *env;
	while (current && current->next)
	{
		if (ft_strcmp(current->next->key, key) == 0)
		{
			temp = current->next;
			current->next = current->next->next;
			free_one_env(temp);
			return;
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


// int main(int argc, char **argv, char **envp)
// {
// 	t_env *env = init_env(envp);

// 	t_env *current = env;

// 	while (current)
// 	{
// 		printf("%s=%s\n", current->key, current->value);
// 		current = current->next;
// 	}

// 	current = env;
// 	del_env(&env, "PATH");
// 	del_env(&env, "OLDPWD");
// 	del_env(&env, "LS_COLORS");
// 	printf("\n\n\n/////////////////////////////////\n\n\n");
// 	while (current)
// 	{
// 		printf("%s=%s\n", current->key, current->value);
// 		current = current->next;
// 	}
// 	free_env(env);
// 	return (0);
// }
