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

#include "../../includes/minishell.h"

void	free_and_exit(t_cmd *cmds, t_env *envs, int exit_code, char *msg)
{
	t_env	*tmp;

	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (cmds)
	{
		free_cmd(cmds);
		cmds = NULL;
	}
	while (envs)
	{
		tmp = envs;
		envs = envs->next;
		if (tmp)
			free_env(tmp);
	}
	exit(exit_code);
}

int	builtin_exit(t_cmd *cmd, t_env *envs)
{
	int	exit_code;

	if (!cmd->has_pipe)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->args[1])
		free_and_exit(cmd, envs, 0, NULL);
	if (!is_valid_number(cmd->args[1]) || is_overflowing(cmd->args[1]))
		handle_exit_error(cmd, envs, cmd->args[1]);
	if (check_exit_args(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exit_code = ft_atoi(cmd->args[1]) & 255;
	set_stat(&envs, exit_code);
	free_and_exit(cmd, envs, exit_code, NULL);
	return (EXIT_SUCCESS);
}
