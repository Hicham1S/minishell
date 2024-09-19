#include "env.h"

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

char *add_double_quotes_to_str(char *str)
{
	int j = 0;
	char *new_val;

	while (str[j] && str[j] != '=')
		j++;

	if (str[j] == '=')
	{
		new_val = malloc(ft_strlen(str) + 3);  // Allocate +2 for quotes and +1 for '\0'
		if (!new_val)
			return NULL;

		ft_strlcpy(new_val, str, j + 2);  // Copy "name=" part
		new_val[j + 1] = '\"';  // Add first quote after '='
		ft_strlcpy(new_val + j + 2, str + j + 1, ft_strlen(str + j + 1) + 1);  // Copy the value part
		ft_strlcat(new_val, "\"", ft_strlen(new_val) + 2);  // Add second quote at the end

		return new_val;
	}
	return NULL;
}

void add_double_quotes(t_exp *head)
{
	while (head)
	{
		char *new_val = add_double_quotes_to_str(head->val);
		if (new_val)
		{
			free(head->val);  // Free old value
			head->val = new_val;  // Assign new value with quotes
		}
		head = head->next;
	}
}

t_exp	*env_to_exp(t_env *env_clone)
{
	t_exp	*exp_clone;
	t_env	*sorted_env;
	t_exp	*new_exp;

	exp_clone = NULL;
	sorted_env = sort_env(env_clone);

	while (sorted_env)
	{
		new_exp = create_exp(sorted_env->val);
		if (!new_exp)
		{
			free_exp(&exp_clone);
			return (NULL);
		}
		add_exp(&exp_clone, new_exp);
		sorted_env = sorted_env->next;
	}

	add_double_quotes(exp_clone);
	return (exp_clone);
}
