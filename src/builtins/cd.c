/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:06:52 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/21 15:06:52 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_oldpwd_path(t_env **envs)
{
	t_env	*oldpwd_env;

	oldpwd_env = get_env(*envs, "OLDPWD");
	if (!oldpwd_env || !oldpwd_env->value)
		return (error("cd", "OLDPWD not set"), NULL);
	return (ft_strdup(oldpwd_env->value));
}

static void	update_pwd_oldpwd(t_env **envs, char *oldpwd)
{
	char	current[1024];

	if (getcwd(current, 1024))
	{
		set_env(envs, "PWD", current);
		set_env(envs, "OLDPWD", oldpwd);
	}
}

static int	change_directory(char *path, t_env **envs, char *oldpwd)
{
	if (chdir(path) == -1)
	{
		error_invalid_cd(path, envs);
		free(path);
		return (EXIT_FAILURE);
	}
	update_pwd_oldpwd(envs, oldpwd);
	free(path);
	set_stat(envs, 0);
	return (EXIT_SUCCESS);
}

int	builtin_cd(t_cmd *cmd, t_env **envs)
{
	char	*path;
	char	oldpwd[1024];

	if (!getcwd(oldpwd, 1024))
		return (error("cd", "getcwd failed"), EXIT_FAILURE);
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
		path = get_oldpwd_path(envs);
	else
	{
		path = get_path(cmd, envs);
		if (path && path[0] == '~')
			tilted_path(envs, &path);
	}
	if (!path)
		return (EXIT_FAILURE);
	return (change_directory(path, envs, oldpwd));
}
