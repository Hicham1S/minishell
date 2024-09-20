#include "env.h"

int	pre_equal(char c)
{
	return (ft_isalnum(c) || c == '_');
}

//{valid identifier, equal exists, exists in env, exists in exp}
int *new_env_status(t_env *env_clone, t_exp *exp_clone, char *str)
{
	int	i;
	int	*flags;
	char *env_name;

	i = -1;
	env_name = get_env_name(str);
	flags = (int *)malloc(4 * sizeof(int));
	if (!flags)
		return (NULL);
	ft_memset(flags, 0, 4 * sizeof(int));
	flags[0] = 1;
	if (!check_env_exp(str) || str[0] == '='
		|| str[ft_strlen(str) - 1] == '=' || str[0] == '\0')
	{
		flags[0] = 0; 
		return (flags);
	}
	while (str[++i])
		if (str[i] == '=')
			flags[1] = 1;
	if (env_exists(env_name, env_clone))
		flags[2] = 1;
	if (exp_exists(env_name, exp_clone))
		flags[3] = 1;
	return (free(env_name), flags);
}

int handle_export_errors(char *str)
{
	if (str[0] == '-')
	{
		ft_printf("bash: export: -%c: invalid option\n", str[1]);
		return (2);
	}
	else
	{
		ft_printf("bash: export: `%s': not a valid identifier\n", str);
		return (1);
	}
}

int	register_env_exp(char *str, t_env *env_clone, t_exp *exp_clone)
{
	char	*env_name;
	int		*flags;

	flags = new_env_status(env_clone, exp_clone, str);
	env_name = get_env_name(str);
	if (flags[0] == 0)
		return (handle_export_errors(str));
	if (flags[3] == 1)
		modify_exp_clone(env_name, exp_clone, str);
	else
		add_exp(&exp_clone, create_exp(str));
	if (flags[1] == 1)
	{
		if (flags[2] == 1)
			modify_env_clone(env_name, env_clone, str);
		else
			add_env(&env_clone, create_env(str));
	}
	return (free(env_name), free(flags), 0);
}
