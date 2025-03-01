/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:13:34 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/25 10:13:34 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	special_char(char c)
{
	return (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || (c == '_')));
}

void	error_detected(char *identifier)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	print_env(t_env *envs)
{
	t_env	*temp;

	temp = envs;
	while (temp)
	{
		if (ft_strcmp(temp->key, "?") != 0)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(temp->key, STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(temp->value, STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
		}
		temp = temp->next;
	}
}

int	validate_and_process_export(t_env **envs, char *arg)
{
	size_t	j;
	char	*value;

	j = 0;
	while (arg[j] && arg[j] != '=')
	{
		if ((arg[0] >= '0' && arg[0] <= '9') || special_char(arg[j]))
			return (error_detected(arg), EXIT_FAILURE);
		j++;
	}
	if (j == 0)
		return (error_detected(arg), EXIT_FAILURE);
	if (arg[j])
	{
		arg[j] = '\0';
		value = ft_strdup(&arg[j + 1]);
		if (!value)
			return (EXIT_FAILURE);
		set_env(envs, arg, value);
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(t_cmd *cmd, t_env **envs)
{
	size_t	i;
	int		exit_status;

	if (!cmd->args[1])
	{
		print_env(*envs);
		set_stat(envs, EXIT_SUCCESS);
		return (EXIT_SUCCESS);
	}
	exit_status = EXIT_SUCCESS;
	i = 1;
	while (cmd->args[i])
	{
		if (validate_and_process_export(envs, cmd->args[i]) == EXIT_FAILURE)
			exit_status = EXIT_FAILURE;
		i++;
	}
	set_stat(envs, exit_status);
	return (exit_status);
}
