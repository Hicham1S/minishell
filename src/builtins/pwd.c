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
	char	path[1024];

	(void)envs;
	(void)cmd;
	if (!getcwd(path, 1024))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	if (check_pwd_opt(cmd))
	{
		set_stat(envs, 2);
		printf("minishell: pwd: -%c: invalid option\n",
				cmd->args[1][1]);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	return (set_stat(envs, 0) ,EXIT_SUCCESS);
}
