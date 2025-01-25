#include "../../../includes/minishell.h"
#include "env.h"

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
	t_env	*temp;

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
