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

int	builtin_export(t_cmd *cmd, t_env **envs)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (cmd->args && cmd->args[i])
	{
		j = 0;
		while (cmd->args[i][j] && cmd->args[i][j] != '=')
		{
			if ((cmd->args[i][0] >= '0' && cmd->args[i][0] <= '9')
				|| special_char(cmd->args[i][j]))
				return (error_detected(cmd->args[i]), EXIT_FAILURE);
			j++;
		}
		if (j == 0)
			return (error_detected(&cmd->args[i][j]), EXIT_FAILURE);
		if (cmd->args[i][j])
		{
			cmd->args[i][j] = '\0';
			char *value = ft_strdup(&cmd->args[i][j + 1]);
			if (!value)
				return (EXIT_FAILURE);
			set_env(envs, cmd->args[i], value);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
