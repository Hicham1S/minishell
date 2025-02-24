/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:46:25 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/23 12:46:25 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(t_cmd *cmd, t_env **envs)
{
	size_t	i;

	i = 1;
	while (cmd->args[i])
	{
		del_env(envs, cmd->args[i]);
		i++;
	}
	return (set_stat(envs, 0), EXIT_SUCCESS);
}
