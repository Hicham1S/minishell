/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:04:24 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/17 11:04:24 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_pwd_opt(t_cmd *cmd)
{
	return (cmd->args[1] && cmd->args[1][0] == '-' && cmd->args[1][1]);
}

int	builtin_pwd(t_cmd *cmd, t_env **envs)
{
	char	*path;

	if (check_pwd_opt(cmd))
	{
		set_stat(envs, 2);
		ft_putstr_fd("minishell: pwd: invalid option -- '", STDERR_FILENO);
		ft_putchar_fd(cmd->args[1][1], STDERR_FILENO);
		ft_putstr_fd("'\nTry 'pwd --help' for more information.\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	path = getcwd(NULL, 0);
	if (!path)
		return (set_stat(envs, 1), EXIT_FAILURE);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (set_stat(envs, 0), EXIT_SUCCESS);
}
