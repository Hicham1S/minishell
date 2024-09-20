#include "env.h"

int	del_env(t_env *env_clone, char *env_name)
{
	t_env	*current;
	t_env	*prev;
	char	*target_name;

	current = env_clone;
	prev = NULL;
	while (current != NULL)
	{
		target_name = get_env_name(current->val);
		if (ft_strcmp(target_name, env_name) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				env_clone = env_clone->next;
			free(target_name);
			return (free(current->val), free(current), 0);
		}
		free(target_name);
		prev = current;
		current = current->next;
	}
	return (-1);
}

int	del_exp(t_exp *exp_clone, char *exp_name)
{
	t_exp	*current;
	t_exp	*prev;
	char	*target_name;

	current = exp_clone;
	prev = NULL;
	while (current != NULL)
	{
		target_name = get_env_name(current->val);
		if (ft_strcmp(target_name, exp_name) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				exp_clone = exp_clone->next;
			free(target_name);
			return (free(current->val), free(current), 0);
		}
		free(target_name);
		prev = current;
		current = current->next;
	}
	return (-1);
}

int handle_unset_errors(char *str)
{
	if (str[0] == '-')
	{
		ft_printf("bash: unset: -%c: invalid option\n", str[1]);
		return (2);
	}
	else
	{
		ft_printf("bash: unset: `%s': not a valid identifier\n", str);
		return (1);
	}
}

int	ft_unset(t_env *env_clone, t_exp *exp_clone, char *env_name)
{
	if (!check_env_exp(env_name) || env_name[0] == '='
		|| env_name[ft_strlen(env_name) - 1] == '='
		|| env_name[0] == '\0')
		return (handle_unset_errors(env_name));
	else
	{
		del_env(env_clone, env_name);
		del_exp(exp_clone, env_name);
		return (0);
	}
}