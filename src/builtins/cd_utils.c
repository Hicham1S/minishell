/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:59:21 by hsarraj           #+#    #+#             */
/*   Updated: 2025/03/01 09:59:21 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*home_path(t_env **envs)
{
	t_env	*env;

	env = get_env(*envs, "HOME");
	if (!env)
	{
		set_stat(envs, 1);
		return (error("cd", "HOME not set"), NULL);
	}
	return (env->value);
}

char	*get_path(t_cmd *cmd, t_env **envs)
{
	size_t	i;
	char	*path;
	char	*home;

	i = 1;
	path = NULL;
	while (cmd->args[i])
	{
		if (cmd->args[i][0])
		{
			if (path)
				return (set_stat(envs, 1), error("cd",
						"too many arguments"), NULL);
			path = cmd->args[i];
		}
		i++;
	}
	if (!path)
	{
		home = home_path(envs);
		if (home)
			return (ft_strdup(home));
		return (NULL);
	}
	return (ft_strdup(path));
}

void	tilted_path(t_env **envs, char **path)
{
	char	*home;
	char	*tmp;

	home = home_path(envs);
	if (home)
	{
		tmp = ft_strjoin(home, *path + 1);
		free(*path);
		*path = tmp;
	}
}
