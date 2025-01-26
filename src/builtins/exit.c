/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:44:04 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/25 12:44:04 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_and_exit(t_cmd *cmds, t_env *envs, int exit_code, char *msg)
{
	t_env	*tmp;

	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	free_cmds(cmds);
	while (envs)
	{
		tmp = envs;
		envs = envs->next;
		free_env(tmp);
	}
	exit(exit_code);
}

static	bool	is_valid_number(const char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_overflowing(const char *str)
{
	bool	is_negative;

	while (*str == '0' && str[1] != '\0')
		str++;
	is_negative = (str[0] == '-');
	if (ft_strlen(str) - is_negative > 19)
		return (true);
	if (is_negative && ft_strcmp(str + 1, "9223372036854775808") > 0)
		return (true);
	if (!is_negative && ft_strcmp(str, "9223372036854775807") > 0)
		return (true);
	return (false);
}

int	builtin_exit(t_cmd *cmd, t_env *envs)
{
	char	**args;

	args = cmd->args;
	if (!cmd->has_pipe)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!args[1])
		free_and_exit(cmd, envs, 0, NULL);
	if (!is_valid_number(args[1]) || is_overflowing(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		free_and_exit(cmd, envs, 2, NULL);
	}
	if (args[2])
	{
		g_exit_status = 1;
		error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	free_and_exit(cmd, envs, ft_atoi(args[1]) & 255, NULL);
	return (EXIT_SUCCESS);
}
