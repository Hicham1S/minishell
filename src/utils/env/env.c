#include "../../../includes/minishell.h"

t_env	*get_env(t_env *env, char *key)
{
	if (!key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	if (!key || !value)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	set_env(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*new;

	if (!key)
		return ;
	new = get_env(*env, key);
	if (new)
	{
		free(new->value);
		new->value = ft_strdup(value);
		return ;
	}
	new = new_env(ft_strdup(key), ft_strdup(value));
	if (*env)
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		*env = new;
}

void	free_env(t_env *env)
{
	t_env *temp;

    while (env)
    {
        temp = env;
        env = env->next;
		if (temp->key)
    	    free(temp->key);
		if (temp->value)
        	free(temp->value);
        free(temp);
    }
}

void	free_one_env(t_env *env)
{
	free(env->key);
	free(env->value);
	env->next = NULL;
	free(env);
}

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
