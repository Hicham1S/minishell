/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 06:38:07 by hsarraj           #+#    #+#             */
/*   Updated: 2025/02/22 06:38:07 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_valid_number(const char *str)
{
	size_t	i;

	if (!str || !*str)
		return (false);
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

bool	is_overflowing(const char *str)
{
	bool	is_negative;

	if (!str || !*str)
		return (true);
	while (*str == '0' && str[1] != '\0')
		str++;
	is_negative = (str[0] == '-');
	if (ft_strlen(str) - is_negative > 19)
		return (true);
	if (!is_negative && ft_strcmp(str, "9223372036854775807") > 0)
		return (true);
	if (is_negative && ft_strcmp(str + 1, "9223372036854775807") > 0)
		return (true);
	return (false);
}

void	handle_exit_error(t_cmd *cmd, t_env *envs, char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	free_and_exit(cmd, envs, 2, NULL);
}

int	check_exit_args(t_cmd *cmd)
{
	if (cmd->args[2])
	{
		g_signal = 1;
		error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
